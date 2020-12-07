
#version 330
layout(location=0)in vec3 pos;
uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;
out vec4 vCol;
void main()
{vCol=vec4(clamp(pos,0.f,1.f),1.f);
    gl_Position=projection*view*model*vec4(pos,1.);
    
}
