SixenseJava.jar: java
	cd dist/java; zip ../../SixenseJava.jar -r .
	cd native; zip ../SixenseJava.jar -r .

jar: SixenseJava.jar
java:
	@-mkdir -p dist/java 2>/dev/null;
	cd src/java; javac $(shell cd src/java; find . -name *java ) -d ../../dist/java;
.PHONY: clean all java jar


CXX = g++

SIXENSE=/home/mabrowning/MinecraftDev/Hydra/SixenseSDK_062612/
SIXENSE=../../SixenseSDK_062612/
CXXFLAGS = -g -fPIC -c -Wall -I$(SIXENSE)include/sixense_utils -I$(SIXENSE)include/sixense_utils/controller_manager -I$(SIXENSE)include
LDFLAGS = -shared -fPIC
SOURCES = com_sixense_Sixense.cpp sixense_java_utils.cpp Quat.cpp $(addprefix com_sixense_utils_,ButtonStates.cpp ControllerManager.cpp Derivatives.cpp Events.cpp PlayerMovement.cpp ViewAngles.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

UNAME:=$(shell uname)
ifeq ($(UNAME), Darwin)
CXXFLAGS+= -I/System/Library/Frameworks/JavaVM.framework/Versions/Current/Headers -I/Developer/SDKs/MacOSX10.6.sdk/System/Library/Frameworks/JavaVM.framework/Versions/A/Headers
LDFLAGS+=-Wl,-headerpad_max_install_names

all: libSixenseJava32.jnilib libSixenseJava64.jnilib

libSixenseJava32.jnilib: $(addprefix build/32/,$(OBJECTS))
	$(CXX) $(LDFLAGS) -m32 -o native/osx/$@ $^ -L$(SIXENSE)lib/osx/release_dll -lsixense -lsixense_utils
	install_name_tool -change /usr/local/lib/libsixense.dylib "@loader_path/libsixense.dylib" native/osx/$@
	install_name_tool -change /usr/local/lib/libsixense_utils.dylib "@loader_path/libsixense_utils.dylib" native/osx/$@

	install_name_tool -change /usr/local/lib/libsixense.dylib "@loader_path/libsixense.dylib" native/osx/libsixense.dylib
	install_name_tool -change /usr/local/lib/libsixense.dylib "@loader_path/libsixense.dylib" native/osx/libsixense_utils.dylib
	install_name_tool -change /usr/local/lib/libsixense_utils.dylib "@loader_path/libsixense_utils.dylib" native/osx/libsixense_utils.dylib

libSixenseJava64.jnilib: $(addprefix build/64/,$(OBJECTS))
	$(CXX) $(LDFLAGS) -m64 -o native/osx/$@ $^ -L$(SIXENSE)lib/osx_x64/release_dll -lsixense_x64 -lsixense_utils_x64
	install_name_tool -change /usr/local/lib/libsixense_x64.dylib "@loader_path/libsixense_x64.dylib" native/osx/$@
	install_name_tool -change /usr/local/lib/libsixense_utils_x64.dylib "@loader_path/libsixense_utils_x64.dylib" native/osx/$@
	install_name_tool -change /usr/local/lib/libsixense_x64.dylib "@loader_path/libsixense_x64.dylib" native/osx/libsixense_x64.dylib
	install_name_tool -change /usr/local/lib/libsixense_x64.dylib "@loader_path/libsixense_x64.dylib" native/osx/libsixense_utils_x64.dylib
	install_name_tool -change /usr/local/lib/libsixense_utils_x64.dylib "@loader_path/libsixense_utils_x64.dylib" native/osx/libsixense_utils_x64.dylib

else
ifeq ($(UNAME), Linux)
CXXFLAGS+= -I/usr/lib/jvm/java-6-openjdk-amd64/include -I/usr/lib/jvm/java-6-openjdk-amd64/include/linux 

LDFLAGS+= -Wl,-rpath,\$$ORIGIN -Wl,--no-undefined -Wl,-soname,
all: libSixenseJava32.so libSixenseJava64.so

libSixenseJava32.so: $(addprefix build/32/,$(OBJECTS))
	$(CXX) $(LDFLAGS)$@ -m32 -o native/linux/$@ $^ -L$(SIXENSE)lib/linux/release -lsixense -lsixense_utils
	strip native/linux/$@

libSixenseJava64.so: $(addprefix build/64/,$(OBJECTS))
	$(CXX) $(LDFLAGS)$@ -m64 -o native/linux/$@ $^ -L$(SIXENSE)lib/linux_x64/release -lsixense_x64 -lsixense_utils_x64
	strip native/linux/$@

endif
endif

build/32/%.o: src/native/%.cpp
	@-mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -m32 -o $@ $<

build/64/%.o: src/native/%.cpp
	@-mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -m64 -o $@ $<

clean:
	rm -r build/32/*.o build/64/*.o
