/// \file Main.cpp
/// \brief Declaration of main function, helper functions, and helper classes.
/// \author Gary M. Zopetti, Chad Hogg, John Shenk
/// \version A02
///
/// This is a fairly simple program that uses OpenGL 3.3 to draw a scene.  It
///   allows limited movement of a very simple virtual camera.


/******************************************************************/
// System includes
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <thread>

// Use GLEW so we can access the latest OpenGL functionality
// Always include GLEW before GLFW!
#include <GL/glew.h>
// Use GLFW so we can create windows and handle events in a
//   platform-independent way
#include <GLFW/glfw3.h>

// GLM is a header-only library, so we do not need to link to it
// It provides matrix classes and mathematical functions
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
// Need for "value_ptr", which allows us to get a pointer from a matrix
#include <glm/gtc/type_ptr.hpp>
// Transforms like lookat, perspective, rotate, scale, translate
#include <glm/gtc/matrix_transform.hpp>


/******************************************************************/
// Local includes
#include "RealOpenGLContext.hpp"
#include "ShaderProgram.hpp"
#include "Mesh.hpp"
#include "Scene.hpp"
#include "myScene.hpp"
#include "Camera.hpp"
#include "Vector3.hpp"
#include "KeyBuffer.hpp"
#include "Transform.hpp"
#include "MouseBuffer.hpp"
#include <chrono>
#include "LightSource.hpp"


/******************************************************************/
// Local types


/******************************************************************/
// Global variables

/// \brief The OpenGLContext through which all OpenGL calls will be made.
///
/// This should be allocated in ::init and deallocated in ::releaseGlResources.
OpenGLContext* g_context;

// We use one VAO for each object we draw
/// \brief A collection of the VAOs for each of the objects we want to draw.
///
/// This will be initialized in initScene, and its contents need to be deleted in
///   releaseGlResources.
Scene* my_Scene;

/// \brief The ShaderProgram that transforms and lights the primitives.
///
/// This should be allocated in ::initShaders and deallocated in
///   ::releaseGlResources.
ShaderProgram* g_shaderProgram;

/// \brief The ShaderProgram that uses Vec3Norm.vert
///
/// This should be allocated in ::initShaders and deallocated in
///   ::releaseGlResources.
ShaderProgram* g_shaderNorm;

/// \brief The Camera that views the Scene.
///
/// This should be allocated in ::initCamera and deallocated in
///   ::releaseGlResources.
Camera* g_camera;

/// \brief The KeyBuffer that is told when a key is pressed down.
///
/// This should be allocated in ::recordKeys and deallocated in 
///   ::releaseGlResources
KeyBuffer* buffer;

/// \brief The MouseBuffer that is told when a mouse button is pressed down
///
/// This should be allocated in ::recordKeys and deallocated in 
///   ::releaseGlResources
MouseBuffer* m_buffer;
/******************************************************************/
// Function prototypes

/// \brief Initializes all libraries and global variables.
/// \param[out] window A pointer that will be filled with a GLFWwindow.
///
/// This should be called once at the beginning of the application.
void
init (GLFWwindow*& window);

/// \brief Initializes the GLFW library.  Should only be called by ::init.
void
initGlfw ();

/// \brief Initializes the GLEW library.  Should only be called by ::init.
void
initGlew ();

/// \brief Creates and initializes the window.  Should only be called by
///   ::init.
/// \param[out] window A pointer that will be filled with a GLFWwindow.
void
initWindow (GLFWwindow*& window);

/// \brief Re-renders the window.  This should be called whenever the window
///   size changes.
/// \param[in] window The GLFWwindow to reset.
/// \param[in] width The new width of the window.
/// \param[in] height The new height of the window.
void
resetViewport (GLFWwindow* window, int width, int height);

/// \brief Creates the Scene.  Should only be called by ::init.
void
initScene ();

/// \brief Creates the ShaderProgram.  Should only be called by ::init.
void
initShaders ();

/// \brief Initializes the Camera.  Should only be called by ::init.
void
initCamera ();

/// \brief Moves geometric objects around using game logic.  This should be
///   called for every frame.
/// \param[in] time The number of seconds since the previous update.
void
updateScene (double time);

/// \brief Draws the Scene onto the window.  This should be called for every
///   frame.
/// \param[in] window The GLFWwindow to draw in.
void
drawScene (GLFWwindow* window);

