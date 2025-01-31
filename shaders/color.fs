#version 330 core
out vec4 FragColor;

in vec3 NormalViewSpace;
in vec3 FragPosViewSpace;
in vec3 FragPosModelSpace;
in vec3 NormalModelSpace;
in vec3 LightPosViewSpace;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightColor2;
uniform vec3 lightPos2;
uniform vec3 viewPos;
uniform float ambientStrength;
uniform float specularStrength;
uniform float diffuseStrength;

void main()
{
    // ambient
    vec3 ambient = ambientStrength * lightColor * lightColor2;

    // diffuse first light (view space)
    vec3 normView = normalize(NormalViewSpace);
    vec3 lightDirView = normalize(LightPosViewSpace - FragPosViewSpace);
    float diffView = max(dot(normView, lightDirView), 0.0);
    vec3 diffuseView = diffuseStrength * diffView * lightColor;

    // diffuse second light (model space)
    vec3 normModel = normalize(NormalModelSpace);
    vec3 lightDirModel = normalize(lightPos2 - FragPosModelSpace);
    float diffModel = max(dot(normModel, lightDirModel), 0.0);
    vec3 diffuseModel = diffuseStrength * diffModel * lightColor2;

    // Combined diffuse
    vec3 diffuseCombined = diffuseView + diffuseModel;

    // specular first light (view space)
    vec3 viewDirView = normalize(-FragPosViewSpace); // the viewer is always at (0,0,0) in view-space
    vec3 reflectDirView = reflect(-lightDirView, normView);
    float specView = pow(max(dot(viewDirView, reflectDirView), 0.0), 32.0); // Ensure both arguments are float
    vec3 specularView = specularStrength * specView * lightColor;

    // specular second light (model space)
    vec3 viewDirModel = normalize(viewPos - FragPosModelSpace);
    vec3 reflectDirModel = reflect(-lightDirModel, normModel);
    float specModel = pow(max(dot(viewDirModel, reflectDirModel), 0.0), 32.0); // Ensure both arguments are float
    vec3 specularModel = specularStrength * specModel * lightColor2;

    vec3 result = (ambient + diffuseCombined + specularView + specularModel) * objectColor;
    FragColor = vec4(result, 1.0);
}