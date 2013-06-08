SixenseJava.jar: java
	cd dist/java; zip ../../SixenseJava.jar -r .
	cd native; zip ../SixenseJava.jar -r .

jar: SixenseJava.jar
java:
	@-mkdir -p dist/java 2>/dev/null;
	cd src/java; javac $(shell cd src/java; find -name *java ) -d ../../dist/java;
.PHONY: clean all java jar


VPATH = dist
CXX = g++

SIXENSE= /home/mabrowning/MinecraftDev/Hydra/SixenseSDK_062612/
CXXFLAGS = -g -fPIC -c -Wall -I/usr/lib/jvm/java-6-openjdk-amd64/include -I/usr/lib/jvm/java-6-openjdk-amd64/include/linux -I$(SIXENSE)include/sixense_utils -I$(SIXENSE)include/sixense_utils/controller_manager -I$(SIXENSE)include
LDFLAGS = -shared -fPIC -Wl,-rpath,\$$ORIGIN -Wl,--no-undefined -Wl,-soname,
SOURCES = com_sixense_Sixense.cpp sixense_java_utils.cpp $(addprefix com_sixense_utils_,ButtonStates.cpp ControllerManager.cpp Derivatives.cpp Events.cpp PlayerMovement.cpp ViewAngles.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

all: libSixenseJava32.so libSixenseJava64.so

libSixenseJava32.so: $(addprefix build/32/,$(OBJECTS))
	$(CXX) $(LDFLAGS)$@ -m32 -o dist/$@ $^ -L$(SIXENSE)lib/linux/release -lsixense -lsixense_utils

libSixenseJava64.so: $(addprefix build/64/,$(OBJECTS))
	$(CXX) $(LDFLAGS)$@ -m64 -o dist/$@ $^ -L$(SIXENSE)lib/linux_x64/release -lsixense_x64 -lsixense_utils_x64

build/32/%.o: src/native/%.cpp
	@-mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -m32 -o $@ $<

build/64/%.o: src/native/%.cpp
	@-mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -m64 -o $@ $<

clean:
	rm -r dist/*.so build/32/*.o build/64/*.o
