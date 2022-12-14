/// \file Mesh.hpp
/// \brief Declaration of Mesh class and any associated global functions.
/// \author Chad Hogg
/// \version A02

#ifndef MESH_HPP
#define MESH_HPP

#include <vector>

#include <glm/mat4x4.hpp>

#include "OpenGLContext.hpp"
#include "ShaderProgram.hpp"
#include "Camera.hpp"
#include "Transform.hpp"
#include "Matrix4.hpp"
#include "Material.hpp"

/// \brief An object that exists in the world, which consists of one or more
///   3-D triangles.
class Mesh
{
public:

  /// \brief Constructs an empty Mesh with no triangles. Sets default material type
  /// \param context A pointer to an object through which the Mesh will be able
  ///   to make OpenGL calls.
  /// \post A unique VAO and VBO have been generated for this Mesh and stored
  ///   for later use.
  Mesh (OpenGLContext* context, ShaderProgram* shader);

  // \brief Constructs a new mesh with materail properties
  // \param[in] program The shader program we want to use
  // \param[in] ambientRelfection The amount of ambient reflection we want
  // \param[in] diffuseReflection The amount of diffuse  relfection we want
  // \param[in] specularReflection The amount of specular reflection we want
  // \param[in] emissiveIntensity The amount on emissive intensity we want
  // \param[in] specularPower The amount of "shininess" we want on our material
  // \post The parameters have been set to their respective uniforms in the fragment and vertex shaders
  Mesh (OpenGLContext* context, ShaderProgram* shader, 
    Vector3 ambientReflection, Vector3 diffuseReflection, Vector3 specularReflection, Vector3 emissiveIntensity, float specularPower);

  /// \brief Destructs this Mesh.
  /// \post The VAO and VBO associated with this Mesh have been deleted.
  virtual
  ~Mesh ();

  /// \brief Copy constructor removed because you shouldn't be copying Meshes.
  Mesh (const Mesh&) = delete;

  /// \brief Assignment operator removed because you shouldn't be assigning
  ///   Meshes.
  Mesh&
  operator= (const Mesh&) = delete;

  /// \brief Adds the geometry of [additional] triangles to this Mesh.
  /// \param[in] geometry A collection of vertex data for 1 or more triangles.
  ///   Each vertex must contain interleaved 3-D position and 3-D color data
  ///   (X, Y, Z, R, G, B) and the vector must contain complete triangles (3
  ///   vertices each).
  /// \pre This Mesh has not yet been prepared.
  /// \post The geometry has been appended to this Mesh's internal geometry
  ///   store for future use.
  void
  addGeometry (const std::vector<float>& geometry);

  /// \brief Copies this Mesh's geometry into this Mesh's VBO and sets up its
  ///   VAO.
  /// \pre This Mesh has not yet been prepared.
  /// \post The first two vertex attributes have been enabled, with
  ///   interleaved 3-part positions and 3-part colors.
  /// \post This Mesh's geometry has been copied to its VBO.
  void
  prepareVao ();

  /// \brief Draws this Mesh in OpenGL.
  /// \param[in] shaderProgram A pointer to the ShaderProgram that should
  ///   be used.
  /// \param[in] viewMatrix The view matrix that should be used by itself as
  ///   the model-view matrix (there is not yet any model part).
  /// \pre This Mesh has been prepared.
  /// \post While the ShaderProgram was enabled, the viewMatrix has been set as
  ///   the "uModelView" uniform matrix and the geometry has been drawn.
  void
  draw (const Transform viewMatrix, Matrix4 projectionMatrix);
  
  // This file contains functions that should be added to your Mesh class.
// Don't actually put this file into your project -- just copy from it.

  /// \brief Gets the mesh's world matrix.
  /// \return The world matrix.
  Transform
  getWorld () const;

  /// \brief Moves the mesh right (locally).
  /// \param[in] distance The distance to move the mesh.
  /// \post The mesh has been moved.
  void
  moveRight (float distance);

  /// \brief Moves the mesh up (locally).
  /// \param[in] distance The distance to move the mesh.
  /// \post The mesh has been moved.
  void
  moveUp (float distance);

  /// \brief Moves the mesh back (locally).
  /// \param[in] distance The distance to move the mesh.
  /// \post The mesh has been moved.
  void
  moveBack (float distance);

  /// \brief Moves the mesh in some local direction.
  /// \param[in] distance How far to move the mesh.
  /// \param[localDirection] The (local) direction to move the mesh in.
  /// \post The mesh has been moved.
  void
  moveLocal (float distance, const Vector3& localDirection);

  /// \brief Moves the mesh in some world direction.
  /// \param[in] distance How far to move the mesh.
  /// \param[in] worldDirection The (world) direciton to move the mesh in.
  /// \post The mesh has been moved.
  void
  moveWorld (float distance, const Vector3& worldDirection);

