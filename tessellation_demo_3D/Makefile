BIN = tessellation_demo
CC = g++
FLAGS = -DAPPLE -Wall -pedantic -mmacosx-version-min=10.5 -arch x86_64 -fmessage-length=0 -UGLFW_CDECL -fprofile-arcs -ftest-coverage
INC = -I ../include -I/sw/include -I/usr/local/include
LIB_PATH = ../include/osx/
LOC_LIB = $(LIB_PATH)libGLEW.a $(LIB_PATH)libglfw3.a
FRAMEWORKS = -framework Cocoa -framework OpenGL -framework IOKit
SRC = main.cpp gl_utils.cpp Shader.cpp Shape3D.cpp Cube.cpp Scene.cpp

all:
	${CC} ${FLAGS} ${FRAMEWORKS} -o ${BIN} ${SRC} ${INC} ${LOC_LIB}
