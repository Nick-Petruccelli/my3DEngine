#version 330 core
in vec2 texCord;

uniform sampler2D ourTexture;

out vec4 FragColor;
void main(){
    FragColor = vec4(1.0, 0.8, 0.8, 1.0) * texture(ourTexture, texCord);
}
