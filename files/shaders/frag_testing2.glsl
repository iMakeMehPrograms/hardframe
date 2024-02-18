#version 330 core
in vec2 pUV;

uniform sampler2D iAlbedo;

out vec4 FragColor;

void main()
{
    FragColor = texture(iAlbedo, pUV+0.5);
} 