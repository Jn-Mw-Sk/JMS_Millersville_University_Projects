/// \file Camera.hpp
/// \brief Implementation of Camera class and any associated global functions.
/// \author John Shenk
/// \version A03



#include <cstdio>
#include <cstdlib>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "RealOpenGLContext.hpp"
#include "OpenGLContext.hpp"
#include "Camera.hpp"

/// \brief Constructs a new Camera.
  ///
  /// \param eyePosition The location (in world coordinates) where the camera
  ///   is located.
  /// \param localBackDirection A vector pointing backwards from the camera.
  /// \param nearClipPlaneDistance The distance to the closest things the
  ///   camera can "see".
  /// \param farClipPlaneDistance The distance to the farthest things the
  ///   camera can "see".
  /// \param aspectRatio The window's width divided by height.
  /// \param verticalFieldOfViewDegrees The angle determining how much the
  ///   camera "sees".
  /// \post The camera's pose has been set and a projection matrix generated.
  /// \post The three orientation vectors are orthonormal with each other.
  /// \post All of the parameters have been copied into their respective data
  ///   members, and the local right and up have been calculated to be
  ///   orthonormal to the local back.
  Camera::Camera (const Vector3& eyePosition, const Vector3& localBackDirection,
	  float nearClipPlaneDistance, float farClipPlaneDistance,
	  float aspectRatio, float verticalFieldOfViewDegrees)
      {
          originalEyePosition = eyePosition;
          originalBackDirection = localBackDirection;
          Matrix3 m_matrix;
          setPosition(eyePosition);
          m_matrix.setBack(localBackDirection);
          setProjectionSymmetricPerspective(verticalFieldOfViewDegrees, aspectRatio, nearClipPlaneDistance, farClipPlaneDistance);
          symmetric = true;
          Vector3 up (0.0f, 1.0f, 0.0f);
          m_matrix.setUp(up);
          m_matrix.orthonormalize();
          m_world.setOrientation(m_matrix);
          m_viewMatrix = m_world;

    }


  /// \brief Destructs a Camera.
  Camera::~Camera ()
  {
      
  }
  
  /// \brief Sets the position (eye point) of the camera.
  /// \param[in] position The new position of the camera.
  /// \post The camera's location has been changed.
  void
  Camera::setPosition (const Vector3& position)
  {
      m_world.setPosition(position);
      isChanged = true;
  }

  /// \brief Moves the position (eye point) of the camera right or left.
  /// \param[in] distance How far to move along the right vector.
  /// \post The camera's location has been changed.
  void
  Camera::moveRight (float distance)
  {
      m_world.setPosition(m_world.getPosition() += m_world.getRight() * distance);
      isChanged = true;
  }

  /// \brief Moves the position (eye point) of the camera up or down.
  /// \param[in] distance How far to move along the up vector.
  /// \post The camera's location has been changed.
  void
  Camera::moveUp (float distance)
  {
      m_world.setPosition(m_world.getPosition() += m_world.getUp() * distance);
      isChanged = true;
  }

  /// \brief Moves the position (eye point) of the camera back or forward.
  /// \param[in] distance How far to move along the back vector.
  /// \post The camera's location has been changed.
  void
  Camera::moveBack (float distance)
  {
      m_world.setPosition(m_world.getPosition() += m_world.getBack() * distance);
      isChanged = true;
  }

  /// \brief Rotates the camera counterclockwise around the up vector.
  /// \param[in] degrees How far to rotate.
  /// \post The camera's orientation has been changed.
  void
  Camera::yaw (float degrees)
  {
      /*
      glm::vec3 glmUp = convert2glm(m_localUpDirection);
      glm::vec3 glmRight = convert2glm(m_localRightDirection); 
      glm::vec3 glmBack = convert2glm(m_localBackDirection);
      glmRight = glm::rotate(glmRight, glm::radians(degrees), glmUp);
      glmBack = glm::rotate(glmBack, glm::radians(degrees), glmUp);
      m_localRightDirection = convert2Vector3(glmRight);
      m_localBackDirection = convert2Vector3(glmBack);
      isChanged = true;
      */
     m_world.yaw(degrees);


     isChanged = true;
  }

  /// \brief Rotates the camera counterclockwise around the right vector
  /// \param[in] degrees How far to rotate.
  /// \post The camera's orientation has been changed.
  void 
  Camera::pitch(float degrees)
  {
    m_world.pitch(degrees);

    isChanged = true;
  }

  /// \brief Rotates the camera counterclockwise around the back vector
  /// \param[in] degrees How far to rotate.
  /// \post The camera's orientation has been changed.
  void
  Camera::roll(float degrees)
  {
      m_world.roll(degrees);
      isChanged = true;
  }

  /// \brief Gets the view matrix, recalculating it only if necessary.
  /// \return A view matrix based on the camera's location and axis vectors.
  Transform
  Camera::getViewMatrix ()
  {
      if(isChanged)
      {
        m_viewMatrix.setOrientation(m_world.getOrientation());
        m_viewMatrix.setPosition(m_world.getPosition());
        m_viewMatrix.invertRt();
        isChanged = false;
      }

      return m_viewMatrix;
  }


  /// \brief Recreates the projection matrix.
  /// \param[in] verticalFovDegrees The viewing angle.
  /// \param[in] aspectRatio The width / height.
  /// \param[in] nearZ The distance to closest visible objects.
  /// \param[in] farZ The distance to furthest visible objects.
  void  
  Camera::setProjectionSymmetricPerspective (double verticalFovDegrees, double aspectRatio,
		 double nearZ, double farZ)
  {
      m_projectionMatrix.setToPerspectiveProjection(verticalFovDegrees, aspectRatio, nearZ, farZ);
  }

