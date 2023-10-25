#include <hal/Extensions.h>
#include "HALSIM_SocketCAN.h"
extern "C" {
#if defined(WIN32) || defined(_WIN32)
__declspec(dllexport)
#endif
    int HALSIM_InitExtension(void) {
  std::puts("SocketCAN Initializing.");

  HALSIM_SocketCAN_Handle handle = HALSIM_SocketCAN_Enable("vcan0");
  HAL_OnShutdown(nullptr, [handle](void*) { HALSIM_SocketCAN_Clean(handle); });

  std::puts("SocketCAN Initialized!");
  return 0;
}
}  // extern "C"
