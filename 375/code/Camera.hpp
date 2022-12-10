/// \file Camera.hpp
/// \brief Declaration of Camera class and any associated global functions.
/// \author Chad Hogg
/// \version A03

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include "OpenGLContext.hpp"
#include "Vector3.hpp"
#include "Matrix3.hpp"
#include "Transform.hpp"
#include "Matrix4.hpp"

/// \brief An eye that is viewing the scene.
class Camera
{
public:

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
  Camera (const Vector3& eyePosition, const Vector3& localBackDirection,
	  float nearClipPlaneDistance, float farClipPlaneDistance,
	  float aspectRatio, float verticalFieldOfViewDegrees);

  /// \brief Destructs a Camera.
  ~Camera ();
  
  /// \brief Sets the position (eye point) of the camera.
  /// \param[in] position The new position of the camera.
  /// \post The camera's location has been changed.
  void
  setPosition (const Vector3& position);

  /// \brief Moves the position (eye point) of the camera right or left.
  /// \param[in] distance How far to move along the right vector.
  /// \post The camera's location has been changed.
  void
  moveRight (float distance);

  /// \brief Moves the position (eye point) of the camera up or down.
  /// \param[in] distance How far to move along the up vector.
  /// \post The camera's location has been changed.
  void
  moveUp (float distance);

  /// \brief Moves the position (eye point) of the camera back or forward.
  /// \param[in] distance How far to move along the back vector.
  /// \post The camera's location has been changed.
  void
  moveBack (float distance);

  /// \brief Rotates the camera counterclockwise around the up vector.
  /// \param[in] degrees How far to rotate.
  /// \post The camera's orientation has been changed.
  void
  yaw (float degrees);

  /// \brief Gets the view matrix, recalculating it only if necessary.
  /// \return A view matrix based on the camera's location and axis vectors.
  Transform
  getViewMatrix ();

  /// \brief Recreates the projection matrix with symmetric perspective
  /// \param[in] verticalFovDegrees The viewing angle.
  /// \param[in] aspectRatio The width / height.
  /// \param[in] nearZ The distance to closest visible objects.
  /// \param[in] farZ The distance to furthest visible objects.
  void
  setProjectionSymmetricPerspective (double verticalFovDegrees, double aspectRatio,
		 double nearZ, double farZ); 

  /// \brief Recreates projection Matrix with asymmetric perspective
  /// \param[in] left x value of left side of projection
  /// \param[in] right x value to right of projection
  /// \param[in] bottom y value to bottom of projection
  /// \param[in] top y value to top of projection
  /// \param[in] nearPlaneZ The distance to near clip distance
  /// \param[in] farPLaneZ The distance to far clip distance
  void
  setProjectionAsymmetricPerspective (double left, double right,
	double bottom, double top,
	double nearPlaneZ, double farPlaneZ);

  /// \brief Recreates projection Matrix with orthographic perspective
  /// \param[in] left x value of left side of projection
  /// \param[in] right x value to right of projection
  /// \param[in] bottom y value to bottom of projection
  /// \param[in] top y value to top of projection
  /// \param[in] nearPlaneZ The distance to near clip distance
  /// \param[in] farPLaneZ The distance to far clip distance
  void
  setProjectionOrthographic(double left, double right,
	double bottom, double top,
    double nearPlaneZ, double farPlaneZ);

  /// \brief Gets the projection matrix.
  /// \return The projection matrix.
  Matrix4
  getProjectionMatrix ();

  /// \brief Resets the camera to its original pose.
  /// \post The position (eye point) is the same as what had been specified in
  ///   the constructor.
  /// \post The back vector is the same as what had been specified in the
  ///   constructor.
  /// \post The up and right vectors are computed as they had been in the
  ///   constructor.
  void
  resetPose ();

  //Returns the original eyePosition
  Vector3&
  ogEyePosition();

  // Converts a Vector3 object to glm::vec3
  glm::vec3
  convert2glm(Vector3& v);


  // Converts a glm::vec3 object to Vector3
  Vector3
  convert2Vector3(glm::vec3& v);

  /// \brief Rotates the camera counterclockwise around the right vector
  /// \param[in] degrees How far to rotate.
  /// \post The camera's orientation has been changed.
  void 
  pitch(float degrees);
  
  /// \brief Rotates the camera counterclockwise around the back vector
  /// \param[in] degrees How far to rotate.
  /// \post The camera's orientation has been changed.
  void 
  roll(float degrees);

  /// \brief Returns wheteher or not the camera is in a symmetric pespective
  /// \return The bool symmetric
  bool
  isSymmetric();

private:

  //The Vector and Matrix as a Transform
  Transform m_world;
  /// The projection matrix.
  Matrix4 m_projectionMatrix;
  /// The view matrix.
  Transform m_viewMatrix;

  //the original eye position of the camera, used in resetPose()
  Vector3 originalEyePosition;
  //original back direction
  Vector3 originalBackDirection;

  //Determines if the view matrix should be recalculated
  bool isChanged = true;
  bool symmetric = false;
};

#endif//CAMERA_HPP
