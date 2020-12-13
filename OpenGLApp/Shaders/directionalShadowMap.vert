
#version 330
//  render everything relative to the light source
layout(location=0)in vec3 pos;

uniform mat4 model;
uniform mat4 directionalLightView; // convert to light space


void main()
{
    gl_Position = directionalLightView * model * vec4(pos, 1.0);
}
