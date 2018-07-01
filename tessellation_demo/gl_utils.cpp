#include "gl_utils.h"
#include <iostream>

using namespace std;

// a call-back function to notify whrn window is resized
void windowResizedCallback (GLFWwindow* window, int width, int height)
{
	window_width = width;
	window_height = height;
	cout << "window width: " << width <<", height: " << height << endl;
}

// print version info
void print_version_info ()
{
	cout << "Renderer:" << glGetString(GL_RENDERER) << endl;
	cout << "OpenGl version:" << glGetString(GL_VERSION) << endl;
}

// print max patch number that supported
void print_max_patch () {
	GLint MaxPatchVertices = 0;
	glGetIntegerv(GL_MAX_PATCH_VERTICES, &MaxPatchVertices);
	cout << "Max supported patch vertices: " << MaxPatchVertices << endl;	
}

// print shader file
void print_shader_file (const char* fileName, char* buff)
{
	cout << "======== " << fileName << " =========" << endl;
	for (int i = 0; i < strlen(buff); i++) cout << buff[i];
	cout << endl;
}
