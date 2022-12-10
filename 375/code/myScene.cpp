/// \file myScene.hpp
/// \brief Implementation of myScene, where the geometry of my shapes will live. 
/// \author John Shenk
/// \version A08

#include <vector>
#include <iostream>
#include <glm/mat4x4.hpp>
#include <sstream>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

#include "OpenGLContext.hpp"
#include "ShaderProgram.hpp"
#include "Scene.hpp"
#include "myScene.hpp"
#include "Geometry.hpp"
#include "ColorsMesh.hpp"
#include "Vector3.hpp"
#include "NormalsMesh.hpp"

myScene::myScene (int lights, OpenGLContext* context, ShaderProgram* colors, ShaderProgram* norms) : Scene (norms, lights)
{ 
  std::vector<float> data;
  std::vector<unsigned int> indices;

  s_colors = colors;
  l_shader->enable();

  setLights(4);
  
  PointLightSource* psource = new PointLightSource(Vector3(1, 1, 1), Vector3(0, 0, 0), Vector3(6.31, -4.18, 10.27), Vector3(1, 0, 1));
  psource->setUniforms(l_shader, 2);

  DirectionalLightSource* dsource = new DirectionalLightSource(Vector3(1, 1, 1), Vector3(1, 1, 1), Vector3(0, -1, 0));
  dsource->setUniforms(l_shader, 0);

  //SpotLightSource* s_source = new SpotLightSource(Vector3(0, 0, 1), Vector3(1, 1, 0), Vector3(1, 1, -10), Vector3(1, 5, 1), Vector3(0, 0, 1), 5 * (M_PI / 180), 1);
  //s_source->setUniforms(l_shader, 0);

  SpotLightSource* s_source = new SpotLightSource(Vector3(1, 1, 0), Vector3(1, 1, 1), Vector3(6.31, 0, 0), Vector3(1, 0, 0), Vector3(0, 0, -1), 10 * (M_PI / 180), 20);
  s_source->setUniforms(l_shader, 1);

  SpotLightSource* s_source2 = new SpotLightSource(Vector3(1, 0, 0), Vector3(1, 1, 1), Vector3(4.31, 1, 0), Vector3(1, 0, 0), Vector3(0, -1, 0), 10 * (M_PI / 180), 20);
  s_source2->setUniforms(l_shader, 3);

  //SpotLightSource* s_source2 = new SpotLightSource(Vector3(1, 1, 0), Vector3(1, 1, 1), Vector3(0, 0, 0), Vector3(1, 0, 0), Vector3(0, 0, 0), 5 * (M_PI / 180), 1);
  //s_source2->setUniforms(l_shader, 2);
  

  l_shader->disable();
  
  /**
  ColorsMesh* a_mesh = new ColorsMesh(context, s_colors);
  std::vector<float> mesh1 {
    0.0f, 3.0f, 0.0f,
    1.0f, 0.0f, 0.0f, 
    -3.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 1.0f,
    3.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f
  };
  indexData(mesh1, a_mesh->getFloatsPerVertex(), data, indices);
  a_mesh->addGeometry(data);
  a_mesh->addIndices(indices);  
  a_mesh->prepareVao();
  this->add("mesh1", a_mesh);  

  data.clear();
  indices.clear();
    
  
  ColorsMesh* b_mesh =  new ColorsMesh(context, s_colors);
  std::vector<float> mesh2 {
    0.1f, 2.75f, 0.0f,
    1.0f, 0.0f, 0.0f,
    0.1f, 2.0f, 0.0f,
    1.0f, 0.0f, 1.0f,
    5.0f, 2.0f, 0.0f,
    1.0f, 0.0f, 1.0f
  };
  indexData(mesh2, b_mesh->getFloatsPerVertex(), data, indices);
  b_mesh->addGeometry(data);
  b_mesh->addIndices(indices);
  b_mesh->prepareVao();
  this->add("mesh2", b_mesh); 

  data.clear();
  indices.clear();

  ColorsMesh* c_mesh =  new ColorsMesh(context, s_colors);
  std::vector<float> mesh3 {
    -5.0f, 2.0f, 0.0f,
    1.0f, 0.0f, 1.0f,
    -0.1f, 2.0f, 0.0f,
    1.0f, 0.0f, 1.0f,
    -0.1f, 2.75f, 0.0f,
    1.0f, 0.0f, 0.0f
  };
  indexData(mesh3, c_mesh->getFloatsPerVertex(), data, indices); 
  c_mesh->addGeometry(data);
  c_mesh->addIndices(indices);
  c_mesh->addGeometry(mesh3);
  c_mesh->prepareVao();
  this->add("mesh3", c_mesh);

  data.clear();
  indices.clear();

  ColorsMesh* d_mesh =  new ColorsMesh(context, s_colors);
  std::vector<float> mesh4 {
    0.0f, -1.0f, 0.0f, 
    0.0f, 1.0f, 1.0f,
    -2.0f, -1.5f, 1.0f,
    0.0f, 0.0f,  1.0f,
    -3.0f, -5.0f, -1.0f,
    0.0f, 1.0f, 1.0f,
    /////////////////
    0.0f, -1.0f ,0.0f,
    0.0f, 1.0f, 1.0f,
    3.0f, -5.0f, -1.0f,
    0.0f, 1.0f, 1.0f,
    2.0f, -1.5f, 1.0f, 
    0.0f, 0.0f, 1.0f,
    /////////////////
    0.0f, -2.0f, 2.0f, 
    0.0f, 0.0f, 1.0f,
    -2.0f, -5.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    2.0f, -5.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    /////////////////
    0.0f, -1.0f, -1.0f,
    0.0f, 0.0f, 1.0f,
    1.0f, -0.1f, 0.0f,
      0.0f, 1.0f, 1.0f,
      -1.0f, -0.1f, 0.0f,
      0.0f, 1.0f, 1.0f
    };
    indexData(mesh4, d_mesh->getFloatsPerVertex(), data, indices);
    d_mesh->addGeometry(data);
    d_mesh->addIndices(indices);
    d_mesh->prepareVao();
    this->add("mesh4", d_mesh); 

    data.clear();
    indices.clear();

    ColorsMesh* e_mesh =  new ColorsMesh(context, s_colors);
    std::vector<float> mesh5 {
      /////Right Eye/////
      -1.5f, -0.5f, 0.0f,
      1.0f, 0.0f, 0.0f,
      -2.0f, -1.0f, 0.0f,
      1.0f, 0.0f, 0.0f,
      -1.0f, -1.0f, 0.0f,
      1.0f, 0.0f, 0.0f,
      /////Left Eye/////
      1.5f, -0.5f, 0.0f,
      1.0f, 0.0f, 0.0f,
      1.0f, -1.0f, 0.0f,
      1.0f, 0.0f, 0.0f,
      2.0f, -1.0f, 0.0f, 
      1.0f, 0.0f, 0.0f
    };
    indexData(mesh5, e_mesh->getFloatsPerVertex(), data, indices);
    e_mesh->addGeometry(data);
    e_mesh->addIndices(indices);
    e_mesh->prepareVao();
    this->add("mesh5", e_mesh); 

    data.clear();
    indices.clear();

    ColorsMesh* f_mesh =  new ColorsMesh(context, s_colors);
    std::vector<float> mesh6 {
      /////Right Face/////
      -2.5f, 0.0f, 0.0f,
      0.0f, 1.0f, 1.0f,
      -2.69f, -4.0f, -1.0f,
      0.0f, 0.0f, 1.0f,
      -1.9f, -0.0f, 0.0f,
      0.0f, 1.0f, 1.0f,
      /////Left Face/////
      2.5f, 0.0f, 0.0f,
      0.0f, 1.0f, 1.0f,
      1.9f, 0.0f, 0.0f,
      0.0f, 0.0f, 1.0f,
      2.69f, -4.0f, -1.0f,
      0.0f, 1.0f, 1.0f,
    };
    indexData(mesh6, f_mesh->getFloatsPerVertex(), data, indices);
    f_mesh->addGeometry(data);
    f_mesh->addIndices(indices);  
    f_mesh->prepareVao();
    this->add("mesh6", f_mesh); 

    data.clear();
    indices.clear();
  **/
    ColorsMesh* g_mesh =  new ColorsMesh(context, s_colors, Vector3(0, 0.5, 0), Vector3(0.4,	0.5,	0.4), Vector3(0.04,	0.7,	0.04), Vector3(0, 1, 0), 	.078125);
    std::vector<float> mesh7 {
       -0.5f, -0.7f, -1.0f,
      1.0f, 1.0f, 1.0f, 
      0.0f, -0.7f, -1.0f,
      1.0f, 1.0f, 1.0f,
      -0.5f, -0.7f, -1.0f,
      1.0f, 1.0f, 1.0f
    };
    indexData(mesh7, g_mesh->getFloatsPerVertex(), data, indices);
    g_mesh->addGeometry(data);
    g_mesh->addIndices(indices);
    g_mesh->prepareVao();
    this->add("mesh7", g_mesh); 

    data.clear();
    indices.clear();

    
    
   std::vector<Triangle> cube = buildCube();
   /**

    ColorsMesh* randomFaceColors = new ColorsMesh(context, s_colors);
    std::vector<Vector3>  randFaceColor = generateRandomFaceColors(cube);
    indexData(dataWithFaceColors(cube, randFaceColor), randomFaceColors->getFloatsPerVertex(), data, indices);
    randomFaceColors->addGeometry(data);
    randomFaceColors->addIndices(indices);
    randomFaceColors->prepareVao();
    this->add("randomFaceColors", randomFaceColors);
    randomFaceColors->moveRight(-5.5f);
    randomFaceColors->moveUp(3.0f);
 knight->rotateLocal(90, Vector3(1, 0, 0));
    knight->moveBack(10);
    knight->moveUp(-1);
    data.clear();
    indices.clear();

    ColorsMesh* randomVertexColors = new ColorsMesh(context, s_colors);
    std::vector<Vector3>  randVertexColor = generateRandomVertexColors(cube);
    indexData(dataWithVertexColors(cube, randVertexColor), randomVertexColors->getFloatsPerVertex(), data, indices);
    randomVertexColors->addGeometry(data);
    randomVertexColors->addIndices(indices);
    randomVertexColors->prepareVao();
    this->add("randomVertexColors", randomVertexColors);
    randomVertexColors->moveRight(-5.5f);
    randomVertexColors->moveUp(1.5f);

  **/
    data.clear(); 
    indices.clear();

    NormalsMesh* dragon = new NormalsMesh(context, l_shader, "models/18481_Dragon_v1.obj", 0,Vector3(0.1745,	0.01175,	0.01175), Vector3(0.61424,	0.04136,	0.04136), Vector3(0.727811,	0.626959,	0.626959), 
      Vector3(0, 0, 0), 0.6);
    dragon->prepareVao();
    this->add("dragon", dragon);
    dragon->moveUp(-1.5);
    dragon->moveBack(1);
    
    dragon->rotateLocal(180, Vector3(0, 0, 1));
    dragon->rotateLocal(45, Vector3(1, 0, 0));
    
    
  
  NormalsMesh* knight = new NormalsMesh(context, l_shader, "models/11073_Knight_V5.obj", 0,Vector3(0.25,	0.25,	0.25), Vector3(0.4,	0.4,	0.4), Vector3(0.774597,	0.774597,	0.774597), 
      Vector3(0, 0, 0), 0.6);
    knight->prepareVao();
    this->add("knight", knight);
    knight->scaleLocal(0.02);
    knight->pitch(-90);
    knight->roll(180);
    //knight->moveUp(100);
    //knight->moveBack(-100);
    //knight->moveUp(750);
    knight->moveLocal(600, Vector3(0, 1, 0));
    //knight->moveLocal(-100, Vector3(0, 0, 1));
    knight->moveLocal(-200, Vector3(0, 0, 1));
  
  NormalsMesh* randomFaceNormals = new NormalsMesh(context, l_shader,  Vector3(0.0,	0.05,	0.0), Vector3(0.4,	0.5,	0.4), Vector3(0.04,	0.7,	0.04), 
      Vector3(1, 1, 0), 0.078125);
    std::vector<Vector3>  randFaceNorms = computeFaceNormals(cube);
    indexData(dataWithFaceNormals(cube, randFaceNorms), randomFaceNormals->getFloatsPerVertex(), data, indices);
    randomFaceNormals->addGeometry(data);
    randomFaceNormals->addIndices(indices);
    randomFaceNormals->prepareVao();
    this->add("randomFaceNormals", randomFaceNormals);
    randomFaceNormals->moveLocal(-11, Vector3( 1, 0, 0));
    randomFaceNormals->moveLocal(5.5, Vector3(0, 1, 0));
    randomFaceNormals->moveLocal(-6.25, Vector3(0, 0, 1));
  
    data.clear();
    indices.clear();

   NormalsMesh* randomVertexNormals = new NormalsMesh(context, l_shader,  Vector3(	1, 0, 0), Vector3(1, 0, 0), Vector3(0.7, 0.6, 0.6), 
      Vector3(1, 0, 0), 0.25);
    std::vector<Vector3> randVertexNorms = computeVertexNormals(cube, randFaceNorms);
    indexData(dataWithVertexNormals(cube, randVertexNorms), randomVertexNormals->getFloatsPerVertex(), data, indices);
    randomVertexNormals->addGeometry(data);
    randomVertexNormals->addIndices(indices);
    randomVertexNormals->prepareVao();
    this->add("randomVertexNormals", randomVertexNormals);
    randomVertexNormals->moveLocal(5, Vector3(0, 0, 1));
    randomVertexNormals->moveLocal(1.5, Vector3(0, 1, 0));

    NormalsMesh* grass = new NormalsMesh(context, l_shader, "models/grass.obj", 0, Vector3(0, 0, 0), Vector3(0.1,	0.35,	0.1), Vector3(0.45,	0.55,	0.45), 
      Vector3(0, 0, 0), 0.25);
    grass->prepareVao();
    this->add("grass", grass);
    grass->scaleLocal(2);
    grass->moveLocal(-2, Vector3(0, 1, 0));
    grass->pitch(90);
    
    
    NormalsMesh* castle = new NormalsMesh(context, l_shader, "models/Castle OBJ.obj", 0, Vector3(0.19225,	0.19225,	0.19225	), Vector3(0.50754,	0.50754,	0.50754), Vector3(0.508273,	0.508273,	0.508273), 
      Vector3(0.5, 0.5, 0.5), 0.4);
    castle->prepareVao();
    this->add("castle", castle);
    castle->scaleLocal(0.5);
    castle->moveLocal(20, Vector3(0, 0, 1));
    castle->moveLocal(-7, Vector3(0, 1, 0));

    NormalsMesh* tree = new NormalsMesh(context, l_shader, "models/tree.obj", 0, Vector3(0.19125,	0.0735,	0.0225	), Vector3(0.7038,	0.27048,	0.0828), Vector3(0.256777,	0.137622,	0.086014), 
      Vector3(), 0.1);
    tree->prepareVao();
    this->add("tree", tree);
    tree->scaleLocal(0.25);
    tree->moveLocal(-10, Vector3( 2, 0, 0));
    tree->moveLocal(-13, Vector3(0, 1, 0));
    tree->moveLocal(20, Vector3(0, 0, 1));

    NormalsMesh* wizard = new NormalsMesh(context, l_shader, "models/wizard.obj", 0, Vector3(0.135,	0.2225,	0.1575), Vector3(0.54,	0.89,	0.63), Vector3(0.316228,	0.316228,	0.316228), 
      Vector3(0, 0, 0.5), 0.1);
    wizard->prepareVao();
    this->add("wizard", wizard);
    wizard->scaleWorld(0.5);
    wizard->moveLocal(-22, Vector3( 1, 0, 0));
    wizard->moveLocal(2.5, Vector3(0, 1, 0));
    wizard->moveLocal(-12.5, Vector3(0, 0, 1));
    wizard->pitch(-90);
    wizard->roll(45);
}



/* 
      Vector3(0.0215,	0.1745,	0.0215), Vector3(0.07568, 0.61424,	0.07568), Vector3(0.633,	0.727811,	0.633), 
      Vector3(0.5, 0.5, 0.5), 0.6)
 */