#version 330
out vec4 color;
vec4 debugColor =  vec4(0.0, 0.0, 1.0, 1.0);
bool err = false;
in vec4 vCol;
in vec2 texCoord;
// use flat for non interpolation
in vec3 normal;
// texture unit 0 is the default
uniform sampler2D theTexture;
uniform sampler2D directionalShadowMap;

in vec3 fragPos;
in vec4 directionalLightSpacePos;

const int MAX_POINT_LIGHTS = 3;
const int MAX_SPOT_LIGHTS = 3;

struct Light{
vec3 color;
float ambientIntensity;
float diffuseIntensity;

};

struct DirectionalLight{
Light base;
vec3 direction;


};

struct PointLight{
    Light base;
    vec3 position;
    float constant;
    float exponent;
    float linear;
};

struct SpotLight{
    PointLight base;
    vec3 direction;
    float edge;
};

uniform int pointLightCount;
uniform int spotLightCount;

uniform DirectionalLight directionalLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];




struct Material{
    float specularIntensity;
    float shininess;
};


uniform Material material;



// camera world position
uniform vec3 eyePosition;

float caclDirectionalShadowFactor(DirectionalLight light)
{
    // w divide
    vec3 projCoords = vec3(directionalLightSpacePos.xyz / directionalLightSpacePos.w);
    // converts to [0 - 1]

  
    
    projCoords = (projCoords * 0.5) + 0.5;

    // bias depends on the angle
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(light.direction);

    float bias = max(0.05 * (1 - dot(norm, lightDir)), 0.005);
   





    // current processed fragment
    float current = projCoords.z;

    
      /* err = true;
        debugColor = vec4(closest, closest, closest, 1.0);*/
    float shadow = 0.0;

    // how big is one unit of the texture
    vec2 texelSize = 1.0 / textureSize(directionalShadowMap, 0);

    for(int x = -1; x <= 1; x++)
    {
        for(int y = -1; y <= 1; y++)
        {
            float pcfDepth = texture(directionalShadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
            shadow += current - bias > pcfDepth ? 1.0 : 0.0;
        }
    }
  
    shadow /= 9.0;
    

    if(projCoords.z > 1.0)
    {
        shadow = 0.0;
    }

    return shadow;

}

vec4 calcLightByDirection(Light light, vec3 direction, float shadowFactor)
{
    vec4 ambientColor = vec4(light.color, 1.0f) * light.ambientIntensity;
    // percentage of color which is why we multiply

    float diffuseFactor = max(dot(normalize(normal), normalize(direction)), 0.0f);
    vec4 diffuseColor = vec4(light.color, 1.0f) * light.diffuseIntensity * diffuseFactor;

    vec4 specularColor = vec4(0.0f);

    // only apply specular lighting on top of specular ligthing
    if(diffuseFactor > 0.0f)
    {
         vec3 fragToEye =  normalize(eyePosition - fragPos);
         vec3 reflectedVertex = normalize(reflect(direction, normalize(normal)));
         float specularFactor = dot(fragToEye, reflectedVertex);

        if(specularFactor > 0.0f)
         {
             specularFactor = pow(specularFactor, material.shininess);
             specularColor = vec4(light.color * material.specularIntensity * specularFactor, 1.0f);
         }

         


    }

    // ambient lighting is always present
    // full shadow is 1.0
    return (ambientColor + (1.0 - shadowFactor) * (diffuseColor + specularColor));
}

vec4 calcDirectionalLight()
{
    float shadowFactor = caclDirectionalShadowFactor(directionalLight);
    return calcLightByDirection(directionalLight.base, directionalLight.direction, shadowFactor);
}

vec4 calcPointLight(PointLight pLight)
{
    vec3 direction = fragPos - pLight.position;
    float distance = length(direction);
    direction = normalize(direction);

    vec4 color = calcLightByDirection(pLight.base, direction, 0.0);
    float attenuation = pLight.exponent * distance * distance + pLight.linear * distance + pLight.constant;
    return (color/attenuation);
}

vec4 calcPointLights()
{
    vec4 totalColor = vec4(0,0,0,0);

    for(int i = 0; i < pointLightCount; i++)
    {
       totalColor += calcPointLight(pointLights[i]);
    }

    return totalColor;

}

vec4 calcSpotLight(SpotLight sLight)
{
    vec3 rayDirection = normalize(fragPos - sLight.base.position);

    float slFactor = dot(rayDirection, sLight.direction);

    if(slFactor > sLight.edge)
    {
        vec4 color = calcPointLight(sLight.base);
        //           res     number to convert     convert to new scale
        return color * ( 1.0f - (1.0f - slFactor) * (1.0f/ (1.0f - sLight.edge)));
    }
    else 
    {
        return vec4 (0,0,0,0);
    }
    

}

vec4 calcSpotLights()
{
        vec4 totalColor = vec4(0,0,0,0);

    for(int i = 0; i < spotLightCount; i++)
    {
       totalColor += calcSpotLight(spotLights[i]);
    }

    return totalColor;

}





void main()
{
    vec4 finalColor = calcDirectionalLight();
    finalColor += calcPointLights();
    finalColor += calcSpotLights();


    color= texture(theTexture, texCoord) * finalColor;

    if(err)
    {
        color = debugColor;
    }
    
}