/// \brief Responds to any user input.  This should be set as a callback.
/// \param[in] window The GLFWwindow the input came from.
/// \param[in] key The key that was pressed or released.
/// \param[in] scanCode The system-specific scancode of the key.
/// \param[in] action What happened to the key.
/// \param[in] modifiers Which modifier keys were depressed.
void
recordKeys (GLFWwindow* window, int key, int scanCode, int action,
         int modifiers);

/// \brief Processes the keys pressed, asking the keyBuffer which Keys are pressed. 
void
processKeys();

/// \brief Cleans up all resources as program exits.
void
releaseGlResources ();

/// \brief Prints an error from GLFW.
/// \param[in] error The error code.
/// \param[in] description The error text.
void
outputGlfwError (int error, const char* description);

/// \brief Records mouse buttons
/// \param[in] window The window
/// \param[in] button The button that is interacted with
/// \param[in] action The action performed
void 
recordMouseButtons (GLFWwindow *window, int key, int action, int mods);

/// \brief Records mouse buttons
/// \param[in] window The window
/// \param[in] x The x pos of cursor
/// \param[in] y the y pos of cursor
static
void 
recordMousePosition (GLFWwindow *window, double x, double y);

void 
scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

void knightSpin();

float fov = 50.0;
/******************************************************************/

/// \brief Runs our program.
/// \param[in] argc The number of command-line arguments, which we ignore.
/// \param[in] argv The array of command-line-arguments, which we ignore.
int
main (int argc, char* argv[])
{
  
  GLFWwindow* window;
  init (window);
  if (glfwRawMouseMotionSupported())
    glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
  // Game/render loop
  double previousTime = glfwGetTime ();
  bool knightReady = false;
  //Transform wiz = my_Scene->getMesh("wizard")->getWorld();
  float back = -0.065;
  float up = -0.01;
  float right = 0.009;
  while (!glfwWindowShouldClose (window))
  {
    Transform world = my_Scene->getMesh("knight")->getWorld(); 
    
    double currentTime = glfwGetTime ();
    // Compute frame times, which we can use later for frame rate computation,
    //   animation, and physics.
    double deltaTime = currentTime - previousTime;
    previousTime = currentTime;
    updateScene (deltaTime);
    drawScene (window);
    // Process events in the event queue, which results in callbacks
    //   being invoked.
    glfwPollEvents ();
    processKeys();

    if(!knightReady)
    {
      my_Scene->getMesh("knight")->moveWorld(0.01, Vector3(0, 0, -1));
      if(world.getPosition().m_z < 10)
      {
        knightReady = true;
      } 
    }
    else
    {
      my_Scene->getMesh("knight")->rotateLocal(300, Vector3(0, 0, 1));
      my_Scene->getMesh("knight")->moveWorld(0.1, Vector3(0, 0.5, -1)); 
      if(world.getPosition().m_y > -2)
      {
        my_Scene->getMesh("dragon")->pitch(50);
        my_Scene->getMesh("dragon")->moveWorld(0.1, Vector3(0.1, 0.5, -1)); 
        my_Scene->getMesh("randomVertexNormals")->pitch(50);
        my_Scene->getMesh("randomVertexNormals")->moveWorld(0.1, Vector3(0.1, 0.5, -1)); 
        if(world.getPosition().m_y > 1)
        {
          g_camera->moveBack(back);
          g_camera->moveRight(up);
          g_camera->moveUp(right);
          if(g_camera->getViewMatrix().getPosition().m_z > 10.25)
          {
            back = 0;
            up = 0;
            right = 0;
          }
        }

      } 
    }
    my_Scene->getMesh("randomFaceNormals")->pitch(50);
    my_Scene->getMesh("randomVertexNormals")->roll(200);
    my_Scene->getMesh("randomVertexNormals")->pitch(200);
    my_Scene->getMesh("randomVertexNormals")->yaw(200);
  }


  releaseGlResources ();
  // Destroying the window destroys the OpenGL context
  glfwDestroyWindow (window);
  glfwTerminate ();

  return EXIT_SUCCESS;
}

/******************************************************************/

void
init (GLFWwindow*& window)
{
  g_context = new RealOpenGLContext ();
  buffer = new KeyBuffer();
  m_buffer = new MouseBuffer();
  // Always initialize GLFW before GLEW
  initGlfw ();
  initWindow (window);
  initGlew ();
  initShaders ();
  initCamera ();
  initScene ();
}

/******************************************************************/

void
initGlfw ()
{
  glfwSetErrorCallback (outputGlfwError);
  if (!glfwInit ())
  {
    fprintf (stderr, "Failed to init GLFW -- exiting\n");
    exit (EXIT_FAILURE);
  }
}

