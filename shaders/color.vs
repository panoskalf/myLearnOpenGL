#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightPos;

out vec3 FragPosViewSpace;
out vec3 NormalViewSpace;
out vec3 FragPosModelSpace;
out vec3 NormalModelSpace;
out vec3 LightPosViewSpace;

void main()
{
    vec4 fragPosViewSpace = view * model * vec4(aPos, 1.0);
    FragPosViewSpace = vec3(fragPosViewSpace);
    NormalViewSpace = mat3(transpose(inverse(view * model))) * aNormal;

    FragPosModelSpace = vec3(model * vec4(aPos, 1.0));
    NormalModelSpace = mat3(transpose(inverse(model))) * aNormal;

    // Calculate the position of the vertex in clip space
    gl_Position = projection * view * model * vec4(aPos, 1.0);

    LightPosViewSpace = vec3(view * vec4(lightPos, 1.0));
}