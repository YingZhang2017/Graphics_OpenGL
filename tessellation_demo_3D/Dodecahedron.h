/* Dodecahedron.h - a class implementation representing
 *              a great sellated Dodecahedron object in OpenGL
 *
 *
 * Author: Ying Zhang
 * July, 2018
 *
 * reference sources:
 * 1. UNH cs770 base code of demos, R.Daniel.Bergeron
 */

 #ifndef DODECAHEDRON_H_
 #define DODECAHEDRON_H_

 #include "Shape3D.h"
 #include <iostream>
 #include <string>

 class Dodecahedron: public Shape3D
 {
 public:
   Dodecahedron(string colorName);
   Dodecahedron(Color c);
   Dodecahedron(float r, float g, float b, float a = 1.0);
   virtual ~Dodecahedron();

   virtual void createBuffer();
   virtual void draw();
 };

 #endif
