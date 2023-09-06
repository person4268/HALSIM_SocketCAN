# HALSIM_SocketCAN

This binds SocketCAN listeners to HALSIM CAN functions. As SocketCAN is Linux only, this vendordep only functions on Linux platforms that are in simulation mode.
Supports both Java and C++.

Applications:
 * Hardware attached integration testing with CAN devices
 * using WPILib on something that's not a roboRIO
 * using real CAN with a Romi or something similar (may require additional work)


# Building/Installing

1. copy [HALSIM_SocketCAN.json](HALSIM_SocketCAN.json) to your project's vendordep json folder

2. run
```bash
# Feel free to change 2023 to the correct year
./gradlew publishToMavenLocal && cp -r ~/.m2/repository/halsim ~/wpilib/2023/maven
```
in this repo

Eventually there will be a proper maven sever...hopefully.


## Building and editing this vendordep
This uses gradle, and uses the same base setup as a standard GradleRIO robot project. This means you build with `./gradlew build`, and can install the native toolchain with `./gradlew installRoboRIOToolchain`. If you open this project in VS Code with the wpilib extension installed, you will get intellisense set up for both C++ and Java.

By default, this template builds against the latest WPILib development build. To build against the last WPILib tagged release, build with `./gradlew build -PreleaseMode`.
