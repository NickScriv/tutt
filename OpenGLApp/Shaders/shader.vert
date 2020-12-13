#version 330
layout(location=0)in vec3 pos;
layout(location=1)in vec2 tex;
layout(location=2)in vec3 norm;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;
out vec4 vCol;
out vec2 texCoord;
out vec3 normal;
out vec3 fragPos;
out vec4 directionalLightSpacePos;

uniform mat4 directionalLightView; // convert to light space
void main()
{
    vCol=vec4(clamp(pos,0.f,1.f),1.f);
    gl_Position=projection*view*model*vec4(pos,1.);
    directionalLightSpacePos = directionalLightView * model * vec4(pos, 1.0);
    texCoord = tex;
    // multplying by the model to account for changes in rotation and scaling
    // transpose and inverse used for non unifrom scaling
    normal = mat3(transpose(inverse(model))) * norm;
    // needs to be in world coordinates
    fragPos = (model*vec4(pos,1.)).xyz;
    
}
