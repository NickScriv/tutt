
#version 330
out vec4 color;
in vec4 vCol;
in vec2 texCoord;
// texture unit 0 is the default
uniform sampler2D theTexture;

struct DirectionalLight{
vec3 color;
float ambientIntensity;

};

uniform DirectionalLight directionalLight;

void main()
{
    vec4 ambientColor = vec4(directionalLight.color, 1.0f) * directionalLight.ambientIntensity;
    // percentage of color which is why we multiply
    color= texture(theTexture, texCoord) * ambientColor;
    
}
