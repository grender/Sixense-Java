#include "sixense_java_utils.h"
#include "button_states.hpp"
#include "com_sixense_utils_ButtonStates.h"

JNIEXPORT jlong JNICALL Java_com_sixense_utils_ButtonStates_create(JNIEnv *, jobject) {
    sixenseUtils::ButtonStates * bStates = new sixenseUtils::ButtonStates();
    return (jlong) bStates;
}

JNIEXPORT void JNICALL Java_com_sixense_utils_ButtonStates_destroy(JNIEnv *env, jobject self) {
    jfieldID fid = getPeerID(env, self);
    jlong peer = env->GetLongField(self, fid);
    if(peer == 0) {
        return;
    }
    free((void *) peer);
    return;
}

JNIEXPORT void JNICALL Java_com_sixense_utils_ButtonStates_update(JNIEnv *env, jobject self, jobject ref) {
    jfieldID fid = getPeerID(env, self);
    sixenseUtils::ButtonStates * bStates = (sixenseUtils::ButtonStates *)env->GetLongField(self, fid);
    sixenseControllerData * data = getControllerData(env, ref);
    bStates->update(data);
    return;
}

JNIEXPORT void JNICALL Java_com_sixense_utils_ButtonStates_setTriggerThreshold(JNIEnv *env, jobject self, jfloat flo) {
    jfieldID fid = getPeerID(env, self);
    sixenseUtils::ButtonStates * bStates = (sixenseUtils::ButtonStates *)env->GetLongField(self, fid);
    bStates->setTriggerThreshold(flo);
    return;
}

JNIEXPORT void JNICALL Java_com_sixense_utils_ButtonStates_setStickThreshold(JNIEnv *env, jobject self, jfloat flo) {
    jfieldID fid = getPeerID(env, self);
    sixenseUtils::ButtonStates * bStates = (sixenseUtils::ButtonStates *)env->GetLongField(self, fid);
    bStates->setStickThreshold(flo);
    return;
}

JNIEXPORT void JNICALL Java_com_sixense_utils_ButtonStates_setAbsoluteTiltAngleThreshold(JNIEnv *env, jobject self, jfloat flo) {
    jfieldID fid = getPeerID(env, self);
    sixenseUtils::ButtonStates * bStates = (sixenseUtils::ButtonStates *)env->GetLongField(self, fid);
    bStates->setAbsoluteTiltAngleThresholdInDeg(flo);
    return;
}

JNIEXPORT void JNICALL Java_com_sixense_utils_ButtonStates_setRelativeTiltAngleThreshold(JNIEnv *env, jobject self, jfloat flo) {
    jfieldID fid = getPeerID(env, self);
    sixenseUtils::ButtonStates * bStates = (sixenseUtils::ButtonStates *)env->GetLongField(self, fid);
    bStates->setRelativeTiltAngleThresholdInDeg(flo);
    return;
}

JNIEXPORT void JNICALL Java_com_sixense_utils_ButtonStates_setRelativeOrigin(JNIEnv *env, jobject self) {
    jfieldID fid = getPeerID(env, self);
    sixenseUtils::ButtonStates * bStates = (sixenseUtils::ButtonStates *)env->GetLongField(self, fid);
    bStates->setRelativeOrigin();
    return;
}

JNIEXPORT void JNICALL Java_com_sixense_utils_ButtonStates_startPointGesture(JNIEnv *env, jobject self) {
    jfieldID fid = getPeerID(env, self);
    sixenseUtils::ButtonStates * bStates = (sixenseUtils::ButtonStates *)env->GetLongField(self, fid);
    bStates->startPointGesture();
    return;
}

JNIEXPORT void JNICALL Java_com_sixense_utils_ButtonStates_stopPointGesture(JNIEnv *env, jobject self) {
    jfieldID fid = getPeerID(env, self);
    sixenseUtils::ButtonStates * bStates = (sixenseUtils::ButtonStates *)env->GetLongField(self, fid);
    bStates->stopPointGesture();
    return;
}

