/* Scene.cpp - a class implementation representing a scence that contains
 *             different 3D objects with different shader
 *
 * Ying Zhang, Jul 2018
 */

 #include "Scene.h"

 using namespace std;


 // =========== constructor =======
 // init scene shader uniform variables
 Scene::Scene(int window_width, int window_height) {
   objects.clear();
   shaders.clear();
   // set init scene shader uniforms. if has shader, send uniforms to shader
   setTessFactors(1.0, 1.0);    // inner, outer

   setLightingFactors(vec3(1.2f, 1.0f, 2.0f),     // light position
                      vec3(1.0f, 1.0f, 1.0f),     // light color
                      vec3(0.0f, 0.75f, 0.75f),   // diffuse material
                      vec3(0.04f, 0.04f, 0.04f)); // ambient material

   setViewFactors(vec3(0.0f, 0.0f, 10.0f),  // camera position
                  vec3(0.0f, 0.0f, 0.0f),   // view position
                  vec3(0.0f, 1.0f, 0.0f));  // head up

   float ratio = (float)window_width / (float)window_height;
   setProjectionFactors(45.0f,  // view angle
                        ratio,  // aspec ratio
                        1.0f,   // near
                        100.f); // far
 }

 // ========== Destructor ===========
 Scene::~Scene(){}

 // ========== add object to scene ========
 void Scene::addObject(Shape3D* obj) {
   objects.push_back(obj);
 }

 // ========== add shader to scene ========
 void Scene::addShader(Shader* sp) {
   shaders.push_back(sp);
 }

 // ========== draw scene =================
 void Scene::drawScene() {
   glEnable(GL_DEPTH_TEST);
   glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );

   // switch between draw line and surface
   for (int i = 0; i < objects.size(); i++) {
     objects[i]->draw();
   }
   glFlush();    // send all output to display

 }

 // set unifrom variables
 // =========== set tess factors ===============
 void Scene::setTessFactors(float inner, float outer) {
    suv.tess_fac_inner = inner > 1.0 ? inner : 1.0;
    suv.tess_fac_outer = outer > 1.0 ? outer : 1.0;

    if (!shaders.empty()) {
      sendTessFactorToShaders();
    }
 }

 // =========== set projection factors ===============
 void Scene::setLightingFactors(vec3 light_pos, vec3 light_col,
                                vec3 diff_m,    vec3 amb_m) {
    suv.light_position = light_pos;
    suv.light_color = light_col;
    suv.diffuse_material = diff_m;
    suv.ambient_material = amb_m;

    if (!shaders.empty()) {
      sendLightFactorToShaders();
    }
}

 // =========== set view factors ===============
 void Scene::setViewFactors(vec3 camera_pos, vec3 view_pos, vec3 head_up) {
   suv.camera_position = camera_pos;
   suv.view_position = view_pos;
   suv.head_up = head_up;
   suv.viewMatrix = generateViewMatrix();

   if (!shaders.empty()) {
     sendViewMatrixToShaders();
   }
 }

 // =========== set lighting factors ===============
 void Scene::setProjectionFactors(float angle, float aspec, float near, float far){
    suv.view_angle = angle;
    suv.aspec_ratio = aspec;
    suv.near = near;
    suv.far = far;

    suv.projectionMatrix = generateProjMatrix();
    if(!shaders.empty()) {
      sendProjMatrixToShaders();
    }
  }

  // ===== scene interations ==========
  // ===== scene rotate ===============
  void Scene::sceneRotate(float angle, float x, float y, float z) {
    for (int i = 0; i < objects.size(); i++) {
      objects[i]->setRotate(angle, x, y, z);
      objects[i]->sendModelMatrixToShader();
    }
  }

  // ====== scence translation =========
  void Scene::sceneTranslate(float x_offset, float y_offset, float z_offset) {
    for (int i = 0; i < objects.size(); i++) {
      vec3 loc = objects[i]->getLocation();
      objects[i]->setLocation(loc.x + x_offset, loc.y + y_offset, loc.z + z_offset);
      objects[i]->sendModelMatrixToShader();
    }
  }

  // ====== scence tessellation =========
  void Scene::sceneTessllate(float inner_offset, float outer_offset) {

    float in = suv.tess_fac_inner + inner_offset;
    float out = suv.tess_fac_outer + outer_offset;
    in = in > 1.0 ? in : 1.0;
    out = out > 1.0 ? out : 1.0;
    setTessFactors(in, out);
  }


  // ========= send all uniform vars to shaders
  void Scene::sendAllUniformToShaders() {
    sendTessFactorToShaders();
    sendLightFactorToShaders();
    sendViewMatrixToShaders();
    sendProjMatrixToShaders();
  }

  // ========== send tessellation uniform vars to shaders
  void Scene::sendTessFactorToShaders() {
     for (int i = 0; i < shaders.size(); i++) {
       Shader * shader = shaders[i];
       shader->use();
       shader->setFloat("tess_fac_outer", suv.tess_fac_outer);
       shader->setFloat("tess_fac_inner", suv.tess_fac_inner);
     }
  }


 // ========== sned light uniform vars to shaders
 void Scene::sendLightFactorToShaders() {
   for (int i = 0; i < shaders.size(); i++) {
     Shader * shader = shaders[i];
     shader->use();
     shader->setVec3("light_position", suv.light_position);
     shader->setVec3("light_color", suv.light_color);
     shader->setVec3("diffuse_material", suv.diffuse_material);
     shader->setVec3("ambient_material", suv.ambient_material);
   }
 }


 // ========== sned view factors uniform vars to shaders
 void Scene::sendViewMatrixToShaders() {
   for (int i = 0; i < shaders.size(); i++) {
     Shader * shader = shaders[i];
     shader->use();
     shader->setVec3("view_position", suv.view_position);
     shader->setMat4("viewMatrix", suv.viewMatrix);
   }
 }


 // ========== sned projectionmatrix uniform vars to shaders
 void Scene::sendProjMatrixToShaders() {
   for (int i = 0; i < shaders.size(); i++) {
     Shader * shader = shaders[i];
     shader->use();
     shader->setMat4("projectionMatrix", suv.projectionMatrix);
   }
 }


 // =========== generate view Matrix =============
 mat4 Scene::generateViewMatrix() {
   return lookAt(suv.camera_position, suv.view_position,  suv.head_up);
 }


 // =========== generate projection Matrix =============
 mat4 Scene::generateProjMatrix() {
   return perspective(suv.view_angle,
                      suv.aspec_ratio,
                      suv.near,
                      suv.far);
 }
