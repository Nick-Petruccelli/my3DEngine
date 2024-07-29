#version 330 core
in vec3 normal;
in vec3 fragPos;
in vec3 LightPos;


out vec4 FragColor;
void main(){
    vec3 objColor = vec3(0.6, 0.2, 0.1);
    vec3 lightColor = vec3(1.0);

    vec3 ambient = 0.1 * lightColor;

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(LightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    float specularStrength = .9;
    vec3 viewDir = normalize(-fragPos);
    vec3 lightRef = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, lightRef), 0.0), 128);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 sum = (ambient + diffuse + specular) * objColor;
    FragColor = vec4(sum, 1.0); 
}
