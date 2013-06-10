Sixense-Java
============

A Java wrapper for the Sixense dynamic libraries.

Building:
========

SixenseSDK REQUIRED. Download [here](http://sixense.com/windowssdkdownload)(for
all platforms, even though link says windows). Modify SDK location in Makefile.
jdk required for building JNI libraries.

Makefile controls Unix builds & java/jar build.
 - make all -> build native libraries for current platform (Linux or OSX)
 - make jar -> builds java classes and copies classes,natives into jar

VS2010 Project in src/native/
