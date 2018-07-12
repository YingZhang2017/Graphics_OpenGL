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

// a call-back function when a GLFW function fails
void errorCallback (int error, const char* description)
{
	cerr << "ERROR: " << description << endl;
}

// a call-back function for key event exit
void exitKeyCallback (GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// set q or ESC as quit
	if ((key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q) && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

// print version info
void print_version_info ()
{
	cout << "Renderer:" << glGetString(GL_RENDERER) << endl;
	cout << "OpenGl version:" << glGetString(GL_VERSION) << endl;
}

// get max patch number that supported
GLuint get_max_patch () {
	GLint MaxPatchVertices = 0;
	glGetIntegerv(GL_MAX_PATCH_VERTICES, &MaxPatchVertices);
	cout << "Max supported patch vertices: " << MaxPatchVertices << endl;
	return MaxPatchVertices;
}

// print shader file
void print_shader_file (const char* fileName, char* buff)
{
	cout << "======== " << fileName << " =========" << endl;
	for (int i = 0; i < strlen(buff); i++) cout << buff[i];
	cout << endl;
}
