#version 330 core
in vec3 normal;
in vec3 fragPos;
in vec3 LightPos;
in vec2 TexCords;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};
struct Light {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadradic;
};

uniform Material material;
uniform Light light;

out vec4 FragColor;
void main(){
    float lightDistance = length(LightPos - fragPos);
    float lightIntensity = 1.0/(light.constant + lightDistance * light.linear + lightDistance * lightDistance * light.quadradic);
    vec3 objColor = vec3(texture(material.diffuse, TexCords));
    vec3 ambient = objColor * light.ambient * lightIntensity;

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(LightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = (objColor * diff) * light.diffuse * lightIntensity;

    vec3 viewDir = normalize(-fragPos);
    vec3 lightRef = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, lightRef), 0.0), 128);
    vec3 specular = (vec3(texture(material.specular, TexCords)) * spec) * light.specular * lightIntensity;

    vec3 sum = ambient + diffuse + specular;
    FragColor = vec4(sum, 1.0); 
}
