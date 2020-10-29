#version 410 core

layout (location = 0) in vec2 pos;
layout (location = 1) in vec3 color;

out vec3 vertexColor;

uniform mat4 projection;
uniform mat4 modelMatrix;

void main() {
    gl_Position = projection * modelMatrix * vec4(pos, 0.0f, 1.0f);
    vertexColor = color;
}