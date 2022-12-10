/// \file ColorsMesh.hpp
/// \brief Declaration of ColorsMesh class and any associated global functions.
/// \author John Shenk
/// \version A08

#ifndef NORMALS_MESH_HPP
#define NORMALSMESH_HPP
#include "Mesh.hpp"
class NormalsMesh : public Mesh
{

    public: 
        /// \brief Construct normals mesh
        /// \param context The OpenGLContext we want to use
        /// \param shader The ShaderProgram we want to use
        /// \post The parameters have all been set to their variables
        NormalsMesh(OpenGLContext* context, ShaderProgram* shader);

        // \brief Constructs a new mesh with materail properties
        // \param[in] program The shader program we want to use
        // \param[in] ambientRelfection The amount of ambient reflection we want
        // \param[in] diffuseReflection The amount of diffuse  relfection we want
        // \param[in] specularReflection The amount of specular reflection we want
        // \param[in] emissiveIntensity The amount on emissive intensity we want
        // \param[in] specularPower The amount of "shininess" we want on our material
        // \post The parameters have been set to their respective uniforms in the fragment and vertex shaders
        NormalsMesh(OpenGLContext* context, ShaderProgram* shader, 
        Vector3 ambientReflection, Vector3 diffuseReflection, Vector3 specularReflection, Vector3 emissiveIntensity, float specularPower);

        /// \brief Constructs a NormalsMesh with triangles pulled from a file.
        /// \param[in] context A pointer to an objec tthrough which the Mesh will be
        ///   able to make OpenGL calls.
        /// \param[in] shader A pointer to the shader program that should be used for
        ///   drawing this mesh.
        /// \param[in] fileName The name of the file this mesh's geometry should be
        ///   read from.
        /// \param[in] meshNum The 0-based index of which mesh from that file should
        ///   be used.
        /// \post A unique VAO, VBO, and IBO have been generated for this Mesh and
        ///   stored for later use.
        /// \post If that file exists and contains a mesh of that number, the indexes
        ///   and geometry from it have been pre-populated into this Mesh.  Otherwise
        ///   this Mesh is empty and an error message has been printed.
        NormalsMesh (OpenGLContext* context, ShaderProgram* shader, std::string fileName, unsigned int meshNum, Vector3 ambientReflection, Vector3 diffuseReflection, Vector3 specularReflection, Vector3 emissiveIntensity, float specularPower);

        NormalsMesh (OpenGLContext* context, ShaderProgram* shader, std::string filename, unsigned int meshNum);
        
        // Empty Destructor
        ~NormalsMesh();

        // \brief Override of getFloatsPerVertex for NormalsMesh
        // \return the number of floats per vertex
        virtual
        unsigned int
        getFloatsPerVertex();

    protected:
        /// \brief Override of enableAttributes for NormalsMesh
        /// \post Attributes have been enabled
        virtual
        void
        enableAttributes();

};
#endif