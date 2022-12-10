/// \file Materials.hpp
/// \brief Implementation of Materials class and any associated global functions.
/// \author John Shenk
/// \version A09

#include "Material.hpp"
Material::Material(ShaderProgram* program)
{
    shader = program;
}



Material::~Material(){};

void
Material::setUniforms(Vector3 ambientReflection, Vector3 diffuseReflection, Vector3 specularReflection, Vector3 emissiveIntensity, float specularPower)
{
    setAmbientReflection(ambientReflection);
    setDiffuseReflection(diffuseReflection);
    setSpecularReflection(specularReflection);
    setEmmissiveIntensity(emissiveIntensity);
    setSpecularPower(specularPower);
}
// \brief Sets the ambient reflection
// \post  The ambient reflection has been set
void 
Material::setAmbientReflection(Vector3 ambientReflection)
{
    shader->enable();
    shader->setUniformVec3("uAmbientReflection", ambientReflection);
    shader->disable();
}

// \brief Sets the diffuse reflection
 // \post  The diffuse reflection has been set
void 
Material::setDiffuseReflection(Vector3 diffuseReflection)
{
    shader->enable();
    shader->setUniformVec3("uDiffuseReflection", diffuseReflection);
    shader->disable();
}
// \brief Sets the specular reflection
// \post  The specular reflection has been set
void 
Material::setSpecularReflection(Vector3 specularRefletion)
{
    shader->enable();
    shader->setUniformVec3("uSpecularReflection", specularRefletion);
    shader->disable();
}

// \brief Sets the emissive intensity
// \post  The emissive intensity has been set
void 
Material::setEmmissiveIntensity(Vector3 emissiveIntensity)
{
    shader->enable();
    shader->setUniformVec3("uEmissiveIntensity", emissiveIntensity);
    shader->disable();
}

// \brief Sets the specular power
// \post The specular power has been set
void 
Material::setSpecularPower(float specularPower)
{
    shader->enable();
    shader->setUniformFloat("uSpecularPower", specularPower);
    shader->disable();
}