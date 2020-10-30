#version 410 core

layout (location = 0) in vec2 pos;

out vec3 vertexColor;

uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;
uniform vec3 color;

void main() {
    gl_Position = projectionMatrix * modelMatrix * vec4(pos, 0.0f, 1.0f);
    vertexColor = color;
}