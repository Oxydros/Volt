>>Vertex

#version 400 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec4 inColor;

uniform mat4 modelViewProjection;

void main()
{
    gl_Position = modelViewProjection * vec4(inPos, 1.0);
}

>>Pixel

#version 330 core
out vec3 pixelColor;

uniform vec3 lightColor;

void main()
{
    pixelColor = lightColor;
}