#include "sixense_java_utils.h"
#include "fps.hpp"
#include "com_sixense_utils_Events.h"

JNIEXPORT jlong JNICALL Java_com_sixense_utils_Events_create(JNIEnv *, jobject) {
	sixenseUtils::FPSEvents * events = new sixenseUtils::FPSEvents();
    return (jlong) events;
}

JNIEXPORT void JNICALL Java_com_sixense_utils_Events_destroy(JNIEnv *env, jobject self) {
	jfieldID fid = getPeerID(env, self);
    jlong peer = env->GetLongField(self, fid);
    if(peer == 0) {
        return;
    }
    free((void *) peer);
    return;
}

JNIEXPORT void JNICALL Java_com_sixense_utils_Events_setGame(JNIEnv *env, jobject self, jstring str) {
	jfieldID fid = getPeerID(env, self);
    sixenseUtils::FPSEvents * events = (sixenseUtils::FPSEvents *)env->GetLongField(self, fid);
    const char * nstr = env->GetStringUTFChars(str, NULL);
    if(nstr == NULL) {
        return;
    }
    events->setGame(nstr);
    return;
}

JNIEXPORT void JNICALL Java_com_sixense_utils_Events_setBinding(JNIEnv *env, jobject self, jobject eventRef, jobject controllerRef, jobject actionRef, jint param) {
	jfieldID fid = getPeerID(env, self);
    sixenseUtils::FPSEvents * events = (sixenseUtils::FPSEvents *)env->GetLongField(self, fid);

	sixenseUtils::FPSEvents::fps_event eventParam;
    jclass enumClass = env->FindClass("com/sixense/utils/enums/EnumEvent");
    if(enumClass == NULL) return;
    jmethodID getNameMethod = env->GetMethodID(enumClass, "name", "()Ljava/lang/String;");
    if(getNameMethod == NULL) return;
    jstring value = (jstring) env->CallObjectMethod(eventRef, getNameMethod);
    const char* valueNative = env->GetStringUTFChars(value, JNI_FALSE);
    if(strcmp(valueNative, "WALK_LEFT") == 0) {
        eventParam = sixenseUtils::FPSEvents::WALK_LEFT;
    } else if(strcmp(valueNative, "WALK_RIGHT") == 0) {
        eventParam = sixenseUtils::FPSEvents::WALK_RIGHT;
    } else if(strcmp(valueNative, "WALK_FORWARD") == 0) {
        eventParam = sixenseUtils::FPSEvents::WALK_FORWARD;
    } else if(strcmp(valueNative, "WALK_BACK") == 0) {
        eventParam = sixenseUtils::FPSEvents::WALK_BACK;
    } else if(strcmp(valueNative, "JUMP") == 0) {
        eventParam = sixenseUtils::FPSEvents::JUMP;
    } else if(strcmp(valueNative, "USE") == 0) {
        eventParam = sixenseUtils::FPSEvents::USE;
    } else if(strcmp(valueNative, "PRIMARY_FIRE") == 0) {
        eventParam = sixenseUtils::FPSEvents::PRIMARY_FIRE;
    } else if(strcmp(valueNative, "SECONDARY_FIRE") == 0) {
        eventParam = sixenseUtils::FPSEvents::SECONDARY_FIRE;
    } else if(strcmp(valueNative, "ZOOM") == 0) {
        eventParam = sixenseUtils::FPSEvents::ZOOM;
    } else if(strcmp(valueNative, "MELEE") == 0) {
        eventParam = sixenseUtils::FPSEvents::MELEE;
    } else if(strcmp(valueNative, "LEAN_LEFT") == 0) {
        eventParam = sixenseUtils::FPSEvents::LEAN_LEFT;
    } else if(strcmp(valueNative, "LEAN_RIGHT") == 0) {
        eventParam = sixenseUtils::FPSEvents::LEAN_RIGHT;
    } else if(strcmp(valueNative, "CROUCH") == 0) {
        eventParam = sixenseUtils::FPSEvents::CROUCH;
    } else if(strcmp(valueNative, "SPRINT") == 0) {
        eventParam = sixenseUtils::FPSEvents::SPRINT;
    } else if(strcmp(valueNative, "THROW_GRENADE") == 0) {
        eventParam = sixenseUtils::FPSEvents::THROW_GRENADE;
    } else if(strcmp(valueNative, "FLASHLIGHT") == 0) {
        eventParam = sixenseUtils::FPSEvents::FLASHLIGHT;
    } else if(strcmp(valueNative, "NIGHTVISION") == 0) {
        eventParam = sixenseUtils::FPSEvents::NIGHTVISION;
    } else if(strcmp(valueNative, "RELOAD") == 0) {
        eventParam = sixenseUtils::FPSEvents::RELOAD;
    } else if(strcmp(valueNative, "NEXT_WEAPON") == 0) {
        eventParam = sixenseUtils::FPSEvents::NEXT_WEAPON;
    } else if(strcmp(valueNative, "PREV_WEAPON") == 0) {
        eventParam = sixenseUtils::FPSEvents::PREV_WEAPON;
    } else if(strcmp(valueNative, "ESC_KEY") == 0) {
        eventParam = sixenseUtils::FPSEvents::ESC_KEY;
    } else if(strcmp(valueNative, "EQUIP_GRENADE") == 0) {
        eventParam = sixenseUtils::FPSEvents::EQUIP_GRENADE;
    } else if(strcmp(valueNative, "MEDPACK_SWITCH") == 0) {
        eventParam = sixenseUtils::FPSEvents::MEDPACK_SWITCH;
    } else if(strcmp(valueNative, "GIVE") == 0) {
        eventParam = sixenseUtils::FPSEvents::GIVE;
    } else if(strcmp(valueNative, "NEXT_PRIMARY_WEAPON") == 0) {
        eventParam = sixenseUtils::FPSEvents::NEXT_PRIMARY_WEAPON;
    } else if(strcmp(valueNative, "ONE_TO_ONE_CARRY") == 0) {
        eventParam = sixenseUtils::FPSEvents::ONE_TO_ONE_CARRY;
    } else if(strcmp(valueNative, "EQUIP_MELEE") == 0) {
        eventParam = sixenseUtils::FPSEvents::EQUIP_MELEE;
    } else if(strcmp(valueNative, "EQUIP_MACHINEGUN") == 0) {
        eventParam = sixenseUtils::FPSEvents::EQUIP_MACHINEGUN;
    } else if(strcmp(valueNative, "EQUIP_PISTOL") == 0) {
        eventParam = sixenseUtils::FPSEvents::EQUIP_PISTOL;
    } else if(strcmp(valueNative, "RATCHET") == 0) {
        eventParam = sixenseUtils::FPSEvents::RATCHET;
    } else {
        eventParam = sixenseUtils::FPSEvents::LAST_FPS_EVENT;
    }

	sixenseUtils::FPSEvents::fps_controller controllerParam;
    jclass enumClass = env->FindClass("com/sixense/utils/enums/EnumController");
    if(enumClass == NULL) return;
    jmethodID getNameMethod = env->GetMethodID(enumClass, "name", "()Ljava/lang/String;");
    if(getNameMethod == NULL) return;
    jstring value = (jstring) env->CallObjectMethod(controllerRef, getNameMethod);
    const char* valueNative = env->GetStringUTFChars(value, JNI_FALSE);
    if(strcmp(valueNative, "LEFT") == 0) {
        controllerParam = sixenseUtils::FPSEvents::CONTROLLER_LEFT;
    } else if(strcmp(valueNative, "RIGHT") == 0) {
        controllerParam = sixenseUtils::FPSEvents::CONTROLLER_RIGHT;
    } else {
        controllerParam = sixenseUtils::FPSEvents::CONTROLLER_LEFT;
    }

	sixenseUtils::FPSEvents::fps_action actionParam;
	jclass enumClass = env->FindClass("com/sixense/utils/enums/EnumActionType");
    if(enumClass == NULL) return;
    jmethodID getNameMethod = env->GetMethodID(enumClass, "name", "()Ljava/lang/String;");
    if(getNameMethod == NULL) return;
    jstring value = (jstring) env->CallObjectMethod(actionRef, getNameMethod);
    const char* valueNative = env->GetStringUTFChars(value, JNI_FALSE);
    if(strcmp(valueNative, "BUTTON_PRESS") == 0) {
        actionParam = sixenseUtils::FPSEvents::ACTION_BUTTON_PRESS;
    } else if(strcmp(valueNative, "JOYSTICK_MOVE") == 0) {
        actionParam = sixenseUtils::FPSEvents::ACTION_JOYSTICK_MOVE;
    } else if(strcmp(valueNative, "TRIGGER_PRESS") == 0) {
        actionParam = sixenseUtils::FPSEvents::ACTION_TRIGGER_PRESS;
    } else if(strcmp(valueNative, "TILT_GESTURE") == 0) {
        actionParam = sixenseUtils::FPSEvents::ACTION_TILT_GESTURE;
    } else if(strcmp(valueNative, "POINT_GESTURE") == 0) {
        actionParam = sixenseUtils::FPSEvents::ACTION_POINT_GESTURE;
    } else if(strcmp(valueNative, "VELOCITY_GESTURE") == 0) {
        actionParam = sixenseUtils::FPSEvents::ACTION_VELOCITY_GESTURE;
    } else {
		actionParam = sixenseUtils::FPSEvents::ACTION_BUTTON_PRESS;
	}

    events->setBinding(eventParam, controllerParam, actionParam, param);
    return;
}

