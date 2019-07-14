>>Vertex

#version 400 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec4 inColor;
layout (location = 2) in vec2 inTextCoord;
layout (location = 3) in vec3 inNormal;

uniform mat4 modelViewProjection;
uniform mat4 model;
uniform mat4 normalMatrix;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos;

uniform float ambientStrength;
uniform float specularStrength;
uniform int shininess;

out vec4 vertexColor;
out vec2 textCoord;

void main()
{
    gl_Position = modelViewProjection * vec4(inPos, 1.0);

    vec3 fragPos = vec3(model * vec4(inPos, 1.0));
    vec3 normal = mat3(normalMatrix) * inNormal;
    vec3 lightDir = normalize(lightPos - fragPos);
    float diffuse = max(dot(normal, lightDir), 0.0);

    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float specCoef = max(dot(viewDir, reflectDir), 0.0);
    float spec = pow(specCoef, shininess);

    vec3 ambientLight = ambientStrength * lightColor;
    vec3 diffuseLight = diffuse * lightColor;
    vec3 specular = specularStrength * spec * lightColor;      

    vertexColor = vec4(ambientLight + diffuseLight + specular, 1.0) * inColor;
    textCoord = inTextCoord;
}

>>Pixel

#version 330 core
out vec4 pixelColor;

in vec4 vertexColor;
in vec2 textCoord;

uniform float mix_ratio;
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    pixelColor = mix(texture(texture1, textCoord), texture(texture2, textCoord), mix_ratio) + vertexColor;
}