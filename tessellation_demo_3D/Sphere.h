/* Sphere.h - a class implementation representing
 *              a Sphere object in OpenGL
 *
 * Ying Zhang, Jul 2018
 */

 #ifndef SPHERE_H_
 #define SPHERE_H_

 #include "Shape3D.h"
 #include <iostream>
 #include <string>

 class Sphere: public Shape3D
 {
 public:
   Sphere(string colorName);
   Sphere(Color c);
   Sphere(float r, float g, float b, float a = 1.0);
   virtual ~Sphere();

   virtual void createBuffer();
   virtual void draw();
 };

 #endif
