#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec2 aTex;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform vec3 lightPos;

out vec3 normal;
out vec3 fragPos;
out vec3 LightPos;
out vec2 TexCords;

void main()
{
    normal = mat3(transpose(inverse(view * model))) * aNorm;
    fragPos = vec3(view * model * vec4(aPos, 1.0));
    LightPos = vec3(view * vec4(lightPos, 1.0));
    TexCords = aTex;
    gl_Position = proj * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
