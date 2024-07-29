#version 330 core
in vec3 normal;
in vec3 fragPos;
in vec3 LightPos;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};
struct Light {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Material material;
uniform Light light;

out vec4 FragColor;
void main(){
    vec3 ambient = material.ambient * light.ambient;

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(LightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = (material.diffuse * diff) * light.diffuse;

    vec3 viewDir = normalize(-fragPos);
    vec3 lightRef = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, lightRef), 0.0), 128);
    vec3 specular = (material.specular * spec) * light.specular;

    vec3 sum = ambient + diffuse + specular;
    FragColor = vec4(sum, 1.0); 
}
