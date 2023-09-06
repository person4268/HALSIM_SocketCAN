#pragma once

typedef void* HALSIM_SocketCAN_Handle;

extern "C" {
/**
 * Binds the WPILib HAL CAN sim system to the specified SocketCAN interface.
 * @param port The socketcan interface to bind to
 * @return 0 on success, -1 on failure
 */
HALSIM_SocketCAN_Handle HALSIM_SocketCAN_Enable(const char* name);

/**
 * Unbinds the WPILib HAL CAN sim system.
 */
void HALSIM_SocketCAN_Clean(HALSIM_SocketCAN_Handle handle);
}