JNIEXPORT void JNICALL Java_com_sixense_utils_Events_setPointGestureButton(JNIEnv *env, jobject self, jint i) {
	jfieldID fid = getPeerID(env, self);
    sixenseUtils::FPSEvents * events = (sixenseUtils::FPSEvents *)env->GetLongField(self, fid);
	events->setPointGestureButton(i);
	return;
}

JNIEXPORT jboolean JNICALL Java_com_sixense_utils_Events_isPointGestureActive(JNIEnv *env, jobject self) {
	jfieldID fid = getPeerID(env, self);
    sixenseUtils::FPSEvents * events = (sixenseUtils::FPSEvents *)env->GetLongField(self, fid);
	return events->isPointGestureActive();
}

JNIEXPORT jboolean JNICALL Java_com_sixense_utils_Events_update(JNIEnv *env, jobject self, jobject leftRef, jobject rightRef, jfloat flo) {
	jfieldID fid = getPeerID(env, self);
    sixenseUtils::FPSEvents * events = (sixenseUtils::FPSEvents *)env->GetLongField(self, fid);
	sixenseControllerData * leftData = getControllerData(env, leftRef);
    sixenseControllerData * rightData = getControllerData(env, rightRef);
    return events->update(leftData, rightData, flo) == SIXENSE_SUCCESS ? JNI_TRUE : JNI_FALSE;
}

