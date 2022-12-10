/// \file ColorsMesh.hpp
/// \brief Declaration of ColorsMesh class and any associated global functions.
/// \author John Shenk
/// \version A08

#ifndef COLORS_MESH_HPP
#define COLORSMESH_HPP
#include "Mesh.hpp"
class ColorsMesh : public Mesh
{

    public: 
        /// \brief Construct colors mesh
        /// \param context The OpenGLContext we want to use
        /// \param shader The ShaderProgram we want to use
        /// \post The parameters have all been set to their variables
        ColorsMesh(OpenGLContext* context, ShaderProgram* shader);

        ColorsMesh(OpenGLContext* context, ShaderProgram* shader, 
        Vector3 ambientReflection, Vector3 diffuseReflection, Vector3 specularReflection, Vector3 emissiveIntensity, float specularPower);

        // Empty Destructor
        ~ColorsMesh();

        // \brief Override of getFloatsPerVertex for ColorsMesh
        // \return the number of floats per vertex
        virtual
        unsigned int
        getFloatsPerVertex();

   
        /// \brief Override of enableAttributes for ColorsMesh
        /// \post Attributes have been enabled
        virtual
        void
        enableAttributes();

};
#endif