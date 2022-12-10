#include "LightSource.hpp"

LightSource::LightSource(const Vector3& diffuseIntensity, const Vector3& specularIntensity)
{
    m_diffuseIntensity = diffuseIntensity;
    m_specularIntensity = specularIntensity;
}

LightSource::~LightSource(){}

void
LightSource::setUniforms(ShaderProgram* program, int lightNum)
{
    program->enable();
    program->setUniformVec3("uLights[" + std::to_string(lightNum) + "].diffuseIntensity", m_diffuseIntensity);
    program->setUniformVec3("uLights[" + std::to_string(lightNum) + "].specularIntensity", m_specularIntensity);
    program->disable();
}

Vector3
LightSource::getDiffuse()
{
    return m_diffuseIntensity;
}

Vector3
LightSource::getSpecular()
{
    return m_specularIntensity;
}

DirectionalLightSource::DirectionalLightSource(const Vector3& diffuseIntensity, const Vector3& specularIntensity, const Vector3& direction) 
    : LightSource (diffuseIntensity, specularIntensity)
{
    m_direction = direction;
}

DirectionalLightSource::~DirectionalLightSource(){}

void
DirectionalLightSource::setUniforms(ShaderProgram* program, int lightNum)
{
    program->enable();
    program->setUniformType("uLights[" + std::to_string(lightNum) + "].type", 0);
    program->setUniformVec3("uLights[" + std::to_string(lightNum) + "].direction", m_direction);
    program->disable();
    LightSource::setUniforms(program, lightNum);
}

LocationLightSource::LocationLightSource(const Vector3& diffuseIntensity, const Vector3& specularIntensity, const Vector3& position, const Vector3& attenuationCoefficients) 
    : LightSource (diffuseIntensity, specularIntensity)
{
    m_position = position;
    m_attenuationCoefficients = attenuationCoefficients;
}

LocationLightSource::~LocationLightSource(){}

void
LocationLightSource::setUniforms (ShaderProgram* program, int lightNum)
{
    
    program->enable();
    program->setUniformVec3("uLights[" + std::to_string(lightNum) + "].position", m_position);
    program->setUniformVec3("uLights[" + std::to_string(lightNum) + "].attenuationCoefficients", m_attenuationCoefficients);
    program->disable();
    LightSource::setUniforms(program, lightNum);
}

PointLightSource::PointLightSource(const Vector3& diffuseIntensity, const Vector3& specularIntensity, const Vector3& position, const Vector3& attenuationCoefficients) 
    : LocationLightSource(diffuseIntensity, specularIntensity, position, attenuationCoefficients){}

PointLightSource::~PointLightSource(){}

void
PointLightSource::setUniforms(ShaderProgram* program, int lightNum)
{
    program->enable();
    program->setUniformType("uLights[" + std::to_string(lightNum) + "].type", 1);
    program->disable();
    LocationLightSource::setUniforms(program, lightNum);
}

SpotLightSource::SpotLightSource(const Vector3& diffuseIntensity, const Vector3& specularIntensity, const Vector3& position, const Vector3& attenuationCoefficients, const Vector3& direction, float cutoffCosAngle, float falloff)
    : LocationLightSource(diffuseIntensity, specularIntensity, position, attenuationCoefficients)
{
    m_direction = direction;
    m_cutoffCosAngle = cutoffCosAngle;
    m_falloff = falloff;
}

SpotLightSource::~SpotLightSource(){}

void 
SpotLightSource::setUniforms(ShaderProgram* program, int lightNum)
{
    
    program->enable();
    program->setUniformType("uLights[" + std::to_string(lightNum) + "].type", 2);
    program->setUniformVec3("uLights[" + std::to_string(lightNum) + "].direction", m_direction);
    program->setUniformFloat("uLights[" + std::to_string(lightNum) + "].cutoffCosAngle", m_cutoffCosAngle);
    program->setUniformFloat("uLights[" + std::to_string(lightNum) + "].falloff", m_falloff);
    program->disable();
    LocationLightSource::setUniforms(program, lightNum);
}
