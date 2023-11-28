#include <hal/Extensions.h>
#include "HALSIM_SocketCAN.h"
#include <cstdio>
#include <cstdlib>

extern "C" {
#if defined(WIN32) || defined(_WIN32)
__declspec(dllexport)
#endif
    int HALSIM_InitExtension(void) {
  std::puts("SocketCAN Initializing.");

  HALSIM_SocketCAN_Handle handle = HALSIM_SocketCAN_Enable(std::getenv("SOCKETCAN_INTERFACE"));
  if (handle == nullptr) {
    std::puts("Failed to initialize SocketCAN");
  } else {
    std::puts("SocketCAN Initialized!");
  }
  return 0;
}
}  // extern "C"
