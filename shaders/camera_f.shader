#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    vec4 color = texture(texture1, TexCoord);
    color.a = color.r;
    FragColor = color;
//    FragColor = texture(texture1, TexCoord);
//    FragColor = vec4(0,TexCoord.x, TexCoord.y, 1);
//    FragColor = mix(texture(texture1, TexCoord),vec4(0,TexCoord.x, TexCoord.y, 1), 0.2);
}