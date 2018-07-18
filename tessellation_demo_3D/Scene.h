/* Scene.h - a class implementation representing a scence that contains
 *             different 3D objects with different shader
 *
 * Ying Zhang, Jul 2018
 */

#ifndef SCENE_H_
#define SCENE_H_

#include "Shader.h"
#include "Cube.h"

#include <iostream>
#include <vector>


struct SecneShaderUniformVars {
  // tessellation factors
  float tess_fac_inner;
  float tess_fac_outer;
  // lighting
  vec3 light_position;
  vec3 light_color;
  vec3 diffuse_material;
  vec3 ambient_material;
  // view
  vec3 camera_position;
  vec3 view_position;
  vec3 head_up;
  // projection
  float view_angle;
  float aspec_ratio;
  float near;
  float far;
  // transformation matrix.
  // scene set view and projection. object set model
  mat4 viewMatrix;
  mat4 projectionMatrix;
};

class Scene {
public:
  Scene(int window_width, int window_height);
  ~Scene();

  void addObject(Shape3D * obj);
  void addShader(Shader * sp);
  void drawScene();
  // set uniform variables
  void setTessFactors(float inner, float outer);
  void setLightingFactors(vec3 light_pos, vec3 light_col, vec3 diff_m, vec3 amb_m);
  void setViewFactors(vec3 camera_pos, vec3 view_pos, vec3 head_up);
  void setProjectionFactors(float angle, float aspec, float near, float far);

  // scene interactions for all objects in SecneShaderUniformVars
  void sceneScale(float x_offset, float y_offset, float z_offset);
  void sceneRotate(float angle, float x, float y, float z);
  void sceneTranslate(float x_offset, float y_offset, float z_offset);
  void sceneTessllate(float inner_offset, float outer_offset);

  // uniform vars
  SecneShaderUniformVars suv;
  void sendAllUniformToShaders();

protected:
  vector<Shape3D*> objects;
  vector<Shader*> shaders;

  void sendTessFactorToShaders();
  void sendLightFactorToShaders();
  void sendViewMatrixToShaders();
  void sendProjMatrixToShaders();

  mat4 generateViewMatrix();
  mat4 generateProjMatrix();
};


#endif
