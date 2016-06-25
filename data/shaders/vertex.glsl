#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;

smooth out vec2 o_texCoord;

uniform mat4 mvp;

void main() {
    gl_Position = mvp * vec4(position, 1.0);
    o_texCoord = texCoord;
}
