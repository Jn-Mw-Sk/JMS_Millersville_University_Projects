/// \file Scene.cpp
/// \brief Implementation of Scene class and any associated global functions.
/// \author John Shenk
/// \version A02

//////////Local Includes//////////
#include "Scene.hpp"

//////////Function Calls//////////
/// \brief Constructs an empty Scene.
Scene::Scene (ShaderProgram* shader, int lights)
{   
  std::cout<<"Scene Constructor";
 
  l_shader = shader;
  
}

/// \brief Destructs a Scene, freeing the memory used by any Meshes in it.
/// \post Any Meshes that were part of the Scene have been freed.
Scene::~Scene ()
{
  clear();
}


/// \brief Adds a new Mesh to this Scene.
/// \param[in] meshName The name of the Mesh.  Unique names should be used so
///   that you can access it in the future.
/// \param[in] mesh A pointer to the Mesh that should be added.  This Mesh
///   must have been dynamically allocated.  The Scene will now own this Mesh
///   and be responsible for de-allocating it.
/// \pre The Scene does not contain any Mesh associated with meshName.
/// \post The Scene contains the mesh, associated with the meshName.
void
Scene::add (const std::string& meshName, Mesh* mesh)
{

  s_meshes.insert(std::pair<const std::string&, Mesh*>(meshName, mesh));
  i = s_meshes.begin();
}

/// \brief Removes a Mesh from this Scene.
/// \param[in] meshName The name of the Mesh that should be removed.
/// \pre This Scene contains a Mesh associated with meshName.
/// \post This Scene no longer associates meshName with anything.
/// \post The Mesh that had been associated with meshName has been freed.
void
Scene::remove (const std::string& meshName)
{
  for (auto it = s_meshes.begin(); it != s_meshes.end(); ++it)
  {
    if (it->first == meshName)
    {
      this->activateNextMesh();
      it->second->~Mesh();
      s_meshes.erase(meshName);
      return;
    }
  }
            
}
        


  /// \brief Removes all Meshes from this Scene.
  /// \post This Scene is empty.
  /// \post All Meshes that had been part of this Scene have been freed.
  void
  Scene::clear ()
  {
      for (auto it = s_meshes.begin(); it != s_meshes.end(); ++it)
      {
        it->second->~Mesh();
      }
      s_meshes.clear();
        
  }

  /// \brief Draws all of the elements in this Scene.
  /// \param[in] shaderProgram The ShaderProgram that should be used for
  ///   drawing.
  /// \param[in] viewMatrix The view matrix that should be used when drawing
  ///   the Scene.
  void
  Scene::draw (const Transform viewMatrix, Matrix4 projectionMatrix)
  {
      
      for (auto it = s_meshes.begin(); it != s_meshes.end(); ++it)
      {
        it->second->draw(viewMatrix, projectionMatrix);
      }
        
  }

  /// \brief Tests whether or not this Scene contains a Mesh associated with a
  ///   name.
  /// \param[in] meshName The name of the requested Mesh.
  /// \return Whether or not this Scene contains a Mesh associated with
  ///   meshName.
  bool
  Scene::hasMesh (const std::string& meshName)
  {
    for (auto it = s_meshes.begin(); it != s_meshes.end(); ++it)
    {
        if(it->first == meshName && it->second != NULL)
        {
            return true;
        }        
    }
            
    return false;
  }

  /// \brief Gets the Mesh associated with a name.
  /// \param[in] meshName The name of the requested Mesh.
  /// \return A pointer to the Mesh associated with meshName.  This pointer
  ///   should not be permanently stored, as the Mesh it points to will be
  ///   deallocated with this Scene.
  /// \pre This Scene has a Mesh assocated with meshName.
  Mesh*
  Scene::getMesh (const std::string& meshName)
  {
    for (auto it = s_meshes.begin(); it != s_meshes.end(); ++it)
    {
        if(it->first == meshName)
        {
            return it->second;
        }
            
      }
    return NULL;
  } 

  /// \brief Sets the active mesh to the mesh named "meshName".
  /// The active mesh is the one affected by transforms.
  /// \param[in] meshName The name of the mesh that should be active.
  /// \pre The scene contains a mesh with that name.
  /// \post The mesh with that name becomes the active mesh.
  void
  Scene::setActiveMesh (const std::string& meshName)
  {
    i = s_meshes.begin();
    while(i != s_meshes.end())
    {
      if(i->first == meshName)
      {
        return;
      }
      i++;
    }
  }

  /// \brief Gets the active mesh.
  /// \pre The scene has at least one mesh.
  /// \return The active mesh.
  Mesh*
  Scene::getActiveMesh ()
  {
    return i->second;
  }

  /// \brief Switches active meshes in the forward direction.
  /// \pre The scene has at least one mesh.
  /// \post The next mesh becomes active.  If the last mesh was active, the
  ///   first mesh becomes active.
  void
  Scene::activateNextMesh ()
  {
    i++;
    if(i == s_meshes.end())
    {
      i = s_meshes.begin();
      return;
    }
  }

  /// \brief Switches active meshes in the backward direction.
  /// \pre The scene has at least one mesh.
  /// \post The previous mesh becomes active.  If the first mesh was active,
  ///   the last mesh becomes active.
  void
  Scene::activatePreviousMesh ()
  {
    if(i == s_meshes.begin())
    {
      i = s_meshes.end();
      i--;
      return;
    }
    i--;
  }
 
  void
  Scene::setLights(int lights)
  {
    l_shader->enable();

    l_shader->setUniformType("uNumLights", lights);
    
    l_shader->setUniformVec3("uEyePosition", Vector3(0, 0, 0));

    l_shader->disable();
  }