JNIEXPORT jboolean JNICALL Java_com_sixense_utils_ButtonStates_justStarted(JNIEnv *env, jobject self, jobject enumObj, jint arg) {
    jfieldID fid = getPeerID(env, self);
    sixenseUtils::ButtonStates * bStates = (sixenseUtils::ButtonStates *)env->GetLongField(self, fid);
    jclass enumClass = env->FindClass("com/sixense/utils/enums/EnumActionType");
    if(enumClass == NULL) return JNI_FALSE;
    jmethodID getNameMethod = env->GetMethodID(enumClass, "name", "()Ljava/lang/String;");
    if(getNameMethod == NULL) return JNI_FALSE;
    jstring value = (jstring) env->CallObjectMethod(enumObj, getNameMethod);
    const char* valueNative = env->GetStringUTFChars(value, JNI_FALSE);
    if(strcmp(valueNative, "BUTTON_PRESS") == 0) {
        return bStates->justStarted(sixenseUtils::ButtonStates::ACTION_BUTTON_PRESS, arg);
    } else if(strcmp(valueNative, "JOYSTICK_MOVE") == 0) {
        return bStates->justStarted(sixenseUtils::ButtonStates::ACTION_JOYSTICK_MOVE, arg);
    } else if(strcmp(valueNative, "TRIGGER_PRESS") == 0) {
        return bStates->justStarted(sixenseUtils::ButtonStates::ACTION_TRIGGER_PRESS, arg);
    } else if(strcmp(valueNative, "TILT_GESTURE") == 0) {
        return bStates->justStarted(sixenseUtils::ButtonStates::ACTION_TILT_GESTURE, arg);
    } else if(strcmp(valueNative, "POINT_GESTURE") == 0) {
        return bStates->justStarted(sixenseUtils::ButtonStates::ACTION_POINT_GESTURE, arg);
    } else if(strcmp(valueNative, "VELOCITY_GESTURE") == 0) {
        return bStates->justStarted(sixenseUtils::ButtonStates::ACTION_VELOCITY_GESTURE, arg);
    }
    return JNI_FALSE;
}

JNIEXPORT jboolean JNICALL Java_com_sixense_utils_ButtonStates_justStopped(JNIEnv *env, jobject self, jobject enumObj, jint arg) {
    jfieldID fid = getPeerID(env, self);
    sixenseUtils::ButtonStates * bStates = (sixenseUtils::ButtonStates *)env->GetLongField(self, fid);
    jclass enumClass = env->FindClass("com/sixense/utils/enums/EnumActionType");
    if(enumClass == NULL) return JNI_FALSE;
    jmethodID getNameMethod = env->GetMethodID(enumClass, "name", "()Ljava/lang/String;");
    if(getNameMethod == NULL) return JNI_FALSE;
    jstring value = (jstring) env->CallObjectMethod(enumObj, getNameMethod);
    const char* valueNative = env->GetStringUTFChars(value, JNI_FALSE);
    if(strcmp(valueNative, "BUTTON_PRESS") == 0) {
        return bStates->justStopped(sixenseUtils::ButtonStates::ACTION_BUTTON_PRESS, arg);
    } else if(strcmp(valueNative, "JOYSTICK_MOVE") == 0) {
        return bStates->justStopped(sixenseUtils::ButtonStates::ACTION_JOYSTICK_MOVE, arg);
    } else if(strcmp(valueNative, "TRIGGER_PRESS") == 0) {
        return bStates->justStopped(sixenseUtils::ButtonStates::ACTION_TRIGGER_PRESS, arg);
    } else if(strcmp(valueNative, "TILT_GESTURE") == 0) {
        return bStates->justStopped(sixenseUtils::ButtonStates::ACTION_TILT_GESTURE, arg);
    } else if(strcmp(valueNative, "POINT_GESTURE") == 0) {
        return bStates->justStopped(sixenseUtils::ButtonStates::ACTION_POINT_GESTURE, arg);
    } else if(strcmp(valueNative, "VELOCITY_GESTURE") == 0) {
        return bStates->justStopped(sixenseUtils::ButtonStates::ACTION_VELOCITY_GESTURE, arg);
    }
    return JNI_FALSE;
}


