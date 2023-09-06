#include "HALSIM_SocketCAN.h"

#include "CANController.h"

#include "hal/CAN.h"
#include "hal/simulation/CanData.h"
#include <cstring>

namespace
{
struct HALSIM_SocketCAN
{
    CANController controller;
    int32_t sendMessageHandle;
    int32_t receiveMessageHandle;
    int32_t canStatusCallback;
};
} // namespace

static void SendMessageCallback(const char *name, void *param,
                                uint32_t messageID,
                                const uint8_t *data,
                                uint8_t dataSize, int32_t periodMs,
                                int32_t *status)
{
    HALSIM_SocketCAN& controller = *static_cast<HALSIM_SocketCAN*>(param);
    CANData canData;
    std::memcpy(canData.data, data, dataSize);
    canData.length = dataSize;
    canData.id = messageID;
    // TODO: Handle Repeating
    controller.controller.putData(canData);
    *status = 0;
}

static void ReceiveMessageCallback(const char *name, void *param, uint32_t *messageID, uint32_t messageIDMask,
                                   uint8_t *data, uint8_t *dataSize, uint32_t *timeStamp, int32_t *status)
{
    HALSIM_SocketCAN& controller = *static_cast<HALSIM_SocketCAN*>(param);
    auto readData = controller.controller.getData(*messageID,messageIDMask);
    if (!readData.has_value()) {
        *status = HAL_ERR_CANSessionMux_MessageNotFound;
        return;
    }

    std::memcpy(data, readData->data, readData->length);
    *dataSize = readData->length;
    *timeStamp = readData->timestamp;
    *messageID = readData->id;
    *status = 0;
}

static void StatusCallback(const char *name, void *param, float *percentBusUtilization,
                           uint32_t *busOffCount, uint32_t *txFullCount, uint32_t *receiveErrorCount,
                           uint32_t *transmitErrorCount, int32_t *status)
{
    *status = 0;
}

extern "C"
{
    HALSIM_SocketCAN_Handle HALSIM_SocketCAN_Enable(const char *name)
    {
        auto controller = new HALSIM_SocketCAN{};
        if (controller->controller.start(name) < 0)
        {
            delete controller;
            return nullptr;
        }

        controller->sendMessageHandle = HALSIM_RegisterCanSendMessageCallback(SendMessageCallback, controller);
        controller->receiveMessageHandle = HALSIM_RegisterCanReceiveMessageCallback(ReceiveMessageCallback, controller);
        controller->canStatusCallback = HALSIM_RegisterCanGetCANStatusCallback(StatusCallback, controller);

        return controller;
    }
    void HALSIM_SocketCAN_Clean(HALSIM_SocketCAN_Handle handle)
    {
        HALSIM_SocketCAN* controller = static_cast<HALSIM_SocketCAN *>(handle);
        HALSIM_CancelCanGetCANStatusCallback(controller->canStatusCallback);
        HALSIM_CancelCanReceiveMessageCallback(controller->receiveMessageHandle);
        HALSIM_CancelCanSendMessageCallback(controller->sendMessageHandle);
        delete controller;
    }
}
