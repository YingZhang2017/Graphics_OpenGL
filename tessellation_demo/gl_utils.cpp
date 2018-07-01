#include "gl_utils.h"
#include <iostream>

using namespace std;

// a call-back function to notify whrn window is resized
void windowResizedCallback (GLFWwindow* window, int width, int height) {
	window_width = width;
	window_height = height;
	cout << "window width: " << width <<", height: " << height << endl;
}

// print version info
void print_version_info () {
	cout << "Renderer:" << glGetString(GL_RENDERER) << endl;
	cout << "OpenGl version:" << glGetString(GL_VERSION) << endl;
}
