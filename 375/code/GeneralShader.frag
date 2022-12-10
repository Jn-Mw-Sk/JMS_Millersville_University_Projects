#version 330
/*
  Filename: Vec3.frag
  Authors: John Shenk
  Course: CSCI375
  Assignment: A09: Project
  Description: A fragment shader for use with GeneralShader.vert
*/

in vec3 positionWorld;
in vec3 normalWorld;

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

const int MAX_LIGHTS = 8;
uniform Light uLights[MAX_LIGHTS];

//viewMatrix
uniform mat4 uView;

//Material Properties
uniform vec3 uDiffuseReflection;
uniform vec3 uSpecularReflection;
uniform float uSpecularPower;
uniform vec3 uEyePosition;
uniform vec3 uAmbientReflection;
uniform vec3 uEmissiveIntensity;
uniform vec3 uAmbientIntensity;

//Input to shader
vec3 vColor;

//Output to shader
out vec4 fColor;

// Calculate diffuse and specular lighting for a single light.
vec3
calculateLighting (Light light, vec3 vertexPosition, vec3 vertexNormal);

void
main()
{
  vColor = uAmbientReflection;

  // Handle ambient and emissive light
  //   It's independent of any particular light
  vColor = uAmbientReflection * uAmbientIntensity
    + uEmissiveIntensity;

  // Stay in bounds [0, 1]
  vColor = clamp (vColor, 0.0, 1.0);
    // Iterate over all lights and calculate diffuse and specular contributions
    for (int i = 0; i < uNumLights; ++i)
    {
        vColor
            += calculateLighting (uLights[i], positionWorld, normalWorld);
    }

    fColor = vec4 (vColor, 1.0);
  
}

vec3
calculateLighting (Light light, vec3 vertexPosition, vec3 vertexNormal)
{
  // Light vector points toward the light
  vec3 lightVector;
  if (light.type == 0)
  { // Directional
    mat3 normalTransform2 = mat3 (uView);
    normalTransform2 = transpose (inverse (normalTransform2));
    lightVector = normalize (-light.direction);
  }
  else
  { // Point or spot
    mat3 view = mat3(uView);
    lightVector = normalize (light.position * view - vertexPosition);
  }
  // Light intensity is proportional to angle between light vector
  //   and vertex normal
  float lambertianCoef = max (dot (lightVector, vertexNormal), 0.0);
  vec3 diffuseAndSpecular = vec3 (0.0);
  if (lambertianCoef > 0.0)
  {
    // Light is incident on vertex, not shining on its edge or back
    vec3 diffuseColor = uDiffuseReflection * light.diffuseIntensity;
    diffuseColor *= lambertianCoef;

    vec3 specularColor = uSpecularReflection * light.specularIntensity;
    // See how light reflects off of vertex
    vec3 reflectionVector = reflect (-lightVector, vertexNormal);
    // Compute view vector, which points toward the eye
    vec3 eyeVector = normalize (uEyePosition - vertexPosition);
    // Light intensity is proportional to angle between reflection vector
    //   and eye vector
    float specularCoef = max (dot (eyeVector, reflectionVector), 0.0);
    // Material's specular power determines size of bright spots
    specularColor *= pow (specularCoef, uSpecularPower);

    float attenuation = 1.0;
    if (light.type != 0)
    { // Non-directional, so light attenuates
      mat3 view = mat3(uView);
      float distance = length (vertexPosition - light.position * view);
      attenuation = 1.0 / (light.attenuationCoefficients.x
          + light.attenuationCoefficients.y * distance
          + light.attenuationCoefficients.z * distance * distance);
    }
    float spotFactor = 1.0f;
    if (light.type == 2)
    { // Spot light
      mat3 normalTransform2 = mat3 (uView);
      normalTransform2 = transpose (inverse (normalTransform2));
      float cosTheta = dot (-lightVector, light.direction * normalTransform2);
      cosTheta = max (cosTheta, 0.0f);
      spotFactor = (cosTheta >= light.cutoffCosAngle) ? cosTheta : 0.0f;
      spotFactor = pow (spotFactor, light.falloff);
    }
    diffuseAndSpecular = spotFactor * attenuation * (diffuseColor
        + specularColor);
  }

  return diffuseAndSpecular;
}

