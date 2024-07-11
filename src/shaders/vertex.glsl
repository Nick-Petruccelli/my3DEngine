#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;
layout (location = 2) in vec2 aTexCord;

uniform mat4 tranformMat;

out vec3 vertColor;
out vec2 texCord;
void main()
{
    gl_Position = transformMat*vec4(aPos.x, aPos.y, aPos.z, 1.0);
    vertColor = aCol;
    texCord = aTexCord;
}
