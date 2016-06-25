#version 330

smooth in vec2 o_texCoord;
out vec4 outColour;

uniform sampler2D tex;

void main() {
    outColour = texture(tex, o_texCoord);
}
