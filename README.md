Sixense-Java
============

	A Java wrapper for the Sixense dynamic libraries

License
============

   Copyright © 2013 Sixense Java Contributors

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

Building:
========

SixenseSDK REQUIRED. Download [here](http://sixense.com/windowssdkdownload)(for
all platforms, even though link says windows). Modify SDK location in Makefile.
jdk required for building JNI libraries.

Makefile controls Unix builds & java/jar build.
 - make all -> build native libraries for current platform (Linux or OSX)
 - make jar -> builds java classes and copies classes,natives into jar

VS2010 Project in src/native/
