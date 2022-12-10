/// \file Materials.hpp
/// \brief Declaration of Materials class and any associated global functions.
/// \author John Shenk
/// \version A09

#include "Vector3.hpp"
#include "ShaderProgram.hpp"

class Material{
    public:
        // Default constructor
        Material(ShaderProgram* program);

        //Empty Material Constructor
        ~Material();
        
        // Sets uniforms
        void
        setUniforms(Vector3 ambientReflection, Vector3 diffuseReflection, Vector3 specularReflection, Vector3 emissiveIntensity, float specularPower);

        // \brief Sets the ambient reflection
        // \post  The ambient reflection has been set
        void setAmbientReflection(Vector3 ambientReflection);

        // \brief Sets the diffuse reflection
        // \post  The diffuse reflection has been set
        void setDiffuseReflection(Vector3 diffuseReflection);

        // \brief Sets the specular reflection
        // \post  The specular reflection has been set
        void setSpecularReflection(Vector3 specularReflection);

        // \brief Sets the emissive intensity
        // \post  The emissive intensity has been set
        void setEmmissiveIntensity(Vector3 emissiveIntensity);

        // \brief Sets the specular power
        // \post The specular power has been set
        void setSpecularPower(float specularPower);

        private:
            ShaderProgram* shader;
};

