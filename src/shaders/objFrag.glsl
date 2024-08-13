#version 330 core
in vec3 Normal;
in vec3 fragPos;
in mat4 VeiwMat;
in vec2 TexCords;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};
struct DirLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
struct PointLight {
    vec3 position;
    float constant;
    float linear;
    float quadradic;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
struct SpotLight {
    vec3 position;
    vec3 direction;
    float innerCutoff;
    float outerCutoff;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

#define maxDirLights 5
#define maxPointLights 20
#define maxSpotLights 10
uniform Material material;
uniform DirLight dirLights[maxDirLights];
uniform PointLight pointLights[maxPointLights];
uniform SpotLight spotLights[maxSpotLights];
uniform int numDirLights;
uniform int numPointLights;
uniform int numSpotLights;

vec3 calcDirLight(DirLight light, vec3 normal, vec3 veiwDir);
vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 veiwDir);
vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 veiwDir);

out vec4 FragColor;
void main(){
    vec3 normal = normalize(Normal);
    vec3 veiwDir = normalize(-fragPos);

    vec3 sum = vec3(0, 0, 0);
    for(int i=0; i<numDirLights; i++){
        sum += calcDirLight(dirLights[i], normal, veiwDir);
    }
    for(int i=0; i<numPointLights; i++){
        sum+= calcPointLight(pointLights[i], normal, fragPos, veiwDir);
    }
    for(int i=0; i<numSpotLights; i++){
        sum += calcSpotLight(spotLights[i], normal, fragPos, veiwDir);
    }

    FragColor = vec4(sum, 1.0); 
}

vec3 calcDirLight(DirLight light, vec3 normal, vec3 veiwDir){
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(veiwDir, reflectDir), 0), material.shininess);
    vec3 fragColor = vec3 (texture(material.diffuse, TexCords));
    vec3 ambient = light.ambient * fragColor;
    vec3 diffuse = light.diffuse * diff * fragColor;
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCords));

    return ambient + diffuse + specular;
}

vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 veiwDir){
    vec3 lightPos = vec3(VeiwMat * vec4(light.position, 1));
    vec3 lightDir = normalize(fragPos - lightPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(veiwDir, reflectDir), 0.0), material.shininess);

    vec3 fragColor = vec3(texture(material.diffuse, TexCords));
    vec3 ambient = light.ambient * fragColor;
    vec3 diffuse = light.diffuse * diff * fragColor;
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCords));

    float distance = length(lightPos - fragPos);
    float attenuation = 1.0/(light.constant + light.linear * distance + light.quadradic * distance * distance);
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return ambient + diffuse + specular;
}

vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 veiwDir){
    vec3 lightDir = normalize(fragPos - light.position);

    float diff = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(veiwDir, reflectDir), 0.0), material.shininess);

    vec3 fragColor = vec3(texture(material.diffuse, TexCords));
    vec3 ambient = light.ambient * fragColor;
    vec3 diffuse = light.diffuse * diff * fragColor;
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCords));

    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.innerCutoff - light.outerCutoff;
    float intensity = clamp((theta - light.outerCutoff) / epsilon, 0.0, 1.0);
    diffuse *= intensity;
    specular *= intensity;

    return ambient + diffuse + specular;
}
