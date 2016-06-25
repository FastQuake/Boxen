#include "Texture.hpp"

Texture::Texture(int width, int height, GLuint glName) {
    this->width = width;
    this->height = height;
    this->glName = glName;
}

int Texture::getWidth() {
    return width;
}

int Texture::getHeight() {
    return height;
}

GLuint Texture::getGlName() {
    return glName;
}
