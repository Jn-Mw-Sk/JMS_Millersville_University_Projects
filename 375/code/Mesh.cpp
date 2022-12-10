/// \file Mesh.cpp
/// \brief Implementation of Mesh class and any associated global functions.
/// \author John Shenk
/// \version A02



#include <vector>

#include <glm/mat4x4.hpp>

#include "OpenGLContext.hpp"
#include "ShaderProgram.hpp"
#include "Mesh.hpp"


  /// \brief Constructs an empty Mesh with no triangles.
  /// \param context A pointer to an object through which the Mesh will be able
  ///   to make OpenGL calls.
  /// \post A unique VAO and VBO have been generated for this Mesh and stored
  ///   for later use.
  Mesh::Mesh (OpenGLContext* context, ShaderProgram* shader){
      m_context = context;
      m_shader = shader;
      m_context->genVertexArrays (1, &m_vao);
      m_context->genBuffers (1, &m_vbo);
      m_context->genBuffers (1, &m_ibo);
      m_material = new Material(m_shader);
      m_ambientReflection = Vector3(0, 0, 0);
      m_diffuseReflection = Vector3(0.01, 0.01, 0.01);
      m_specularReflection = Vector3(0.5, 0.5, 0.5);
      m_emissiveIntensity = Vector3(1, 1, 1);
      m_SpecularPower = 0.25;
  }

  Mesh::Mesh (OpenGLContext* context, ShaderProgram* shader, 
    Vector3 ambientReflection, Vector3 diffuseReflection, Vector3 specularReflection, 
    Vector3 emissiveIntensity, float specularPower)
    {
      m_context = context;
      m_shader = shader;
      m_context->genVertexArrays (1, &m_vao);
      m_context->genBuffers (1, &m_vbo);
      m_context->genBuffers (1, &m_ibo);
      m_material = new Material(shader);
      m_ambientReflection = ambientReflection;
      m_diffuseReflection = diffuseReflection;
      m_specularReflection = specularReflection;
      m_emissiveIntensity = emissiveIntensity;
      m_SpecularPower = specularPower;
    }

  /// \brief Destructs this Mesh.
  /// \post The VAO and VBO associated with this Mesh have been deleted.
  Mesh::~Mesh (){
    m_context->deleteVertexArrays (1, &m_vao);
    m_context->deleteBuffers(1, &m_vbo);
  }


  /// \brief Adds the geometry of [additional] triangles to this Mesh.
  /// \param[in] geometry A collection of vertex data for 1 or more triangles.
  ///   Each vertex must contain interleaved 3-D position and 3-D color data
  ///   (X, Y, Z, R, G, B) and the vector must contain complete triangles (3
  ///   vertices each).
  /// \pre This Mesh has not yet been prepared.
  /// \post The geometry has been appended to this Mesh's internal geometry
  ///   store for future use.
  void
  Mesh::addGeometry (const std::vector<float>& geometry)
  {
    
    for(float index : geometry)
    {
      m_geometry.push_back(index);
    }
     
  }

  /// \brief Copies this Mesh's geometry into this Mesh's VBO and sets up its
  ///   VAO.
  /// \pre This Mesh has not yet been prepared.
  /// \post The first two vertex attributes have been enabled, with
  ///   interleaved 3-part positions and 3-part colors.
  /// \post This Mesh's geometry has been copied to its VBO.
  void
  Mesh::prepareVao (){
  
    m_context->bindVertexArray(m_vao);
    m_context->bindBuffer (GL_ARRAY_BUFFER, m_vbo);
    m_context->bufferData (GL_ARRAY_BUFFER, m_geometry.size() * sizeof(float),
			m_geometry.data (), GL_STATIC_DRAW);
    m_context->bindBuffer (GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    m_context->bufferData (GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned),
      m_indices.data(), GL_STATIC_DRAW);
      
    enableAttributes();
    m_context->bindVertexArray (0);

  }

  /// \brief Draws this Mesh in OpenGL.
  /// \param[in] shaderProgram A pointer to the ShaderProgram that should
  ///   be used.
  /// \param[in] viewMatrix The view matrix that should be used by itself as
  ///   the model-view matrix (there is not yet any model part).
  /// \pre This Mesh has been prepared.
  /// \post While the ShaderProgram was enabled, the viewMatrix has been set as
  ///   the "uModelView" uniform matrix and the geometry has been drawn.
  void
  Mesh::draw (const Transform viewMatrix, Matrix4 projectionMatrix)
  {  
    m_material->setUniforms(m_ambientReflection, m_diffuseReflection, m_specularReflection, m_emissiveIntensity, m_SpecularPower);

    m_shader->enable();

    Transform c = viewMatrix;
    c.combine(m_world);

    m_shader->setUniformMatrix ("uProjection", projectionMatrix);
    m_shader->setUniformMatrix("uModelView", c.getTransform());
    m_shader->setUniformMatrix("uView", viewMatrix.getTransform());
    m_shader->setUniformMatrix("uWorld", m_world.getTransform());
    
    m_context->bindVertexArray(m_vao);
    m_context->drawElements (GL_TRIANGLES , m_indices.size () , GL_UNSIGNED_INT, reinterpret_cast<void*>(0) ) ;
    m_context->bindVertexArray(0);

    m_shader->disable();
  }

 /// \brief Gets the mesh's world matrix.
  /// \return The world matrix.
  Transform
  Mesh::getWorld () const
  {
    return m_world;
  }

  /// \brief Moves the mesh right (locally).
  /// \param[in] distance The distance to move the mesh.
  /// \post The mesh has been moved.
  void
  Mesh::moveRight (float distance)
  {
    m_world.moveRight(distance);
  }

  /// \brief Moves the mesh up (locally).
  /// \param[in] distance The distance to move the mesh.
  /// \post The mesh has been moved.
  void
  Mesh::moveUp (float distance)
  {
    m_world.moveUp(distance);
  }

  /// \brief Moves the mesh back (locally).
  /// \param[in] distance The distance to move the mesh.
  /// \post The mesh has been moved.
  void
  Mesh::moveBack (float distance)
  {
    m_world.moveUp(distance);
  }

  /// \brief Moves the mesh in some local direction.
  /// \param[in] distance How far to move the mesh.
  /// \param[localDirection] The (local) direction to move the mesh in.
  /// \post The mesh has been moved.
  void
  Mesh::moveLocal (float distance, const Vector3& localDirection)
  {
    m_world.moveLocal(distance, localDirection);
  }

  /// \brief Moves the mesh in some world direction.
  /// \param[in] distance How far to move the mesh.
  /// \param[in] worldDirection The (world) direciton to move the mesh in.
  /// \post The mesh has been moved.
  void
  Mesh::moveWorld (float distance, const Vector3& worldDirection)
  {
    m_world.moveWorld(distance, worldDirection);
  }

  /// \brief Rotates the mesh around its own local right axis.
  /// \param[in] angleDegrees How much to rotate.
  /// \post The mesh has been rotated.
  void
  Mesh::pitch (float angleDegrees)
  {
    m_world.pitch(angleDegrees);
  }

  /// \brief Rotates the mesh around its own local up axis.
  /// \param[in] angleDegrees How much to rotate.
  /// \post The mesh has been rotated.
  void
  Mesh::yaw (float angleDegrees)
  {
    m_world.yaw(angleDegrees);
  }

  /// \brief Rotates the mesh around its own local back axis.
  /// \param[in] angleDegrees How much to rotate.
  /// \post The mesh has been rotated.
  void
  Mesh::roll (float angleDegrees)
  {
    m_world.roll(angleDegrees);
  }

  /// \brief Rotates the mesh around some local direction.
  /// \param[in] angleDegrees How much to rotate.
  /// \param[in] axis The (local) direction to rotate around.
  /// \post The mesh has been rotated.
  void
  Mesh::rotateLocal (float angleDegrees, const Vector3& axis)
  {
    m_world.rotateLocal(angleDegrees, axis);
  }

  /// \brief Aligns the mesh with the world Y axis.
  /// \post The mesh's local up axis is (0, 1, 0).
  /// \post The mesh's local right and back axes perpendicular to each other
  ///   and to its local up axis.
  void
  Mesh::alignWithWorldY ()
  {
    m_world.alignWithWorldY();
  }

  /// \brief Scales the mesh (locally).
  /// \param[in] scale The amount to scale.
  /// \post The mesh has been scaled.
  void
  Mesh::scaleLocal (float scale)
  {
    m_world.scaleLocal(scale);
  }

  /// \brief Scales the mesh (locally).
  /// \param[in] scaleX the amount to scale in the local right direction.
  /// \param[in] scaleY The amount to scale in the local up direction.
  /// \param[in] scaleZ The amount to scale in the local back direction.
  /// \post The mesh has been scaled.
  void
  Mesh::scaleLocal (float scaleX, float scaleY, float scaleZ)
  {
    m_world.scaleLocal(scaleX, scaleY, scaleZ);
  }
    
  /// \brief Scales the mesh (worldly).
  /// \param[in] scale The amount to scale.
  /// \post The mesh has been scaled.
  void
  Mesh::scaleWorld (float scale)
  {
    m_world.scaleWorld(scale);
  }

  /// \brief Scales the mesh (worldly).
  /// \param[in] scaleX The amount to scale in the world right direction.
  /// \param[in] scaleY The amount to scale in the world up direction.
  /// \param[in] scaleZ The amount to scale in the world back direction.
  /// \post The mesh has been scaled.
  void
  Mesh::scaleWorld (float scaleX, float scaleY, float scaleZ)
  {
    m_world.scaleWorld(scaleX, scaleY, scaleZ);
  }

  /// \brief Shears the mesh's local X by its local Y and local Z.
  /// \param[in] shearY How much local Y to add to X.
  /// \param[in] shearZ How much local Z to add to X.
  /// \post The mesh has been sheared.
  void
  Mesh::shearLocalXByYz (float shearY, float shearZ)
  {
    m_world.shearLocalXByYz(shearY, shearZ);
  }

  /// \brief Shears the mesh's local Y by its local X and local Z.
  /// \param[in] shearX How much local X to add to Y.
  /// \param[in] shearZ How much local Z to add to Y.
  /// \post The mesh has been sheared.
  void
  Mesh::shearLocalYByXz (float shearX, float shearZ)
  {
    m_world.shearLocalYByXz(shearX, shearZ);
  }

  /// \brief Shears the mesh's local Z by its local X and local Y.
  /// \param[in] shearX How much local X to add to Z.
  /// \param[in] shearY How much local Y to add to Z.
  /// \post The mesh has been sheared.
  void
  Mesh::shearLocalZByXy (float shearX, float shearY)
  {
    m_world.shearLocalZByXy(shearX, shearY);
  }