JNIEXPORT jboolean JNICALL Java_com_sixense_utils_Events_eventActive(JNIEnv *env, jobject self, jobject eventRef) {
	jfieldID fid = getPeerID(env, self);
    sixenseUtils::FPSEvents * events = (sixenseUtils::FPSEvents *)env->GetLongField(self, fid);

	sixenseUtils::FPSEvents::fps_event eventParam;
    jclass enumClass = env->FindClass("com/sixense/utils/enums/EnumEvent");
    if(enumClass == NULL) return;
    jmethodID getNameMethod = env->GetMethodID(enumClass, "name", "()Ljava/lang/String;");
    if(getNameMethod == NULL) return;
    jstring value = (jstring) env->CallObjectMethod(eventRef, getNameMethod);
    const char* valueNative = env->GetStringUTFChars(value, JNI_FALSE);
    if(strcmp(valueNative, "WALK_LEFT") == 0) {
        eventParam = sixenseUtils::FPSEvents::WALK_LEFT;
    } else if(strcmp(valueNative, "WALK_RIGHT") == 0) {
        eventParam = sixenseUtils::FPSEvents::WALK_RIGHT;
    } else if(strcmp(valueNative, "WALK_FORWARD") == 0) {
        eventParam = sixenseUtils::FPSEvents::WALK_FORWARD;
    } else if(strcmp(valueNative, "WALK_BACK") == 0) {
        eventParam = sixenseUtils::FPSEvents::WALK_BACK;
    } else if(strcmp(valueNative, "JUMP") == 0) {
        eventParam = sixenseUtils::FPSEvents::JUMP;
    } else if(strcmp(valueNative, "USE") == 0) {
        eventParam = sixenseUtils::FPSEvents::USE;
    } else if(strcmp(valueNative, "PRIMARY_FIRE") == 0) {
        eventParam = sixenseUtils::FPSEvents::PRIMARY_FIRE;
    } else if(strcmp(valueNative, "SECONDARY_FIRE") == 0) {
        eventParam = sixenseUtils::FPSEvents::SECONDARY_FIRE;
    } else if(strcmp(valueNative, "ZOOM") == 0) {
        eventParam = sixenseUtils::FPSEvents::ZOOM;
    } else if(strcmp(valueNative, "MELEE") == 0) {
        eventParam = sixenseUtils::FPSEvents::MELEE;
    } else if(strcmp(valueNative, "LEAN_LEFT") == 0) {
        eventParam = sixenseUtils::FPSEvents::LEAN_LEFT;
    } else if(strcmp(valueNative, "LEAN_RIGHT") == 0) {
        eventParam = sixenseUtils::FPSEvents::LEAN_RIGHT;
    } else if(strcmp(valueNative, "CROUCH") == 0) {
        eventParam = sixenseUtils::FPSEvents::CROUCH;
    } else if(strcmp(valueNative, "SPRINT") == 0) {
        eventParam = sixenseUtils::FPSEvents::SPRINT;
    } else if(strcmp(valueNative, "THROW_GRENADE") == 0) {
        eventParam = sixenseUtils::FPSEvents::THROW_GRENADE;
    } else if(strcmp(valueNative, "FLASHLIGHT") == 0) {
        eventParam = sixenseUtils::FPSEvents::FLASHLIGHT;
    } else if(strcmp(valueNative, "NIGHTVISION") == 0) {
        eventParam = sixenseUtils::FPSEvents::NIGHTVISION;
    } else if(strcmp(valueNative, "RELOAD") == 0) {
        eventParam = sixenseUtils::FPSEvents::RELOAD;
    } else if(strcmp(valueNative, "NEXT_WEAPON") == 0) {
        eventParam = sixenseUtils::FPSEvents::NEXT_WEAPON;
    } else if(strcmp(valueNative, "PREV_WEAPON") == 0) {
        eventParam = sixenseUtils::FPSEvents::PREV_WEAPON;
    } else if(strcmp(valueNative, "ESC_KEY") == 0) {
        eventParam = sixenseUtils::FPSEvents::ESC_KEY;
    } else if(strcmp(valueNative, "EQUIP_GRENADE") == 0) {
        eventParam = sixenseUtils::FPSEvents::EQUIP_GRENADE;
    } else if(strcmp(valueNative, "MEDPACK_SWITCH") == 0) {
        eventParam = sixenseUtils::FPSEvents::MEDPACK_SWITCH;
    } else if(strcmp(valueNative, "GIVE") == 0) {
        eventParam = sixenseUtils::FPSEvents::GIVE;
    } else if(strcmp(valueNative, "NEXT_PRIMARY_WEAPON") == 0) {
        eventParam = sixenseUtils::FPSEvents::NEXT_PRIMARY_WEAPON;
    } else if(strcmp(valueNative, "ONE_TO_ONE_CARRY") == 0) {
        eventParam = sixenseUtils::FPSEvents::ONE_TO_ONE_CARRY;
    } else if(strcmp(valueNative, "EQUIP_MELEE") == 0) {
        eventParam = sixenseUtils::FPSEvents::EQUIP_MELEE;
    } else if(strcmp(valueNative, "EQUIP_MACHINEGUN") == 0) {
        eventParam = sixenseUtils::FPSEvents::EQUIP_MACHINEGUN;
    } else if(strcmp(valueNative, "EQUIP_PISTOL") == 0) {
        eventParam = sixenseUtils::FPSEvents::EQUIP_PISTOL;
    } else if(strcmp(valueNative, "RATCHET") == 0) {
        eventParam = sixenseUtils::FPSEvents::RATCHET;
    } else if(strcmp(valueNative, "LAST_EVENT") == 0) {
        eventParam = sixenseUtils::FPSEvents::LAST_FPS_EVENT;
    } else {
        eventParam = sixenseUtils::FPSEvents::LAST_FPS_EVENT;
    }

	return events->eventActive(eventParam);
}

