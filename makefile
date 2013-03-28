CXX_CFLAGS = -Wall -Wextra -pedantic
CXX_LDFLAGS = -Wl,-rpath,'./OgreLib'
LIBRARIES = -lBulletCollision -lBulletDynamics -lBulletSoftBody -lCEGUIBase -lCEGUIDevILImageCodec -lCEGUIExpatParser -lCEGUIFalagardWRBase -lCEGUIFreeImageImageCodec -lCEGUILibxmlParser -lCEGUIOgreRenderer -lCEGUIOpenGLRenderer -lCEGUISTBImageCodec -lCEGUISampleHelper -lCEGUITGAImageCodec -lCEGUITinyXMLParser -lLinearMath -lOIS -lOgreBulletCol -lOgreBulletDyn -lOgreMain -lOgrePaging -lOgreProperty -lOgreRTShaderSystem -lOgreTerrain
CPP_FILES := $(wildcard *.cpp)
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))
LD_FLAGS := ...
CC_FLAGS := ...

DifferenceEngine: $(OBJ_FILES)
	g++ -o $@ $^ $(CXX_LDFLAGS) $(LIBRARIES)

obj/%.o: %.cpp
	mkdir -p obj
	g++ $(CXX_CFLAGS) -c -o $@ $<
	
clean:
	rm -rf obj/*
	rm DifferenceEngine
