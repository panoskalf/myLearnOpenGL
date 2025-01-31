#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform float ambientStrength;
uniform float specularStrength;
uniform float diffuseStrength;

out vec3 FragPosModelSpace;
out vec3 NormalModelSpace;
out vec3 LightPosViewSpace;

out vec3 ambientLight1;
out vec3 diffuseLight1;
out vec3 specularLight1;

void main()
{
    vec4 fragPosViewSpace = view * model * vec4(aPos, 1.0);
    vec3 FragPosViewSpace = vec3(fragPosViewSpace);
    vec3 NormalViewSpace = mat3(transpose(inverse(view * model))) * aNormal;

    FragPosModelSpace = vec3(model * vec4(aPos, 1.0));
    NormalModelSpace = mat3(transpose(inverse(model))) * aNormal;

    // Calculate the position of the vertex in clip space
    gl_Position = projection * view * model * vec4(aPos, 1.0);

    LightPosViewSpace = vec3(view * vec4(lightPos, 1.0));

    // Calculate ambient, diffuse, and specular for light1 (Gouraud shading)
    vec3 normView = normalize(NormalViewSpace);
    vec3 lightDirView = normalize(LightPosViewSpace - FragPosViewSpace);
    vec3 viewDirView = normalize(-FragPosViewSpace); // the viewer is always at (0,0,0) in view-space
    vec3 reflectDirView = reflect(-lightDirView, normView);

    // Ambient
    ambientLight1 = ambientStrength * lightColor;

    // Diffuse
    float diffView = max(dot(normView, lightDirView), 0.0);
    diffuseLight1 = diffuseStrength * diffView * lightColor;

    // Specular
    float specView = pow(max(dot(viewDirView, reflectDirView), 0.0), 32.0);
    specularLight1 = specularStrength * specView * lightColor;
}