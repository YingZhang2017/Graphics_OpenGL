/**
 *   gl_yz.h
 *
 *   This file tries to encapsulate in one file all the variations
 *   needed for portable OpenGL demo.
 *
 *   Mac OS tested.
 *   Win/linux need test.
 *
 */

 #ifndef _GL_YZ_H_
    #define _GL_YZ_H_
    #if defined(__APPLE__)  // Mac OS version
    #   include <GL/glew.h>    // include GLEW
    #   include <GLFW/glfw3.h> // include GLFW
    #   include <glm/glm.hpp>  // include gl math library
    // include glm transformations matrix library
    #   include <glm/gtx/transform.hpp>
    #   include <glm/gtc/matrix_transform.hpp>
    #else // win/linux
    #   include <GL/glew.h>    // include GLEW
    #   include <GLFW/glfw3.h> // include GLFW
    #   include <glm/glm.hpp>  // include gl math library
    // include glm transformations matrix library
    #   include <glm/gtx/transform.hpp>
    #   include <glm/gtc/matrix_transform.hpp>
    #endif
 #endif