JNIEXPORT jboolean JNICALL Java_com_sixense_utils_Events_eventStarted(JNIEnv *env, jobject self, jobject eventRef) {
	jfieldID fid = getPeerID(env, self);
    sixenseUtils::FPSEvents * events = (sixenseUtils::FPSEvents *)env->GetLongField(self, fid);

	sixenseUtils::FPSEvents::fps_event eventParam;
    jclass enumClass = env->FindClass("com/sixense/utils/enums/EnumEvent");
    if(enumClass == NULL) return;
    jmethodID getNameMethod = env->GetMethodID(enumClass, "name", "()Ljava/lang/String;");
    if(getNameMethod == NULL) return;
    jstring value = (jstring) env->CallObjectMethod(eventRef, getNameMethod);
    const char* valueNative = env->GetStringUTFChars(value, JNI_FALSE);
    if(strcmp(valueNative, "WALK_LEFT") == 0) {
        eventParam = sixenseUtils::FPSEvents::WALK_LEFT;
    } else if(strcmp(valueNative, "WALK_RIGHT") == 0) {
        eventParam = sixenseUtils::FPSEvents::WALK_RIGHT;
    } else if(strcmp(valueNative, "WALK_FORWARD") == 0) {
        eventParam = sixenseUtils::FPSEvents::WALK_FORWARD;
    } else if(strcmp(valueNative, "WALK_BACK") == 0) {
        eventParam = sixenseUtils::FPSEvents::WALK_BACK;
    } else if(strcmp(valueNative, "JUMP") == 0) {
        eventParam = sixenseUtils::FPSEvents::JUMP;
    } else if(strcmp(valueNative, "USE") == 0) {
        eventParam = sixenseUtils::FPSEvents::USE;
    } else if(strcmp(valueNative, "PRIMARY_FIRE") == 0) {
        eventParam = sixenseUtils::FPSEvents::PRIMARY_FIRE;
    } else if(strcmp(valueNative, "SECONDARY_FIRE") == 0) {
        eventParam = sixenseUtils::FPSEvents::SECONDARY_FIRE;
    } else if(strcmp(valueNative, "ZOOM") == 0) {
        eventParam = sixenseUtils::FPSEvents::ZOOM;
    } else if(strcmp(valueNative, "MELEE") == 0) {
        eventParam = sixenseUtils::FPSEvents::MELEE;
    } else if(strcmp(valueNative, "LEAN_LEFT") == 0) {
        eventParam = sixenseUtils::FPSEvents::LEAN_LEFT;
    } else if(strcmp(valueNative, "LEAN_RIGHT") == 0) {
        eventParam = sixenseUtils::FPSEvents::LEAN_RIGHT;
    } else if(strcmp(valueNative, "CROUCH") == 0) {
        eventParam = sixenseUtils::FPSEvents::CROUCH;
    } else if(strcmp(valueNative, "SPRINT") == 0) {
        eventParam = sixenseUtils::FPSEvents::SPRINT;
    } else if(strcmp(valueNative, "THROW_GRENADE") == 0) {
        eventParam = sixenseUtils::FPSEvents::THROW_GRENADE;
    } else if(strcmp(valueNative, "FLASHLIGHT") == 0) {
        eventParam = sixenseUtils::FPSEvents::FLASHLIGHT;
    } else if(strcmp(valueNative, "NIGHTVISION") == 0) {
        eventParam = sixenseUtils::FPSEvents::NIGHTVISION;
    } else if(strcmp(valueNative, "RELOAD") == 0) {
        eventParam = sixenseUtils::FPSEvents::RELOAD;
    } else if(strcmp(valueNative, "NEXT_WEAPON") == 0) {
        eventParam = sixenseUtils::FPSEvents::NEXT_WEAPON;
    } else if(strcmp(valueNative, "PREV_WEAPON") == 0) {
        eventParam = sixenseUtils::FPSEvents::PREV_WEAPON;
    } else if(strcmp(valueNative, "ESC_KEY") == 0) {
        eventParam = sixenseUtils::FPSEvents::ESC_KEY;
    } else if(strcmp(valueNative, "EQUIP_GRENADE") == 0) {
        eventParam = sixenseUtils::FPSEvents::EQUIP_GRENADE;
    } else if(strcmp(valueNative, "MEDPACK_SWITCH") == 0) {
        eventParam = sixenseUtils::FPSEvents::MEDPACK_SWITCH;
    } else if(strcmp(valueNative, "GIVE") == 0) {
        eventParam = sixenseUtils::FPSEvents::GIVE;
    } else if(strcmp(valueNative, "NEXT_PRIMARY_WEAPON") == 0) {
        eventParam = sixenseUtils::FPSEvents::NEXT_PRIMARY_WEAPON;
    } else if(strcmp(valueNative, "ONE_TO_ONE_CARRY") == 0) {
        eventParam = sixenseUtils::FPSEvents::ONE_TO_ONE_CARRY;
    } else if(strcmp(valueNative, "EQUIP_MELEE") == 0) {
        eventParam = sixenseUtils::FPSEvents::EQUIP_MELEE;
    } else if(strcmp(valueNative, "EQUIP_MACHINEGUN") == 0) {
        eventParam = sixenseUtils::FPSEvents::EQUIP_MACHINEGUN;
    } else if(strcmp(valueNative, "EQUIP_PISTOL") == 0) {
        eventParam = sixenseUtils::FPSEvents::EQUIP_PISTOL;
    } else if(strcmp(valueNative, "RATCHET") == 0) {
        eventParam = sixenseUtils::FPSEvents::RATCHET;
    } else if(strcmp(valueNative, "LAST_EVENT") == 0) {
        eventParam = sixenseUtils::FPSEvents::LAST_FPS_EVENT;
    } else {
        eventParam = sixenseUtils::FPSEvents::LAST_FPS_EVENT;
    }

	return events->eventStarted(eventParam);
}

