
#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    vec2 flippedTexCoord = vec2(1.0 - TexCoord.x, TexCoord.y);
    vec4 color1 = texture(texture1, TexCoord);
    vec4 color2 = texture(texture2, flippedTexCoord);
    FragColor = mix(color1, color2, 0.2);
}