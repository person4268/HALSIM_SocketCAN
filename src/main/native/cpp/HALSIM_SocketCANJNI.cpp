#include "jni.h"
#include "halsim_socketcan_HALSIM_SocketCAN.h"
#include "HALSIM_SocketCAN.h"
#include <unordered_map>
#include <stdint.h>
#include <mutex>

static std::unordered_map<int, HALSIM_SocketCAN_Handle> handle_map;
static int ctr = 0;
static std::mutex handle_lock;

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
    // Check to ensure the JNI version is valid

    JNIEnv* env;
    if (vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK)
        return JNI_ERR;

    // In here is also where you store things like class references
    // if they are ever needed

    return JNI_VERSION_1_6;
}

JNIEXPORT void JNICALL JNI_OnUnload(JavaVM* vm, void* reserved) {}

JNIEXPORT jint JNICALL Java_halsim_socketcan_HALSIM_1SocketCAN_enable
  (JNIEnv * env, jclass, jstring portObj) {
    const char* port = env->GetStringUTFChars(portObj, 0);
    HALSIM_SocketCAN_Handle hdl = HALSIM_SocketCAN_Enable(port);
    if (hdl == nullptr) return -1;
    {
      std::lock_guard<std::mutex> guard{handle_lock};
      int ptr = ctr++;
      handle_map[ptr] = hdl;
      return ptr;
    }

}

JNIEXPORT void JNICALL Java_halsim_socketcan_HALSIM_1SocketCAN_clean
  (JNIEnv * env, jclass, jint handle) {

    std::lock_guard<std::mutex> guard{handle_lock};
    if (!handle_map.contains(handle)) return;

    HALSIM_SocketCAN_Handle hdl = handle_map[handle];
    HALSIM_SocketCAN_Clean(hdl);
    handle_map.erase(handle);
}
