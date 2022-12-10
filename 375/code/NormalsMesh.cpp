/// \file NormalsMesh.cpp
/// \brief Implementation of NormalsMesh class and any associated global functions.
/// \author John Shenk
/// \version A08

#include "NormalsMesh.hpp"
#include "Mesh.hpp"
#include <assimp/Importer.hpp>      
#include <assimp/scene.h>          
#include <assimp/postprocess.h> 

NormalsMesh::NormalsMesh(OpenGLContext* context, ShaderProgram* shader):Mesh(context,shader){}

NormalsMesh::NormalsMesh(OpenGLContext* context, ShaderProgram* shader, 
    Vector3 ambientReflection, Vector3 diffuseReflection, Vector3 specularReflection, Vector3 emissiveIntensity, float specularPower)
    :Mesh(context, shader, ambientReflection, diffuseReflection, specularReflection, emissiveIntensity, specularPower){}

NormalsMesh::NormalsMesh (OpenGLContext* context, ShaderProgram* shader, std::string filename, unsigned int meshNum,Vector3 ambientReflection, Vector3 diffuseReflection, Vector3 specularReflection, Vector3 emissiveIntensity, float specularPower)
    :Mesh(context, shader, ambientReflection, diffuseReflection, specularReflection, emissiveIntensity, specularPower)
{
  Assimp::Importer importer;
  unsigned int flags =
    aiProcess_Triangulate              // convert all shapes to triangles
    | aiProcess_GenSmoothNormals       // create vertex normals if not there
    | aiProcess_JoinIdenticalVertices; // combine vertices for indexing
  const aiScene* scene = importer.ReadFile (filename,
					    flags);
  if (scene == nullptr)
  {
    auto error = importer.GetErrorString ();
    std::cerr << "Failed to load model " << filename << " with error " << error << std::endl;
  }
  else
  {
    if(meshNum >= scene->mNumMeshes)
    {
      std::cerr << "Could not read mesh " << meshNum << " from " << filename << " because it only has " << scene->mNumMeshes << " meshes." << std::endl;
    }
    else
    {
      const aiMesh* mesh = scene->mMeshes[meshNum];
      std::vector<float> vertexData;
      std::vector<unsigned int> indexes;
      for (unsigned vertexNum = 0; vertexNum < mesh->mNumVertices; ++vertexNum)
      {
	      vertexData.push_back (mesh->mVertices[vertexNum].x);
	      vertexData.push_back (mesh->mVertices[vertexNum].y);
	      vertexData.push_back (mesh->mVertices[vertexNum].z);
	      vertexData.push_back (mesh->mNormals[vertexNum].x);
	      vertexData.push_back (mesh->mNormals[vertexNum].y);
	      vertexData.push_back (mesh->mNormals[vertexNum].z);
      }
      for (unsigned int faceNum = 0; faceNum < mesh->mNumFaces; ++faceNum)
      {
	      const aiFace& face = mesh->mFaces[faceNum];
	      for (unsigned int indexNum = 0; indexNum < 3; ++indexNum)
	      {
	        unsigned int vertexNum = face.mIndices[indexNum];
	        indexes.push_back (vertexNum);
	      }
      }
      addGeometry (vertexData);
      addIndices (indexes);
    
    }  
  }
}

NormalsMesh::NormalsMesh (OpenGLContext* context, ShaderProgram* shader, std::string filename, unsigned int meshNum) : Mesh(context, shader)
{
  Assimp::Importer importer;
  unsigned int flags =
    aiProcess_Triangulate              // convert all shapes to triangles
    | aiProcess_GenSmoothNormals       // create vertex normals if not there
    | aiProcess_JoinIdenticalVertices; // combine vertices for indexing
  const aiScene* scene = importer.ReadFile (filename,
					    flags);
  if (scene == nullptr)
  {
    auto error = importer.GetErrorString ();
    std::cerr << "Failed to load model " << filename << " with error " << error << std::endl;
  }
  else
  {
    if(meshNum >= scene->mNumMeshes)
    {
      std::cerr << "Could not read mesh " << meshNum << " from " << filename << " because it only has " << scene->mNumMeshes << " meshes." << std::endl;
    }
    else
    {
      const aiMesh* mesh = scene->mMeshes[meshNum];
      std::vector<float> vertexData;
      std::vector<unsigned int> indexes;
      for (unsigned vertexNum = 0; vertexNum < mesh->mNumVertices; ++vertexNum)
      {
	      vertexData.push_back (mesh->mVertices[vertexNum].x);
	      vertexData.push_back (mesh->mVertices[vertexNum].y);
	      vertexData.push_back (mesh->mVertices[vertexNum].z);
	      vertexData.push_back (mesh->mNormals[vertexNum].x);
	      vertexData.push_back (mesh->mNormals[vertexNum].y);
	      vertexData.push_back (mesh->mNormals[vertexNum].z);
      }
      for (unsigned int faceNum = 0; faceNum < mesh->mNumFaces; ++faceNum)
      {
	      const aiFace& face = mesh->mFaces[faceNum];
	      for (unsigned int indexNum = 0; indexNum < 3; ++indexNum)
	      {
	        unsigned int vertexNum = face.mIndices[indexNum];
	        indexes.push_back (vertexNum);
	      }
      }
      addGeometry (vertexData);
      addIndices (indexes);
    
      if(scene->HasMaterials())
      {
        for (unsigned int materialNum = 0; materialNum < scene->mNumMaterials; ++materialNum)
        {
          aiMaterial* material = scene->mMaterials[materialNum];
          aiColor3D color;
          float shine;
          if(material->Get(AI_MATKEY_COLOR_AMBIENT, color) == AI_SUCCESS)
          {
            shader->enable();
            shader->setUniformVec3("uAmbientReflection", Vector3(color.r, color.g, color.b));
            shader->disable();
          }
          if(material->Get(AI_MATKEY_COLOR_DIFFUSE, color) == AI_SUCCESS)
          {
            shader->enable();
            shader->setUniformVec3("uDiffuseReflection", Vector3(color.r, color.g, color.b));
            shader->disable();
          }
          if(material->Get(AI_MATKEY_COLOR_SPECULAR, color) == AI_SUCCESS)
          {
            shader->enable();
            shader->setUniformVec3("uSpecularReflection", Vector3(color.r, color.g, color.b));
            shader->disable();
          }
          if(material->Get(AI_MATKEY_COLOR_EMISSIVE, color) == AI_SUCCESS)
          {
            shader->enable();
            shader->setUniformVec3("uEmissiveIntensity", Vector3(color.r, color.g, color.b));
            shader->disable();
          }
          if(material->Get(AI_MATKEY_SHININESS, shine) == AI_SUCCESS)
          {
            shader->enable();
            shader->setUniformVec3("uSpecularPower", shine);
            shader->disable();
          }
        }
      }
      
    }  
  }
}



NormalsMesh::~NormalsMesh(){}

unsigned int
NormalsMesh::getFloatsPerVertex()
{
    return (unsigned int)6;
}

void 
NormalsMesh::enableAttributes()
{
    const GLint NORMAL_ATTRIB_INDEX = 2;
    m_context->enableVertexAttribArray (NORMAL_ATTRIB_INDEX);
    // Colors have 3 parts, each are floats, and start at 10th position in array
    m_context->vertexAttribPointer (NORMAL_ATTRIB_INDEX, 3, GL_FLOAT, GL_FALSE, (6 * sizeof(float)),
			  reinterpret_cast<void*> (3 * sizeof(float)));
    Mesh::enableAttributes();
}