JNIEXPORT jboolean JNICALL Java_com_sixense_utils_Events_eventStopped(JNIEnv *env, jobject self, jobject eventRef) {
	jfieldID fid = getPeerID(env, self);
    sixenseUtils::FPSEvents * events = (sixenseUtils::FPSEvents *)env->GetLongField(self, fid);

	sixenseUtils::FPSEvents::fps_event eventParam;
    jclass enumClass = env->FindClass("com/sixense/utils/enums/EnumEvent");
    if(enumClass == NULL) return;
    jmethodID getNameMethod = env->GetMethodID(enumClass, "name", "()Ljava/lang/String;");
    if(getNameMethod == NULL) return;
    jstring value = (jstring) env->CallObjectMethod(eventRef, getNameMethod);
    const char* valueNative = env->GetStringUTFChars(value, JNI_FALSE);
    if(strcmp(valueNative, "WALK_LEFT") == 0) {
        eventParam = sixenseUtils::FPSEvents::WALK_LEFT;
    } else if(strcmp(valueNative, "WALK_RIGHT") == 0) {
        eventParam = sixenseUtils::FPSEvents::WALK_RIGHT;
    } else if(strcmp(valueNative, "WALK_FORWARD") == 0) {
        eventParam = sixenseUtils::FPSEvents::WALK_FORWARD;
    } else if(strcmp(valueNative, "WALK_BACK") == 0) {
        eventParam = sixenseUtils::FPSEvents::WALK_BACK;
    } else if(strcmp(valueNative, "JUMP") == 0) {
        eventParam = sixenseUtils::FPSEvents::JUMP;
    } else if(strcmp(valueNative, "USE") == 0) {
        eventParam = sixenseUtils::FPSEvents::USE;
    } else if(strcmp(valueNative, "PRIMARY_FIRE") == 0) {
        eventParam = sixenseUtils::FPSEvents::PRIMARY_FIRE;
    } else if(strcmp(valueNative, "SECONDARY_FIRE") == 0) {
        eventParam = sixenseUtils::FPSEvents::SECONDARY_FIRE;
    } else if(strcmp(valueNative, "ZOOM") == 0) {
        eventParam = sixenseUtils::FPSEvents::ZOOM;
    } else if(strcmp(valueNative, "MELEE") == 0) {
        eventParam = sixenseUtils::FPSEvents::MELEE;
    } else if(strcmp(valueNative, "LEAN_LEFT") == 0) {
        eventParam = sixenseUtils::FPSEvents::LEAN_LEFT;
    } else if(strcmp(valueNative, "LEAN_RIGHT") == 0) {
        eventParam = sixenseUtils::FPSEvents::LEAN_RIGHT;
    } else if(strcmp(valueNative, "CROUCH") == 0) {
        eventParam = sixenseUtils::FPSEvents::CROUCH;
    } else if(strcmp(valueNative, "SPRINT") == 0) {
        eventParam = sixenseUtils::FPSEvents::SPRINT;
    } else if(strcmp(valueNative, "THROW_GRENADE") == 0) {
        eventParam = sixenseUtils::FPSEvents::THROW_GRENADE;
    } else if(strcmp(valueNative, "FLASHLIGHT") == 0) {
        eventParam = sixenseUtils::FPSEvents::FLASHLIGHT;
    } else if(strcmp(valueNative, "NIGHTVISION") == 0) {
        eventParam = sixenseUtils::FPSEvents::NIGHTVISION;
    } else if(strcmp(valueNative, "RELOAD") == 0) {
        eventParam = sixenseUtils::FPSEvents::RELOAD;
    } else if(strcmp(valueNative, "NEXT_WEAPON") == 0) {
        eventParam = sixenseUtils::FPSEvents::NEXT_WEAPON;
    } else if(strcmp(valueNative, "PREV_WEAPON") == 0) {
        eventParam = sixenseUtils::FPSEvents::PREV_WEAPON;
    } else if(strcmp(valueNative, "ESC_KEY") == 0) {
        eventParam = sixenseUtils::FPSEvents::ESC_KEY;
    } else if(strcmp(valueNative, "EQUIP_GRENADE") == 0) {
        eventParam = sixenseUtils::FPSEvents::EQUIP_GRENADE;
    } else if(strcmp(valueNative, "MEDPACK_SWITCH") == 0) {
        eventParam = sixenseUtils::FPSEvents::MEDPACK_SWITCH;
    } else if(strcmp(valueNative, "GIVE") == 0) {
        eventParam = sixenseUtils::FPSEvents::GIVE;
    } else if(strcmp(valueNative, "NEXT_PRIMARY_WEAPON") == 0) {
        eventParam = sixenseUtils::FPSEvents::NEXT_PRIMARY_WEAPON;
    } else if(strcmp(valueNative, "ONE_TO_ONE_CARRY") == 0) {
        eventParam = sixenseUtils::FPSEvents::ONE_TO_ONE_CARRY;
    } else if(strcmp(valueNative, "EQUIP_MELEE") == 0) {
        eventParam = sixenseUtils::FPSEvents::EQUIP_MELEE;
    } else if(strcmp(valueNative, "EQUIP_MACHINEGUN") == 0) {
        eventParam = sixenseUtils::FPSEvents::EQUIP_MACHINEGUN;
    } else if(strcmp(valueNative, "EQUIP_PISTOL") == 0) {
        eventParam = sixenseUtils::FPSEvents::EQUIP_PISTOL;
    } else if(strcmp(valueNative, "RATCHET") == 0) {
        eventParam = sixenseUtils::FPSEvents::RATCHET;
    } else if(strcmp(valueNative, "LAST_EVENT") == 0) {
        eventParam = sixenseUtils::FPSEvents::LAST_FPS_EVENT;
    } else {
        eventParam = sixenseUtils::FPSEvents::LAST_FPS_EVENT;
    }

	return events->eventStopped(eventParam);
}