/// \brief Recreates projection Matrix with asymmetric perspective
/// \param[in] left x value of left side of projection
/// \param[in] right x value to right of projection
/// \param[in] bottom y value to bottom of projection
/// \param[in] top y value to top of projection
/// \param[in] nearPlaneZ The distance to near clip distance
/// \param[in] farPLaneZ The distance to far clip distance
void 
Camera::setProjectionAsymmetricPerspective(double left, double right,
    double bottom, double top,
	double nearPlaneZ, double farPlaneZ)
{
    m_projectionMatrix.setToPerspectiveProjection(left, right, bottom, top, nearPlaneZ, farPlaneZ);
}

/// \brief Recreates projection Matrix with orthographic perspective
/// \param[in] left x value of left side of projection
/// \param[in] right x value to right of projection
/// \param[in] bottom y value to bottom of projection
/// \param[in] top y value to top of projection
/// \param[in] nearPlaneZ The distance to near clip distance
/// \param[in] farPLaneZ The distance to far clip distance
void 
Camera::setProjectionOrthographic(double left, double right,
	double bottom, double top,
    double nearPlaneZ, double farPlaneZ)
{
    m_projectionMatrix.setToOrthographicProjection(left, right, bottom, top, nearPlaneZ, farPlaneZ);
}

  /// \brief Gets the projection matrix.
  /// \return The projection matrix.
  Matrix4
  Camera::getProjectionMatrix ()
  {
      return m_projectionMatrix;
  }

  /// \brief Resets the camera to its original pose.
  /// \post The position (eye point) is the same as what had been specified in
  ///   the constructor.
  /// \post The back vector is the same as what had been specified in the
  ///   constructor.
  /// \post The up and right vectors are computed as they had been in the
  ///   constructor.
  void
  Camera::resetPose ()
  {
      m_world.setPosition(ogEyePosition());
      Matrix3 m_matrix;
      m_matrix.setBack(originalBackDirection);

      Vector3 up (0.0f, 1.0f, 0.0f);
      m_matrix.setUp(up);
      m_matrix.orthonormalize();
    
      m_world.setOrientation(m_matrix);
      m_viewMatrix = m_world;
      
  }

  Vector3&
  Camera::ogEyePosition()
  {
      return originalEyePosition;
  }

  glm::vec3
  Camera::convert2glm(Vector3& v)
  {
      glm::vec3 vec (v.m_x, v.m_y, v.m_z);
      return vec;
  }

  Vector3
  Camera::convert2Vector3(glm::vec3& v)
  {
      Vector3 vec (v.x, v.y, v.z);
      return vec;
  }
  
  bool 
  Camera::isSymmetric()
  {
      return symmetric;
  }

   