  /// \brief Rotates the mesh around its own local right axis.
  /// \param[in] angleDegrees How much to rotate.
  /// \post The mesh has been rotated.
  void
  pitch (float angleDegrees);

  /// \brief Rotates the mesh around its own local up axis.
  /// \param[in] angleDegrees How much to rotate.
  /// \post The mesh has been rotated.
  void
  yaw (float angleDegrees);

  /// \brief Rotates the mesh around its own local back axis.
  /// \param[in] angleDegrees How much to rotate.
  /// \post The mesh has been rotated.
  void
  roll (float angleDegrees);

  /// \brief Rotates the mesh around some local direction.
  /// \param[in] angleDegrees How much to rotate.
  /// \param[in] axis The (local) direction to rotate around.
  /// \post The mesh has been rotated.
  void
  rotateLocal (float angleDegrees, const Vector3& axis);

  /// \brief Aligns the mesh with the world Y axis.
  /// \post The mesh's local up axis is (0, 1, 0).
  /// \post The mesh's local right and back axes perpendicular to each other
  ///   and to its local up axis.
  void
  alignWithWorldY ();

  /// \brief Scales the mesh (locally).
  /// \param[in] scale The amount to scale.
  /// \post The mesh has been scaled.
  void
  scaleLocal (float scale);

  /// \brief Scales the mesh (locally).
  /// \param[in] scaleX the amount to scale in the local right direction.
  /// \param[in] scaleY The amount to scale in the local up direction.
  /// \param[in] scaleZ The amount to scale in the local back direction.
  /// \post The mesh has been scaled.
  void
  scaleLocal (float scaleX, float scaleY, float scaleZ);
    
  /// \brief Scales the mesh (worldly).
  /// \param[in] scale The amount to scale.
  /// \post The mesh has been scaled.
  void
  scaleWorld (float scale);

  /// \brief Scales the mesh (worldly).
  /// \param[in] scaleX The amount to scale in the world right direction.
  /// \param[in] scaleY The amount to scale in the world up direction.
  /// \param[in] scaleZ The amount to scale in the world back direction.
  /// \post The mesh has been scaled.
  void
  scaleWorld (float scaleX, float scaleY, float scaleZ);

  /// \brief Shears the mesh's local X by its local Y and local Z.
  /// \param[in] shearY How much local Y to add to X.
  /// \param[in] shearZ How much local Z to add to X.
  /// \post The mesh has been sheared.
  void
  shearLocalXByYz (float shearY, float shearZ);

  /// \brief Shears the mesh's local Y by its local X and local Z.
  /// \param[in] shearX How much local X to add to Y.
  /// \param[in] shearZ How much local Z to add to Y.
  /// \post The mesh has been sheared.
  void
  shearLocalYByXz (float shearX, float shearZ);

  /// \brief Shears the mesh's local Z by its local X and local Y.
  /// \param[in] shearX How much local X to add to Z.
  /// \param[in] shearY How much local Y to add to Z.
  /// \post The mesh has been sheared.
  void
  shearLocalZByXy (float shearX, float shearY);

  /// \brief Adds additional triangles to this Mesh.
  /// \param[in] indices A collection of indices into the vertex buffer for 1
  ///   or more triangles.  There must be 3 indices per triangle.
  /// \pre This Mesh has not yet been prepared.
  /// \post The indices have been appended to this Mesh's internal index store
  ///   for future use.
  void
  addIndices (const std::vector<unsigned int>& indices);

  /// \brief Gets the number of floats used to represent each vertex.
  /// \return The number of floats used for each vertex.
  virtual unsigned int
  getFloatsPerVertex () const;

/// A material to store material properties of a mesh
  Material* m_material;
protected:
  /// A pointer to the object through which this Mesh will make OpenGL calls.
  OpenGLContext* m_context;

  

  /// \brief Enables VAO attributes.
  /// \pre This Mesh's VAO has been bound.
  /// \post Any attributes (positions, colors, normals, texture coordinates)
  ///   have been enabled and configured.
  /// This should only be called from the middle of prepareVao().
  virtual void
  enableAttributes();
  
private: 
  //A Transform used to perform transformations to our mesh
  Transform m_world;

  // TODO: Add the other data members you think you will need here.
  GLuint m_vao, m_vbo, m_ibo;
  std::vector<float> m_geometry;
  std::vector<unsigned int> m_indices;

  // A shader program used for colors
  ShaderProgram* m_shader;

  // Material properties
  Vector3 m_ambientReflection;
  Vector3 m_diffuseReflection;
  Vector3 m_specularReflection;
  Vector3 m_emissiveIntensity;
  float m_SpecularPower;
};

#endif//MESH_HPP
