#include "jni.h"
#include "halsim_socketcan_HALSIM_SocketCAN.h"

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
  (JNIEnv *, jclass, jstring portObj) {
  return 0;
}

JNIEXPORT void JNICALL Java_halsim_socketcan_HALSIM_1SocketCAN_clean
  (JNIEnv *, jclass, jint handle) {
  return;
}