/******************************************************************/

void
initWindow (GLFWwindow*& window)
{
  
  glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
#ifdef __APPLE__
  // Necessary on MacOS! Was needed in one case on Linux too.
  glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif
  window = glfwCreateWindow (800, 600, "OpenGL Engine", nullptr, nullptr);
  if (window == nullptr)
  {
    fprintf (stderr, "Failed to init the window -- exiting\n");
    glfwTerminate ();
    exit (EXIT_FAILURE);
  }
  glfwSetWindowPos (window, 200, 100);

  glfwMakeContextCurrent (window);
  // Swap buffers after 1 frame
  glfwSwapInterval (1);
  glfwSetKeyCallback (window, recordKeys);
  glfwSetCursorPosCallback(window, recordMousePosition);
  glfwSetMouseButtonCallback(window, recordMouseButtons);
  glfwSetScrollCallback(window, scroll_callback);
  glfwSetFramebufferSizeCallback (window, resetViewport);
  // Specify background color
  g_context->clearColor (0.0f, 0.0f, 0.0f, 1.0f);
  // Enable depth testing so occluded surfaces aren't drawn
  g_context->enable (GL_DEPTH_TEST);
  // Enable the culling of back-facing triangles
  // A triangle must be wound CCW in window coordinates to be front facing
  // If it is wound CW it is back facing and will NOT be displayed!
  g_context->enable (GL_CULL_FACE);
  // The next two setting are default, but we'll be explicit.
  g_context->frontFace (GL_CCW);
  g_context->cullFace (GL_BACK);
  // Set initial viewport size
  int width, height;
  glfwGetFramebufferSize (window, &width, &height);
  g_context->viewport (0, 0, width, height);
}

/******************************************************************/

void
initGlew ()
{
 
  GLenum status = glewInit ();
  if (status != GLEW_OK)
  {
    fprintf (stderr, "Failed to initialize GLEW -- exiting"
         " (%s).\n",
         glewGetErrorString (status));
    exit (EXIT_FAILURE);
  }
  const GLubyte* version = glewGetString (GLEW_VERSION);
  fprintf (stderr, "Using GLEW version %s.\n", version);
  version = g_context->getString (GL_VERSION);
  fprintf (stderr, "Using OpenGL version %s\n", version);
}

/******************************************************************/

void
resetViewport (GLFWwindow* window, int width, int height)
{
  // Render into entire window
  // Origin for window coordinates is lower-left of window
  g_context->viewport (0, 0, width, height);

  g_camera->setProjectionSymmetricPerspective(50.0, (double)width / height, 0.01, 40.0);
  Transform modelView = g_camera->getViewMatrix();
  my_Scene->draw(modelView, g_camera->getProjectionMatrix());
}

/******************************************************************/

void
initScene ()
{
  
  my_Scene = new myScene(2, g_context, g_shaderProgram, g_shaderNorm);
}

/******************************************************************/

void
initShaders ()
{
  // Create shader programs, which consist of linked shaders.
  // No need to use the program until we draw or set uniform variables.
  g_shaderProgram = new ShaderProgram (g_context);
  g_shaderProgram->createVertexShader ("Vec3.vert");
  g_shaderProgram->createFragmentShader ("Vec3.frag");
  g_shaderProgram->link ();

  g_shaderNorm = new ShaderProgram (g_context);
  g_shaderNorm->createVertexShader ("GeneralShader.vert");
  g_shaderNorm->createFragmentShader ("GeneralShader.frag");
  g_shaderNorm->link ();
}

/******************************************************************/

void
initCamera ()
{
  
  float verticalFov = 50;
  float aspectRatio = 1200.0f / 900;
  // Near plane
  float nearZ = 0.01f;
  // Far plane
  float farZ = 40.0f;
  Vector3 position (0.0f, 0.0f, 12.0f);
  Vector3 at (0.0f, 0.0f, 1.0f);

  //Set up camera
  g_camera = new Camera(position, at, nearZ, farZ, aspectRatio, verticalFov);
  g_camera->moveRight(5);
  g_camera->yaw(30);
  g_camera->moveBack(7);
  
  
}

/******************************************************************/

void
updateScene (double time)
{
  // No updates in this simple program.
}

/******************************************************************/

