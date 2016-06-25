#include "ResourceManager.hpp"
#include <SDL2/SDL_image.h>

using namespace std;

Texture::Texture(int width, int height, GLuint glName) {
    this->width = width;
    this->height = height;
    this->glName = glName;
}

ResourceManager::ResourceManager(Renderer &renderer) {
    this->renderer = &renderer;
}

Texture *ResourceManager::loadTexture(string name) {
    map<string, Texture*>::iterator it;
    it = this->textures.find(name);
    if(it != this->textures.end()) {
        return it->second;
    }

    SDL_Surface *image = IMG_Load(name.c_str());
    int width = image->w;
    int height = image->h;
    GLenum glFormat;
    switch(image->format->BytesPerPixel) {
        case 3: // *Probably* RGB
            glFormat = GL_RGB;
        case 4: // *Probably* RGBA
            glFormat = GL_RGBA;
    }

    GLuint texName = this->renderer->genTexture(width, height,
                                                glFormat, image->pixels);
    Texture *newTex = new Texture(width, height, texName);
    this->textures.insert(pair<string, Texture*>(name, newTex));
    SDL_FreeSurface(image);
    return newTex;
}
