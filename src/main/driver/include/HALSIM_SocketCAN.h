#pragma once

typedef void* HALSIM_SocketCAN_Handle;

extern "C" {
HALSIM_SocketCAN_Handle HALSIM_SocketCAN_Enable(const char* name);
void HALSIM_SocketCAN_Clean(HALSIM_SocketCAN_Handle handle);
}
