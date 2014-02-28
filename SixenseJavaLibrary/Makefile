.PHONY: clean all java jar


CXX = g++

SIXENSE=/home/grender/soft/sixenseSDK_linux_OSX/
#SIXENSE=../../../SixenseSDK_062612/
CXXFLAGS = -g -fPIC -c -Wall -I$(SIXENSE)include/sixense_utils -I$(SIXENSE)include/sixense_utils/controller_manager -I$(SIXENSE)include
LDFLAGS = -shared -fPIC
SOURCES = com_sixense_Sixense.cpp sixense_java_utils.cpp Quat.cpp $(addprefix com_sixense_utils_,ButtonStates.cpp ControllerManager.cpp Derivatives.cpp Events.cpp LaserPointer.cpp PlayerMovement.cpp ViewAngles.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
OUTDIR = natives

UNAME:=$(shell uname)
ifeq ($(UNAME), Darwin)
CXXFLAGS+= -I/System/Library/Frameworks/JavaVM.framework/Versions/Current/Headers -I/Developer/SDKs/MacOSX10.6.sdk/System/Library/Frameworks/JavaVM.framework/Versions/A/Headers
LDFLAGS+=-Wl,-headerpad_max_install_names

all: $(OUTDIR)/osx/libSixenseJava32.jnilib $(OUTDIR)/osx/libSixenseJava64.jnilib

$(OUTDIR)/osx/libSixenseJava32.jnilib: $(addprefix build/32/,$(OBJECTS))
	$(CXX) $(LDFLAGS) -m32 -o $@ $^ -L$(SIXENSE)lib/osx/release_dll -lsixense -lsixense_utils
	install_name_tool -change /usr/local/lib/libsixense.dylib "@loader_path/libsixense.dylib" $@
	install_name_tool -change /usr/local/lib/libsixense_utils.dylib "@loader_path/libsixense_utils.dylib" $@

	install_name_tool -change /usr/local/lib/libsixense.dylib "@loader_path/libsixense.dylib" $(OUTDIR)/osx/libsixense.dylib
	install_name_tool -change /usr/local/lib/libsixense.dylib "@loader_path/libsixense.dylib" $(OUTDIR)/osx/libsixense_utils.dylib
	install_name_tool -change /usr/local/lib/libsixense_utils.dylib "@loader_path/libsixense_utils.dylib" $(OUTDIR)/osx/libsixense_utils.dylib

$(OUTDIR)/osx/libSixenseJava64.jnilib: $(addprefix build/64/,$(OBJECTS))
	$(CXX) $(LDFLAGS) -m64 -o $@ $^ -L$(SIXENSE)lib/osx_x64/release_dll -lsixense_x64 -lsixense_utils_x64
	install_name_tool -change /usr/local/lib/libsixense_x64.dylib "@loader_path/libsixense_x64.dylib" $@
	install_name_tool -change /usr/local/lib/libsixense_utils_x64.dylib "@loader_path/libsixense_utils_x64.dylib" $@
	install_name_tool -change /usr/local/lib/libsixense_x64.dylib "@loader_path/libsixense_x64.dylib" $(OUTDIR)/osx/libsixense_x64.dylib
	install_name_tool -change /usr/local/lib/libsixense_x64.dylib "@loader_path/libsixense_x64.dylib" $(OUTDIR)/osx/libsixense_utils_x64.dylib
	install_name_tool -change /usr/local/lib/libsixense_utils_x64.dylib "@loader_path/libsixense_utils_x64.dylib" $(OUTDIR)/osx/libsixense_utils_x64.dylib

else
ifeq ($(UNAME), Linux)
CXXFLAGS+= -I/usr/lib/jvm/java-7-oracle/include -I/usr/lib/jvm/java-7-oracle/include/linux 

LDFLAGS+= -Wl,-rpath,\$$ORIGIN -Wl,--no-undefined -Wl,-soname,
all: $(OUTDIR)/linux/libSixenseJava32.so $(OUTDIR)/linux/libSixenseJava64.so

$(OUTDIR)/linux/libSixenseJava32.so: $(addprefix build/32/,$(OBJECTS))
	$(CXX) $(LDFLAGS) -m32 -o $@ $^ -L$(SIXENSE)lib/linux/release -lsixense -lsixense_utils
	strip $@

#$(OUTDIR)/linux/libSixenseJava64.so: $(addprefix build/64/,$(OBJECTS))
#	$(CXX) $(LDFLAGS) -m64 -o $@ $^ -L$(SIXENSE)lib/linux_x64/release -lsixense_x64 -lsixense_utils_x64
#	strip $@

endif
endif

build/32/%.o: src/%.cpp
	@-mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -m32 -o $@ $<

build/64/%.o: src/%.cpp
	@-mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -m64 -o $@ $<

clean:
	rm -r build/32/*.o build/64/*.o

deploy:
	mvn deploy
