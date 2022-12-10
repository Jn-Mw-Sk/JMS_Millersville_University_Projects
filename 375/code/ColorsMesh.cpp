/// \file ColorsMesh.hpp
/// \brief Implementation of ColorsMesh class and any associated global functions.
/// \author John Shenk
/// \version A08

#include "ColorsMesh.hpp"

ColorsMesh::ColorsMesh(OpenGLContext* context, ShaderProgram* shader):Mesh(context,shader)
{

}

ColorsMesh::ColorsMesh(OpenGLContext* context, ShaderProgram* shader, 
Vector3 ambientReflection, Vector3 diffuseReflection, Vector3 specularReflection, Vector3 emissiveIntensity, float specularPower)
:Mesh(context, shader, ambientReflection, diffuseReflection, specularReflection, emissiveIntensity, specularPower){}

ColorsMesh::~ColorsMesh(){}

unsigned int
ColorsMesh::getFloatsPerVertex()
{
    return (unsigned int)6;
}

void 
ColorsMesh::enableAttributes()
{
    const GLint COLOR_ATTRIB_INDEX = 1;
    m_context->enableVertexAttribArray (COLOR_ATTRIB_INDEX);
    m_context->vertexAttribPointer (COLOR_ATTRIB_INDEX, 3, GL_FLOAT, GL_FALSE, (6 * sizeof(float)),
			  reinterpret_cast<void*> (3 * sizeof(float)));
    Mesh::enableAttributes();
}