void
drawScene (GLFWwindow* window)
{
  g_context->clear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
  // Set shader uniforms
  // Only the model-view matrix needs set, since the projection is
  //   already set and it will persist.
  // Create view matrix
  Transform modelView = g_camera->getViewMatrix();
  my_Scene->draw(modelView, g_camera->getProjectionMatrix());
  // Swap the front and back buffers.
  // We draw to the back buffer, which is then swapped with the front
  //   for display.
  //Set astive mesh
  
  glfwSwapBuffers (window);
}


/******************************************************************/

void
recordKeys (GLFWwindow* window, int key, int scanCode, int action,
         int modifiers)
{
  // Actions are GLFW_PRESS, GLFW_RELEASE, and GLFW_REPEAT
  // Exit if ESC is pressed
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
  {
    glfwSetWindowShouldClose (window, GL_TRUE);
    return;
  }
  
  //Set Key Down
  if(action == GLFW_PRESS)
  {
    buffer->setKeyDown(key);
  }

  //Set key up
  if(action == GLFW_RELEASE)
  {
    buffer->setKeyUp(key);
  } 

  //Reset position
  if (key == GLFW_KEY_R && action == GLFW_PRESS)
    g_camera->resetPose();
  
}
/********************************************************************************************/

void 
recordMouseButtons (GLFWwindow *window, int key, int action, int mods)
{
  if(key == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    m_buffer->setLeftButton(true);
  if(key == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    m_buffer->setLeftButton(false);
  if(key == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    m_buffer->setRightButton(true);
  if(key == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
    m_buffer->setRightButton(false);
}

/********************************************************************************************/

void 
scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
  if(!g_camera->isSymmetric())
    g_camera->setProjectionSymmetricPerspective(fov, 1200.0f / 900.0f, 0.1, 40.0);

  if(yoffset < m_buffer->getY())
  {
    fov++;
    if(fov > 120.0f)
      fov = 120.0f;
    g_camera->setProjectionSymmetricPerspective(fov, 1200.0f / 900.0f, 0.1, 40.0);
  }
    
  if(yoffset > m_buffer->getY())
  {
    fov--;
    if(fov < 1.0f)
      fov = 1.0f;
    g_camera->setProjectionSymmetricPerspective(fov, 1200.0f / 900.0f, 0.1, 40.0);
  }
}
/********************************************************************************************/
static
void 
recordMousePosition (GLFWwindow *window, double x, double y)
{
  // Left Button
  if(m_buffer->getLeftButton())
  {
    if(x < m_buffer->getX())
    {
      g_camera->yaw(1.5f);
      m_buffer->setPosition(x, y);
    }
    if(x > m_buffer->getX())
    {
      g_camera->yaw(-1.5f);
      m_buffer->setPosition(x, y);
    }
    if(y < m_buffer->getY())
    {
      g_camera->pitch(1.5f);
      m_buffer->setPosition(x, y);
    }
    if(y > m_buffer->getY())
    {
      g_camera->pitch(-1.5f);
      m_buffer->setPosition(x, y);
    }
  }

  if(m_buffer->getRightButton())
  {
    if(y < m_buffer->getY())
    {
      g_camera->roll(1.5f);
      m_buffer->setPosition(x, y);
    }
    if(y > m_buffer->getY())
    {
      g_camera->roll(-1.5f);
      m_buffer->setPosition(x, y);
    }
  }
}

/********************************************************************************************/

void 
processKeys()
{
  const float MOVEMENT_DELTA = 0.5f;
  if (buffer->isKeyDown(GLFW_KEY_W))
  {
    g_camera->moveBack(-MOVEMENT_DELTA);
    
  }
    
  if (buffer->isKeyDown(GLFW_KEY_S))
    g_camera->moveBack(MOVEMENT_DELTA);
  // TODO: Add support for movement along x and y axes

  ////////////////////////////////////////////CAMERA CONTROLS////
  // x-axis - camera
  if (buffer->isKeyDown(GLFW_KEY_A))
    g_camera->moveRight(-MOVEMENT_DELTA);
  if (buffer->isKeyDown(GLFW_KEY_D))
    g_camera->moveRight(MOVEMENT_DELTA);

  // y-axis - camera
  if (buffer->isKeyDown(GLFW_KEY_C))
    g_camera->moveUp(-MOVEMENT_DELTA);
  if (buffer->isKeyDown(GLFW_KEY_F))
    g_camera->moveUp(MOVEMENT_DELTA);
  ///////////////////////
  
  /////MESH CONTROLS/////
  // Yawing
  if(buffer->isKeyDown(GLFW_KEY_J))
    my_Scene->getActiveMesh()->yaw(7.5f);
  if(buffer->isKeyDown(GLFW_KEY_L))
    my_Scene->getActiveMesh()->yaw(-7.5f);

  // Pitching
  if(buffer->isKeyDown(GLFW_KEY_I))
    my_Scene->getActiveMesh()->pitch(7.5f);
  if(buffer->isKeyDown(GLFW_KEY_K))
    my_Scene->getActiveMesh()->pitch(-7.5f);
  
  // Rolling
  if(buffer->isKeyDown(GLFW_KEY_N))
    my_Scene->getActiveMesh()->roll(7.5f);
  if(buffer->isKeyDown(GLFW_KEY_M))
    my_Scene->getActiveMesh()->roll(-7.5f);

  // Moving Right Axis
  if(buffer->isKeyDown(GLFW_KEY_1))
    my_Scene->getActiveMesh()->moveRight(1.0f);
  if(buffer->isKeyDown(GLFW_KEY_2))
    my_Scene->getActiveMesh()->moveRight(-1.0f);

  //Moving Up Axis
  if(buffer->isKeyDown(GLFW_KEY_3))
    my_Scene->getActiveMesh()->moveUp(1.0f);
  if(buffer->isKeyDown(GLFW_KEY_4))
    my_Scene->getActiveMesh()->moveUp(1.0f);

  // Moving Back Axis
  if(buffer->isKeyDown(GLFW_KEY_5))
    my_Scene->getActiveMesh()->moveBack(1.0f);
  if(buffer->isKeyDown(GLFW_KEY_6))
    my_Scene->getActiveMesh()->moveBack(-1.0f);

  // Scaling
  if(buffer->isKeyDown(GLFW_KEY_7))
    my_Scene->getActiveMesh()->scaleLocal(1.01f);
  if(buffer->isKeyDown(GLFW_KEY_8))
    my_Scene->getActiveMesh()->scaleLocal(0.99f);

  // Activating previous mesh
  if(buffer->isKeyDown(GLFW_KEY_MINUS))
    my_Scene->activatePreviousMesh();

  // Activating next mesh
  if(buffer->isKeyDown(GLFW_KEY_EQUAL))
    my_Scene->activateNextMesh();

  // Set camera to symmetric projection
  if(buffer->isKeyDown(GLFW_KEY_P))
  {
    g_camera->setProjectionSymmetricPerspective(50.0, 4.0 / 3.0, 0.01, 40.0);
    Transform modelView = g_camera->getViewMatrix();
    my_Scene->draw(modelView, g_camera->getProjectionMatrix());
  }

  // Set camera to asymmetirc projection
  if(buffer->isKeyDown(GLFW_KEY_LEFT_BRACKET))
  {
    g_camera->setProjectionAsymmetricPerspective(-7.0, 5.0, -5.0, 3.0, 5.0, 40.0);
    Transform modelView = g_camera->getViewMatrix();
    my_Scene->draw(modelView, g_camera->getProjectionMatrix());
  }

  // Set camera to orthographic projection
  if(buffer->isKeyDown(GLFW_KEY_O))
  {
    g_camera->setProjectionOrthographic(-20.0, 20.0, -15.0, 15.0, 0.01, 40.0);
    Transform modelView = g_camera->getViewMatrix();
    my_Scene->draw(modelView, g_camera->getProjectionMatrix());
  }
    
}
/******************************************************************/

void
releaseGlResources ()
{
  // Delete OpenGL resources, particularly important if program will
  //   continue running
  delete my_Scene;
  delete g_camera;
  delete g_shaderProgram;
  delete g_context;
  delete m_buffer;
  delete buffer;
  //delete g_shaderNorm;
}

/******************************************************************/

void
outputGlfwError (int error, const char* description)
{
  fprintf (stderr, "GLFW error: %s, code %d\n", description, error);
}

/******************************************************************/

/* For safe-keeping:
  
  // Translate camera/eye point using WASD keys
  const float MOVEMENT_DELTA = 1.0f;
  if (key == GLFW_KEY_W && action == GLFW_PRESS)
    g_camera->moveBack(-MOVEMENT_DELTA);
  else if (key == GLFW_KEY_S && action == GLFW_PRESS)
    g_camera->moveBack(MOVEMENT_DELTA);
  // TODO: Add support for movement along x and y axes

  */

void
knightSpin()
{
    my_Scene->getMesh("knight")->rotateLocal(300, Vector3(0, 0, 1));
    my_Scene->getMesh("knight")->moveWorld(0.1, Vector3(0, 0.5, -1));  
}