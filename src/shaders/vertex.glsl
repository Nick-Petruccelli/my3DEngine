#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec2 aTex;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform vec3 lightPos;

out vec3 Normal;
out vec3 fragPos;
out mat4 ViewMat;
out vec2 TexCords;

void main()
{
    Normal = mat3(transpose(inverse(view * model))) * aNorm;
    fragPos = vec3(view * model * vec4(aPos, 1.0));
    TexCords = aTex;
    gl_Position = proj * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