/// \brief Adds additional triangles to this Mesh.
/// \param[in] indices A collection of indices into the vertex buffer for 1
///   or more triangles.  There must be 3 indices per triangle.
/// \pre This Mesh has not yet been prepared.
/// \post The indices have been appended to this Mesh's internal index store
///   for future use.
void
Mesh::addIndices (const std::vector<unsigned int>& indices)
{
  m_indices.insert(m_indices.end(), indices.begin(), indices.end());
}


/// \brief Gets the number of floats used to represent each vertex.
/// \return The number of floats used for each vertex.
unsigned int
Mesh::getFloatsPerVertex () const
{
  return (unsigned int)3;
}

/// \brief Enables VAO attributes.
/// \pre This Mesh's VAO has been bound.
/// \post Any attributes (positions, colors, normals, texture coordinates)
///   have been enabled and configured.
/// This should only be called from the middle of prepareVao().
void
Mesh::enableAttributes()
{
  const GLint POSITION_ATTRIB_INDEX = 0;
  // Tell the shaders how the data in the array is laid out
  m_context->enableVertexAttribArray (POSITION_ATTRIB_INDEX);
  // Positions have 3 parts, each are floats, and start at beginning of array
  m_context->vertexAttribPointer (POSITION_ATTRIB_INDEX, 3, GL_FLOAT, GL_TRUE, (6 * sizeof(float)),
			  reinterpret_cast<void*> (0));
}




