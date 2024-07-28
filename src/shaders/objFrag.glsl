#version 330 core
in vec3 normal;
in vec3 fragPos;

uniform vec3 lightPos;

out vec4 FragColor;
void main(){
    vec3 objColor = vec3(0.8, 0.5, 0.1);
    vec3 lightColor = vec3(1.0);
    vec3 ambient = 0.1 * lightColor;
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(fragPos - lightPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    vec3 sum = (ambient + diffuse) * objColor;
    FragColor = vec4(sum, 1.0); 
}
