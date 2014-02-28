/*
* This file is part of Sixense Java.
*
* Copyright © 2012-2013, Sixense Java Contributors
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

package com.sixense.utils;

/*
 * @author Gabriel Smith
 * @depreciated Acording to Danny this utility was never finished and has been dropped.
 */
public class LaserPointer {
    private long peer;

    public LaserPointer() {
        peer = create();
    }

    @Override
    protected void finalize() {
        destroy();
        peer = 0;
    }

    private native long create();

    private synchronized native void destroy();

    /**
     *
     * @param width
     * @param height
     */
    public native void setScreenSize(float width, float height);

    /**
     *
     * @param x
     * @param y
     * @param z
     */
    public native void setScreenCenterOffset(float x, float y, float z);

    /**
     *
     * @return
     */
    public native float[] getScreenSize();

    /**
     *
     * @return
     */
    public native float[] getScreenCenterOffset();

    /**
     *
     * @param pos
     * @param rot
     * @return
     */
    public float[] getIntersection(float[] pos, float[][] rot) {
        return getIntersection(pos[0], pos[1], pos[2], rot[0][0], rot[0][1], rot[0][2], rot[1][0], rot[1][1], rot[1][2], rot[2][0], rot[2][1], rot[2][2]);
    }
    
    private native float[] getIntersection(float x, float y, float z, float _00, float _01, float _02, float _10, float _11, float _12, float _20, float _21, float _22);

    /**
     *
     * @param bottomLeftA
     * @param topRightA
     * @param bottomLeftB
     * @param topRightB
     * @return
     */
/*
    public boolean compute(float[] bottomLeftA, float[] topRightA, float[] bottomLeftB, float[] topRightB) {
	return compute(bottomLeftA[0],bottomLeftA[1],bottomLeftA[2],topRightA[0],topRightA[1],topRightA[2],bottomLeftB[0],bottomLeftB[1],bottomLeftB[2],topRightB[0],topRightB[1],topRightB[2]);
    }

    public native boolean compute(float bla1,float bla2,float bla3, float tra1, float tra2, float tra3,float blb1,float blb2,float blb3, float trb1, float trb2, float trb3);
*/
    /**
     *
     * @param width
     * @param aspect
     * @param bottomLeft
     * @param topRight
     * @return
     */
/*
    public boolean compute(float width, float aspect, float[] bottomLeft, float[] topRight) {
	return compute(width, aspect, bottomLeft[0], bottomLeft[1],bottomLeft[2],topRight[0],topRight[1],topRight[2]);
    }

    public native boolean compute(float width, float aspect, float bl1,float bl2,float bl3, float tr1, float tr2, float tr3);
*/
}
