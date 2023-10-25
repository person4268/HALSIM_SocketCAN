#include <hal/Extensions.h>
#include "HALSIM_SocketCAN.h"
#include <cstdio>

extern "C" {
#if defined(WIN32) || defined(_WIN32)
__declspec(dllexport)
#endif
    int HALSIM_InitExtension(void) {
  std::puts("SocketCAN Initializing.");

  HALSIM_SocketCAN_Handle handle = HALSIM_SocketCAN_Enable("vcan0");

  std::puts("SocketCAN Initialized!");
  return 0;
}
}  // extern "C"
