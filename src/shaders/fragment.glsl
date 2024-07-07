#version 330 core
in vec3 vertColor;
in vec2 texCord;

uniform sampler2D ourTexture;

out vec4 FragColor;
void main(){
    FragColor = texture(ourTexture, texCord);
}
