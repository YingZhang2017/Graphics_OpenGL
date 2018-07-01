
## Introduction ##
This is a OpenGL demo program for tessellation shader.

## Libraries ##
The libraries reside in the /include/
* include - header files
* include/gl-yz.h - customized header file for multiple os
* include/GL - GLEW(v2.1.0)
* include/GLFW - GLFW(v3.2)
* inlcude/osx - 64-bit Mac OS libraries

## compile ##
`make -f Makefile`

## bash script ##
`bash clear.sh` - clean all complied and execute files
`bash rebuild.sh` - clean and recompile, then auto run executable program

## file definition ##
* main.cpp - main program
* gl_utils - helper functions for print info, check error
* make_shaders - helper functions for set shader programs
* <shader_name>.glsl - shader files