JNIEXPORT jfloatArray JNICALL Java_com_sixense_utils_Events_getGrenadeThrowVelocity(JNIEnv *env, jobject self) {
	jfieldID fid = getPeerID(env, self);
    sixenseUtils::FPSEvents * events = (sixenseUtils::FPSEvents *)env->GetLongField(self, fid);

	sixenseMath::Vector3 vel = events->getGrenadeThrowVelocity();
	jfloatArray arr = env->NewFloatArray(3);
	env->SetFloatArrayRegion(arr, 0, 3, vec._vec);
	return arr;
}

JNIEXPORT void JNICALL Java_com_sixense_utils_Events_setParameter(JNIEnv *env, jobject self, jobject paramRef, jfloat val) {
	jfieldID fid = getPeerID(env, self);
    sixenseUtils::FPSEvents * events = (sixenseUtils::FPSEvents *)env->GetLongField(self, fid);

	sixenseUtils::FPSEvents::fps_params param;
	jclass enumClass = env->FindClass("com/sixense/utils/enums/EnumEventParam");
    if(enumClass == NULL) return;
    jmethodID getNameMethod = env->GetMethodID(enumClass, "name", "()Ljava/lang/String;");
    if(getNameMethod == NULL) return;
    jstring value = (jstring) env->CallObjectMethod(actionRef, getNameMethod);
    const char* valueNative = env->GetStringUTFChars(value, JNI_FALSE);
    if(strcmp(valueNative, "MELEE_SENSITIVITY") == 0) {
        param = sixenseUtils::FPSEvents::MELEE_SENSITIVITY;
    } else if(strcmp(valueNative, "WEAPON_SELECT_SENSITIVITY") == 0) {
        param = sixenseUtils::FPSEvents::WEAPON_SELECT_SENSITIVITY;
    } else if(strcmp(valueNative, "CROUCH_SENSITIVITY") == 0) {
        param = sixenseUtils::FPSEvents::CROUCH_SENSITIVITY;
    } else if(strcmp(valueNative, "JUMP_SENSITIVITY") == 0) {
        param = sixenseUtils::FPSEvents::JUMP_SENSITIVITY;
    } else if(strcmp(valueNative, "RELOAD_SENSITIVITY") == 0) {
        param = sixenseUtils::FPSEvents::RELOAD_SENSITIVITY;
    } else if(strcmp(valueNative, "THROW_SENSITIVITY") == 0) {
        param = sixenseUtils::FPSEvents::THROW_SENSITIVITY;
    } else if(strcmp(valueNative, "CONTROLLER_ANGLE_MODE") == 0) {
        param = sixenseUtils::FPSEvents::CONTROLLER_ANGLE_MODE;
    } else if(strcmp(valueNative, "AUTO_ONE_TO_ONE_START_VEL") == 0) {
        param = sixenseUtils::FPSEvents::AUTO_ONE_TO_ONE_START_VEL;
    } else if(strcmp(valueNative, "AUTO_ONE_TO_ONE_START_ACCEL") == 0) {
        param = sixenseUtils::FPSEvents::AUTO_ONE_TO_ONE_START_ACCEL;
    } else if(strcmp(valueNative, "AUTO_ONE_TO_ONE_START_ACCEL_TIMER") == 0) {
        param = sixenseUtils::FPSEvents::AUTO_ONE_TO_ONE_START_ACCEL_TIMER;
    } else if(strcmp(valueNative, "AUTO_ONE_TO_ONE_START_ANGLE_THRESH") == 0) {
        param = sixenseUtils::FPSEvents::AUTO_ONE_TO_ONE_START_ANGLE_THRESH;
    } else if(strcmp(valueNative, "AUTO_ONE_TO_ONE_STOP_XY_DIST") == 0) {
        param = sixenseUtils::FPSEvents::AUTO_ONE_TO_ONE_STOP_XY_DIST;
    } else if(strcmp(valueNative, "AUTO_ONE_TO_ONE_STOP_Z_DIST") == 0) {
        param = sixenseUtils::FPSEvents::AUTO_ONE_TO_ONE_STOP_Z_DIST;
    } else if(strcmp(valueNative, "LEFT_HANDED") == 0) {
        param = sixenseUtils::FPSEvents::LEFT_HANDED;
    } else {
        param = sixenseUtils::FPSEvents::LAST_FPS_EVENTS_PARAM;
    }

	events->setParameter(param, val);
	return;
}

