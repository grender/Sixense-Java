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

package com.sixense;
import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.IOException;

/**
 * @author Gabriel Smith, Mark Browning
 */
public class Sixense {

	private static boolean libraryLoaded = false;

	public static boolean LoadLibrary( File nativeDir )
	{
		if( libraryLoaded ) return true;
		String os = System.getProperty("os.name");
		boolean is64bit = System.getProperty("sun.arch.data.model").equalsIgnoreCase("64"); 
		String[] libs = null;
		String zipDir = "";

        if ( os.contains("Win") )
        {
			zipDir = "windows";
			if( is64bit )
				libs = new String[]{ "SixenseJava64.dll","sixense_x64.dll","sixense_utils_x64.dll" };
			else
				libs = new String[]{ "SixenseJava32.dll","sixense.dll","sixense_utils.dll" };
			
		}
		else if (os.contains("Mac") )
		{
			zipDir = "osx";
			if( is64bit )
				libs = new String[]{ "libSixenseJava64.jnilib","libsixense_x64.dylib", "libsixense_utils_x64.dylib" };
			else
				libs = new String[]{ "libSixenseJava32.jnilib","libsixense.dylib", "libsixense_utils.dylib"  };
        }
        else if (os.contains("Linux") )
        {
			zipDir = "linux";
			if( is64bit )
				libs = new String[]{ "libSixenseJava64.so","libsixense_x64.so", "libsixense_utils_x64.so" };
			else
				libs = new String[]{ "libSixenseJava32.so","libsixense.so", "libsixense_utils.so"  };
        }
		else
		{
            System.out.println("Operating System not supported: " + os );
		}

		try 
		{
			System.out.println("Extracting libs to: "+nativeDir+". java.library.path: "+System.getProperty("java.library.path"));
			for( String libName : libs )
			{
				System.out.println("Loading jar:/"+libName+" ... ");
				InputStream libStream = Sixense.class.getResourceAsStream( "/" + zipDir + "/" +libName );
				if( libStream != null )
				{
					byte[] buffer = new byte[1024];
					int len = libStream.read(buffer);
					File outFile = new File( nativeDir, libName );
					OutputStream out = new FileOutputStream( outFile );

					while (len != -1) 
					{
						out.write(buffer, 0, len);
						len = libStream.read(buffer);
					}
					out.close();
				}
				else
				{
					System.err.println("Couldn't open "+libName+" from jar file! Are you using a strange classloader?");
				}
			}

			if( is64bit )
			{
				System.loadLibrary("sixense_x64");
				System.loadLibrary("sixense_utils_x64");
				System.loadLibrary( "SixenseJava64" );
			}
			else
			{
				System.loadLibrary("sixense");
				System.loadLibrary("sixense_utils");
				System.loadLibrary( "SixenseJava32" );
			}

			libraryLoaded = true;

			System.out.println( "SixenseJava loaded");
		} 
		catch( Exception e ) 
		{ 
			System.out.println( e.toString() );
			System.out.println( "Couldn't load SixenseJava... :(" );
		}
		return libraryLoaded;
    }

    /**
     * Initializes the Sixense library. It must be called at least one time per
     * application. Subsequent calls will have no effect. Once initialized, the
     * other Sixense function calls will work as described until
     * <code>Sixense.exit()</code> is called.
     *
     * @return true on success, false on failure
     */
    public static native boolean init();

    /**
     * Shuts down the Sixense library. After this method call, all Sixense API
     * calls will return failure until
     * <code>Sixense.init()</code> is called again.
     *
     * @return true on success, false on failure
     */
    public static native boolean exit();

    /**
     * Gets the maximum number of base units supported by the Sixense control
     * system.
     *
     * @return number of bases supported.
     */
    public static native int getMaxBases();

    /**
     * Designates which base subsequent API calls are to be directed to.
     *
     * @param base_num an integer from <code>0</code> *
     * to <code>Sixense.getMaxBases()-1</code>
     * @return true on success, false on failure
     */
    public static native boolean setActiveBase(int base_num);

    /**
     * Determines if a base is currently connected to the system.
     *
     * @param base_num an integer from <code>0</code> *
     * to <code>Sixense.getMaxBases()-1</code>
     * @return true if connected, false otherwise
     */
    public static native boolean isBaseConnected(int base_num);

    /**
     * Returns the maximum number of controllers supported by the Sixense
     * control system.
     *
     * @return the number of controllers supported
     */
    public static native int getMaxControllers();

    /**
     * Returns the number of active controllers.
     *
     * @return the number of controllers linked to the base unit
     */
    public static native int getNumActiveControllers();

    /**
     * Returns true if the referenced controller is currently connected to the
     * Base Unit.
     *
     * @param controller_id an integer from 0 *
     * to <code>Sixense.getMaxControllers()</code>-1
     * @return true if connected, otherwise false
     */
    public static native boolean isControllerEnabled(int controller_id);

    /**
     * Gets the most recent state of all of the controllers.
     *
     * @param all_data an initialized ControllerData[4] that the controller data
     * will be put in
     * @return true on as long as the system has been initialized, otherwise
     * false
     */
    public static native boolean getAllNewestData(ControllerData[] all_data);

