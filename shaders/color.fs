#version 330 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float     emissionIntensity;
    float     shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 color;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;
uniform float time;

void main()
{


    // ambient
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

    // emission
    vec3 emission = vec3(0.0);
    // check for black box inside specular texture
    if (texture(material.specular, TexCoords).r == 0.0)
    {
        // apply emission
        // emission = texture(material.emission, TexCoords).rgb;
        // move in y direction
        emission = material.emissionIntensity * texture(material.emission, TexCoords + vec2(0.0,time)).rgb;
    }

    // combined output
    color = vec4(ambient + diffuse + specular + emission, 1.0f);
}