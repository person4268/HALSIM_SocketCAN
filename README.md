# HALSIM_SocketCAN

This binds SocketCAN listeners to HALSIM CAN functions. As SocketCAN is Linux only, this halsim extension only functions on Linux platforms that are in simulation mode.
Supports both Java and C++.

Applications:
 * Hardware attached integration testing with CAN devices
 * using WPILib on something that's not a roboRIO
 * using real CAN with a Romi or something similar (may require additional work)


# Building/Installing

1. Clone https://github.com/wpilibsuite/allwpilib

2. run
```bash
mkdir build && cd build && cmake .. -DWPILIB_DIR=../path/to/wpilib/clone && make -j
```
in this repo

3. Add libhalsim_socketcan.so to HALSIM_EXTENSIONS when simulating.

# General running tips

FRC non-FD buses (that is, everything except the CANivore) uses 1 Mbps CAN so to configure a SocketCAN interface on ``can0`` one might do:

```bash
sudo ip link set can0 type can bitrate 1000000 && sudo ip link set can0 up
```
to provision ``can0``

Or use `vcan.sh` to setup a virtual can bus.

## Running with custom halsim extensions
```bash
HALSIM_EXTENSIONS=${ROBOT_CODE_PATH}/build/jni/release/libhalsim_gui.so:${HALSIM_SOCKETCAN_PATH}/build/libhalsim_socketcan.so LD_LIBRARY_PATH=${ROBOT_CODE_PATH}/build/jni/release SOCKETCAN_INTERFACE=vcan0 ~/wpilib/2025/jdk/bin/java -jar build/libs/2025Robot.jar
```
replacing env vars and names as needed
