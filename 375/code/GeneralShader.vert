#version 330

/*
  Filename: GeneralShader.vert
  Authors: Gary M. Zoppetti, Ph.D. & Chad Hogg
  Course: CSCI375
  Assignment: A09Project
  Description: A vertex shader that demonstrates how up to 8 light sources of a
    variety of types could be provided.
*/

// By default, all float variables will use high precision.
precision highp float;

// The C++ code will tell us how many light sources there are (maximum 8).
uniform int uNumLights;

// Information about one light source.
// Because different light sources store different information, not every type
//   will use every data member.
struct Light
{
  // 0 if directional, 1 if point, 2 if spot -- other values illegal.
  int type;

  // All lights have these parameters.
  vec3 diffuseIntensity;
  vec3 specularIntensity;

  // Point and spot light parameters.
  vec3 position;
  vec3 attenuationCoefficients;

  // Directional and spot light parameter.
  vec3 direction;

  // Spot light parameters.
  float cutoffCosAngle;
  float falloff;
};

// An array of lights that will be filled by the C++ code.
const int MAX_LIGHTS = 8;
uniform Light uLights[MAX_LIGHTS];

// Single ambient light, provided by the C++ code.
uniform vec3  uAmbientIntensity;

// Material properties, provided by the C++ code.
uniform vec3  uAmbientReflection;
uniform vec3  uDiffuseReflection;
uniform vec3  uSpecularReflection;
uniform float uSpecularPower;
uniform vec3  uEmissiveIntensity;

// Inputs from the VBO.
in vec3 aPosition;
layout(location = 2) in vec3 aNormal;

// Output to the fragment shader.
out vec3 vColor;
out vec3 positionWorld;
out vec3 normalWorld;

// Transformation matrices, provided by C++ code.
uniform mat4 uView;
uniform mat4 uProjection;
uniform mat4 uWorld;

// Eye posiiton, in world space, provided by C++ code.
uniform vec3 uEyePosition;


void
main (void)
{
  mat4 worldViewProjection = uProjection * uView * uWorld;
  // Transform vertex into clip space
  gl_Position = worldViewProjection * vec4 (aPosition, 1);
  // Transform vertex into world space for lighting
  positionWorld = vec3 (uWorld * uView * vec4 (aPosition, 1));

  // We're doing lighting in world space for this example!
  mat3 normalTransform = mat3 (uWorld);
  normalTransform = transpose (inverse (normalTransform));
  mat3 normalTransform2 = mat3 (uView);
  normalTransform2 = transpose (inverse (normalTransform2));
  // Normal matrix is world inverse transpose
  normalWorld = normalize (normalTransform * normalTransform2 * aNormal);
  
}

// **