JNIEXPORT jfloat JNICALL Java_com_sixense_utils_Events_getParameter(JNIEnv *env, jobject self, jobject paramRef) {
	jfieldID fid = getPeerID(env, self);
    sixenseUtils::FPSEvents * events = (sixenseUtils::FPSEvents *)env->GetLongField(self, fid);

	sixenseUtils::FPSEvents::fps_params param;
	jclass enumClass = env->FindClass("com/sixense/utils/enums/EnumEventParam");
    if(enumClass == NULL) return;
    jmethodID getNameMethod = env->GetMethodID(enumClass, "name", "()Ljava/lang/String;");
    if(getNameMethod == NULL) return;
    jstring value = (jstring) env->CallObjectMethod(actionRef, getNameMethod);
    const char* valueNative = env->GetStringUTFChars(value, JNI_FALSE);
    if(strcmp(valueNative, "MELEE_SENSITIVITY") == 0) {
        param = sixenseUtils::FPSEvents::MELEE_SENSITIVITY;
    } else if(strcmp(valueNative, "WEAPON_SELECT_SENSITIVITY") == 0) {
        param = sixenseUtils::FPSEvents::WEAPON_SELECT_SENSITIVITY;
    } else if(strcmp(valueNative, "CROUCH_SENSITIVITY") == 0) {
        param = sixenseUtils::FPSEvents::CROUCH_SENSITIVITY;
    } else if(strcmp(valueNative, "JUMP_SENSITIVITY") == 0) {
        param = sixenseUtils::FPSEvents::JUMP_SENSITIVITY;
    } else if(strcmp(valueNative, "RELOAD_SENSITIVITY") == 0) {
        param = sixenseUtils::FPSEvents::RELOAD_SENSITIVITY;
    } else if(strcmp(valueNative, "THROW_SENSITIVITY") == 0) {
        param = sixenseUtils::FPSEvents::THROW_SENSITIVITY;
    } else if(strcmp(valueNative, "CONTROLLER_ANGLE_MODE") == 0) {
        param = sixenseUtils::FPSEvents::CONTROLLER_ANGLE_MODE;
    } else if(strcmp(valueNative, "AUTO_ONE_TO_ONE_START_VEL") == 0) {
        param = sixenseUtils::FPSEvents::AUTO_ONE_TO_ONE_START_VEL;
    } else if(strcmp(valueNative, "AUTO_ONE_TO_ONE_START_ACCEL") == 0) {
        param = sixenseUtils::FPSEvents::AUTO_ONE_TO_ONE_START_ACCEL;
    } else if(strcmp(valueNative, "AUTO_ONE_TO_ONE_START_ACCEL_TIMER") == 0) {
        param = sixenseUtils::FPSEvents::AUTO_ONE_TO_ONE_START_ACCEL_TIMER;
    } else if(strcmp(valueNative, "AUTO_ONE_TO_ONE_START_ANGLE_THRESH") == 0) {
        param = sixenseUtils::FPSEvents::AUTO_ONE_TO_ONE_START_ANGLE_THRESH;
    } else if(strcmp(valueNative, "AUTO_ONE_TO_ONE_STOP_XY_DIST") == 0) {
        param = sixenseUtils::FPSEvents::AUTO_ONE_TO_ONE_STOP_XY_DIST;
    } else if(strcmp(valueNative, "AUTO_ONE_TO_ONE_STOP_Z_DIST") == 0) {
        param = sixenseUtils::FPSEvents::AUTO_ONE_TO_ONE_STOP_Z_DIST;
    } else if(strcmp(valueNative, "LEFT_HANDED") == 0) {
        param = sixenseUtils::FPSEvents::LEFT_HANDED;
    } else {
        param = sixenseUtils::FPSEvents::LAST_FPS_EVENTS_PARAM;
    }

	return events->getParameter(param, val);
}