    /**
     * Gets state of all of the controllers, selecting how far back into a
     * history of the last 10 updates.
     *
     * @param index_back an integer from 0 to 9
     * @param all_data an initialized ControllerData[4] that the controller data
     * will be put in
     * @return true on as long as the system has been initialized, otherwise
     * false
     */
    public static native boolean getAllData(int index_back, ControllerData[] all_data);

    /**
     * Gets the most recent state of one of the controllers. If the desired
     * controller is not connected, an empty data packet is returned. Empty data
     * packets are initialized to a zero position and the identity rotation
     * matrix.
     *
     * @param controller_id an integer from 0 *
     * to <code>Sixense.getMaxControllers()</code>-1
     * @param data a ControllerData that the controller data will be put in
     * @return true on as long as the system has been initialized, false if the
     * controller is not connected
     */
    public static native boolean getNewestData(int controller_id, ControllerData data);

    /**
     * Gets state of one of the controllers, selecting how far back into a
     * history of the last 10 updates. If the desired controller is not
     * connected, an empty data packet is returned. Empty data packets are
     * initialized to a zero position and the identity rotation matrix.
     *
     * @param controller_id an integer from 0 *
     * to <code>Sixense.getMaxControllers()</code>-1
     * @param index_back an integer from 0 to 9
     * @param data a ControllerData that the controller data will be put in
     * @return true on as long as the system has been initialized, false if the
     * controller is not connected
     */
    public static native boolean getData(int controller_id, int index_back, ControllerData data);

    /**
     * Gets the size of the history buffer.
     *
     * @return the size of the history buffer
     */
    public static native int getHistorySize();

    /**
     * Sets the internal position and orientation filtering on or off.
     *
     * @param on_or_off true to enable, false to disable
     * @return true on as long as the system has been initialized, otherwise
     * false
     */
    public static native boolean setFilterEnabled(boolean on_or_off);

    /**
     * Returns the enable status of the internal position and orientation
     * filtering.
     *
     * @return true if enabled, false if disabled
     */
    public static native boolean getFilterEnabled();

    /**
     * Sets the parameters that control the position and orientation filtering
     * level.
     *
     * @param params
     * @return true on as long as the system has been initialized, otherwise
     * false
     */
    public static boolean setFilterParams(float[] params) {
        return setFilterParams(params[0], params[1], params[2], params[3]);
    }

    /**
     * Sets the parameters that control the position and orientation filtering
     * level.
     *
     * @param near_range
     * @param near_val
     * @param far_range
     * @param far_val
     * @return true on as long as the system has been initialized, otherwise
     * false
     */
    public static native boolean setFilterParams(float near_range, float near_val, float far_range, float far_val);

    /**
     * Gets the current filtering parameter values.
     *
     * @return current filter parameters
     */
    public static native float[] getFilterParams();

    /**
     * Enables a period of tactile feedback using the vibration motor. Note the
     * Razer Hydra does not support vibration.
     *
     * @param controller_id an integer from 0 *
     * to <code>Sixense.getMaxControllers()</code>-1
     * @param duration the duration of the vibration, in 100 millisecond units
     * @param pattern_id this argument is ignored and the vibration motor is
     * engaged for the full duration
     * @return true on as long as the system has been initialized, otherwise
     * false
     */
    public static native boolean triggerVibration(int controller_id, int duration, int pattern_id);

    /**
     * Enables Hemisphere Tracking when the controller is aiming at the base.
     * This call is deprecieated, as hemisphere tracking is automatically
     * enabled when the controllers are in the dock or by the
     * <code>sixense.utils.ControllerManager</code>. See the Sixense API
     * Overivew for more information.
     *
     * @param controller_id this argument is ignored and the vibration motor is
     * engaged for the full duration
     * @return true on as long as the system has been initialized, otherwise
     * false
     * @deprecated com.sixense.utils.ControllerManager
     */
    public static native boolean autoEnableHemisphereTracking(int controller_id);

    /**
     * Sets High Priority RF binding mode. This call is only used with the
     * wireless Sixense devkits.
     *
     * @param on_or_off true to enable, false to disable
     * @return true on as long as the system has been initialized, otherwise
     * false
     */
    public static native boolean setHighPriorityBinding(boolean on_or_off);

    /**
     * Gets the current state of High Priority RF binding mode. This call is
     * only used with the wireless Sixense devkits.
     *
     * @return true if enabled, false if disabled
     */
    public static native boolean getHighPriorityBinding();

    /**
     * Gets the color of the LED on the Sixense wireless devkits. Each value is
     * between 0 and 255, 0 is off and 255 is fully on.
     *
     * @param colors
     * @return true on as long as the system has been initialized, otherwise
     * false
     */
    public static boolean setBaseColor(int[] colors) {
        return setBaseColor(colors[0], colors[1], colors[2]);
    }

    /**
     * Gets the color of the LED on the Sixense wireless devkits. Each value is
     * between 0 and 255, 0 is off and 255 is fully on.
     *
     * @param red the red component of the led color
     * @param green the green component of the led color
     * @param blue the blue component of the led color
     * @return true on as long as the system has been initialized, otherwise
     * false
     */
    public static native boolean setBaseColor(int red, int green, int blue);

    /**
     * Gets the color of the LED on the Sixense wireless devkits.
     *
     * @return the color values
     */
    public static native int[] getColorBase();
}
