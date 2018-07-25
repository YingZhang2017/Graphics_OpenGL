/**
 * Color.h -- a class for gl color specification
 *
 * Author: Ying Zhang,
 * July, 2018
 *
 * reference sources:
 * 1. UNH cs770 base code of demos, R.Daniel.Bergeron
 */

#ifndef COLOR_H
#define COLOR_H

#include <string>
#include <iostream>
using namespace std;

class Color {
public:
  float r, g, b, a;
  // ------ Constructor -----------
  Color(): r(1.0), g(1.0), b(1.0){}
  Color(float red, float green, float blue, float alpha = 1.0f) : r(red), g(green), b(blue), a(alpha){}
  Color( const Color& c ): r(c.r), g(c.g), b(c.b), a(c.a) {}
  Color(string colorName) { set(colorName); }
  // ------- reset color ----------
  inline void set(float red, float green, float blue, float alpha = 1.0f){
    r = red; g = green; b = blue; a = alpha;
  }
  inline void set(string colorName) {
    if (colorName == "IndiaRed") set_IndiaRed();
    else if (colorName == "Coral")    set_Coral();
    else if (colorName == "Salmon")   set_Salmon();
    else if (colorName == "Orange")   set_Orange();
    else if (colorName == "Violet")   set_Violet();
    else if (colorName == "ForestGreen")  set_ForestGreen();
    else if (colorName == "SteelBlue")    set_SteelBlue();
    else if (colorName == "DogerBlue")    set_DogerBlue();
    else {
      // noit a predifined color name
      cerr << "set color < "  << colorName << ">: ";
      cerr << "this is not a predifined color. please choose from following color name: \n";
      cout << "IndiaRed, Coral, Salmon, Orange, Violet, ForestGreen, SteelBlue, DogerBlue\n";
    }
  }

  // predifined colors
  inline void set_IndiaRed() { r = 0.804; g = 0.361; b = 0.361; a = 1.0; }
  inline void set_Coral()    { r = 1.000; g = 0.498; b = 0.314; a = 1.0; }
  inline void set_Salmon()   { r = 0.980; g = 0.502; b = 0.447; a = 1.0; }
  inline void set_Orange()   { r = 1.000; g = 0.647; b = 0.001; a = 1.0; }
  inline void set_Violet()   { r = 0.541; g = 0.169; b = 0.886; a = 1.0; }
  inline void set_Orchid()   { r = 0.600; g = 0.196; b = 0.800; a = 1.0; }
  inline void set_ForestGreen() { r = 0.133; g = 0.545; b = 0.133; a = 1.0; }
  inline void set_SteelBlue()   { r = 0.275; g = 0.510; b = 0.706; a = 1.0; }
  inline void set_DogerBlue()   { r = 0.118; g = 0.565; b = 1.000; a = 1.0; }
};

#endif /* COLOR_H */
