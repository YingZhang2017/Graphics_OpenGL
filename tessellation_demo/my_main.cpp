/***
This is a demo programm using tessellation shader in OpenGL
Author: Ying Zhang
==========
Controller:
Raise/Lower "inner" tessellation factor: Q/A keys
Raise/Lower "outter" tessellation factor: W/S keys
***/

#include <GL/glew.h> // include GLEW
#include <GLFW/glfw3.h> // include GLFW
#include "gl_utils.h"

#include <stdio>
#include <stdlib>
#include <time>
#include <assert>
#include <string>

using namespace std;

// define the original window size
int window_width = 1280;
int window_height = 720;

// define the initial inner/outter tessellation factor
float inner_tess_factor = 1.0;
float outter_tess_factor = 1.0;


int main () {

  cout << glfwGetVersionString() << endl;


}
