/*
* This file is part of Sixense Java.
*
* Copyright � 2012-2013, Sixense Java Contributors
* FTB Launcher is licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include "sixense_java_utils.h"
#include "sixense_math.hpp"
#include "laser_pointer.hpp"
#include "com_sixense_utils_LaserPointer.h"

using sixenseMath::Vector2;
using sixenseMath::Vector3;
using sixenseMath::Matrix3;
using sixenseUtils::LaserPointer;
using sixenseUtils::LaserPointerCalib;

JNIEXPORT jlong JNICALL Java_com_sixense_utils_LaserPointer_create(JNIEnv *, jobject) {
    LaserPointer * laser = new LaserPointer();
    return (jlong) laser;
}

JNIEXPORT void JNICALL Java_com_sixense_utils_LaserPointer_destroy(JNIEnv *env, jobject self) {
    jfieldID fid = getPeerID(env, self);
    jlong peer = env->GetLongField(self, fid);
    if(peer == 0) {
        return;
    }
    free((void *) peer);
    return;
}

JNIEXPORT void JNICALL Java_com_sixense_utils_LaserPointer_setScreenSize(JNIEnv *env, jobject self, jfloat width, jfloat height) {
	jfieldID fid = getPeerID(env, self);
	LaserPointer * laser = (LaserPointer *)env->GetLongField(self, fid);
	laser->setScreenSize(Vector2(width, height));
}

JNIEXPORT void JNICALL Java_com_sixense_utils_LaserPointer_setScreenCenterOffset(JNIEnv *env, jobject self, jfloat x, jfloat y, jfloat z) {
	jfieldID fid = getPeerID(env, self);
	LaserPointer * laser = (LaserPointer *)env->GetLongField(self, fid);
	laser->setScreenCenterOffsetFromBase(Vector3(x, y, z));
}

JNIEXPORT jfloatArray JNICALL Java_com_sixense_utils_LaserPointer_getScreenSize(JNIEnv *env, jobject self) {
	jfieldID fid = getPeerID(env, self);
	LaserPointer * laser = (LaserPointer *)env->GetLongField(self, fid);
	jfloatArray size = env->NewFloatArray(2);
	Vector2 size2 = laser->getScreenSize();
	jfloat size3[2] = {size2[0], size2[1]};
    env->SetFloatArrayRegion(size, 0, 2, size3);
	return size;
}

JNIEXPORT jfloatArray JNICALL Java_com_sixense_utils_LaserPointer_getScreenCenterOffset(JNIEnv *env, jobject self) {
	jfieldID fid = getPeerID(env, self);
	LaserPointer * laser = (LaserPointer *)env->GetLongField(self, fid);
	jfloatArray offset = env->NewFloatArray(3);
	Vector3 offset2 = laser->getScreenCenterOffsetFromBase();
	jfloat offset3[3] = {offset2[0], offset2[1], offset2[2]};
    env->SetFloatArrayRegion(offset, 0, 3, offset3);
	return offset;
}

JNIEXPORT jfloatArray JNICALL Java_com_sixense_utils_LaserPointer_getIntersection(JNIEnv *env, jobject self, jfloat x, jfloat y, jfloat z, jfloat _00, jfloat _01, jfloat _02, jfloat _10, jfloat _11, jfloat _12, jfloat _20, jfloat _21, jfloat _22) {
	jfieldID fid = getPeerID(env, self);
	LaserPointer * laser = (LaserPointer *)env->GetLongField(self, fid);
	jfloatArray inter = env->NewFloatArray(2);
	Vector2 inter2 = laser->getIntersection(Vector3(x, y, z), Matrix3(_00,  _01,  _02,  _10,  _11,  _12,  _20,  _21,  _22));
	jfloat inter3[2] = {inter2[0], inter2[1]};
    env->SetFloatArrayRegion(inter, 0, 2, inter3);
	return inter;
}
/*
JNIEXPORT jboolean JNICALL Java_com_sixense_utils_LaserPointer_compute1
  (JNIEnv *env, jobject self, jfloat bla1,jfloat bla2,jfloat bla3, jfloat tra1, jfloat tra2, jfloat tra3,jfloat blb1,jfloat blb2,jfloat blb3, jfloat trb1, jfloat trb2, jfloat trb3) {
	jfieldID fid = getPeerID(env, self);
	LaserPointer * laser = (LaserPointer *)env->GetLongField(self, fid);
	LaserPointerCalib* calib=new LaserPointerCalib();

	bool result = calib->compute(Vector3(bla1,bla2,bla3),Vector3(tra1,tra2,tra3),Vector3(blb1,blb2,blb3), Vector3(trb1,trb2,trb3));
	
	laser->setScreenSize(calib->getScrenSize());
	laser->setScreenCenterOffsetFromBase(calib->setScreenCenterOffsetFromBase());
	delete calib;

	return result ? JNI_TRUE : JNI_FALSE;
}
  
JNIEXPORT jboolean JNICALL Java_com_sixense_utils_LaserPointer_compute2
  (JNIEnv *env, jobject self, jfloat width, jfloat aspect, jfloat bl1,jfloat bl2,jfloat bl3, jfloat tr1, jfloat tr2, jfloat tr3) {
	jfieldID fid = getPeerID(env, self);
	LaserPointer * laser = (LaserPointer *)env->GetLongField(self, fid);
	LaserPointerCalib* calib=new LaserPointerCalib();
	bool result = calib->compute(width,aspect,Vector3(bl1,bl2,bl3),Vector3(tr1,tr2,tr3));
	
	laser->setScreenSize(calib->getScrenSize());
	laser->setScreenCenterOffsetFromBase(calib->setScreenCenterOffsetFromBase());
	delete calib;
	
	return result ? JNI_TRUE : JNI_FALSE;
}
*/