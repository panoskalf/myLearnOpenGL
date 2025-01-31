#version 330 core
out vec4 FragColor;

in vec3 FragPosModelSpace;
in vec3 NormalModelSpace;
in vec3 LightPosViewSpace;

in vec3 ambientLight1;
in vec3 diffuseLight1;
in vec3 specularLight1;

uniform vec3 objectColor;
uniform vec3 lightColor2;
uniform vec3 lightPos2;
uniform vec3 viewPos;
uniform float ambientStrength;
uniform float specularStrength;
uniform float diffuseStrength;

void main()
{
    // Use the passed ambient, diffuse, and specular components for light1
    vec3 ambient = ambientLight1;
    vec3 diffuse = diffuseLight1;
    vec3 specular = specularLight1;

    // Calculate lighting for light2 (Phong shading)
    vec3 normModel = normalize(NormalModelSpace);
    vec3 lightDirModel = normalize(lightPos2 - FragPosModelSpace);
    vec3 viewDirModel = normalize(viewPos - FragPosModelSpace);
    vec3 reflectDirModel = reflect(-lightDirModel, normModel);

    // Ambient for light2
    vec3 ambient2 = ambientStrength * lightColor2;

    // Diffuse for light2
    float diffModel = max(dot(normModel, lightDirModel), 0.0);
    vec3 diffuse2 = diffuseStrength * diffModel * lightColor2;

    // Specular for light2
    float specModel = pow(max(dot(viewDirModel, reflectDirModel), 0.0), 32.0);
    vec3 specular2 = specularStrength * specModel * lightColor2;

    // Combine results
    vec3 result = (ambient + diffuse + specular + ambient2 + diffuse2 + specular2) * objectColor;
    FragColor = vec4(result, 1.0);
}