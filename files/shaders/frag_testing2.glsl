#version 330 core
in vec2 pUV;

uniform sampler2D iAlbedo;

out vec4 FragColor;

void main()
{
    FragColor = vec4(pUV, 0.0f, 1.0f);
} 