
#version 330
out vec4 color;
in vec4 vCol;
in vec2 texCoord;
// use flat for non interpolation
in vec3 normal;
// texture unit 0 is the default
uniform sampler2D theTexture;

in vec3 fragPos;

const int MAX_POINT_LIGHTS = 3;

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

uniform int pointLightCount;

uniform DirectionalLight directionalLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];




struct Material{
    float specularIntensity;
    float shininess;
};


uniform Material material;

// camera world position
uniform vec3 eyePosition;

vec4 calcLightByDirection(Light light, vec3 direction)
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


    return (ambientColor + diffuseColor + specularColor);
}

vec4 calcDirectionalLight()
{
    return calcLightByDirection(directionalLight.base, directionalLight.direction);
}

vec4 calcPointLights()
{
    vec4 totalColor = vec4(0,0,0,0);

    for(int i = 0; i < pointLightCount; i++)
    {
        vec3 direction = fragPos - pointLights[i].position;
        float distance = length(direction);
        direction = normalize(direction);

        vec4 color = calcLightByDirection(pointLights[i].base, direction);
        float attenuation = pointLights[i].exponent * distance * distance + pointLights[i].linear * distance + pointLights[i].constant;
        totalColor += (color/attenuation);
    }

    return totalColor;

}



void main()
{
    vec4 finalColor = calcDirectionalLight();
    finalColor += calcPointLights();

    color= texture(theTexture, texCoord) * finalColor;
    
}
