#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUV;
layout (location = 2) in vec3 aNormal;

uniform mat4 iModel;
uniform mat4 iView;
uniform mat4 iProj;

void main()
{
    gl_Position = iProj * iView * iModel * vec4(aPos, 1.0);
}