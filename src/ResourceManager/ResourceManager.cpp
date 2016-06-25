#include <SDL2/SDL_image.h>
#include "ResourceManager.hpp"
#include "../Error.hpp"
using namespace std;

#define RESOURCE_ERROR "RESOURCE MANAGER ERROR"

ResourceManager *ResourceManager::rm = NULL;

ResourceManager::ResourceManager(Renderer &renderer) {
    this->renderer = &renderer;
}

void ResourceManager::createInstance(Renderer &renderer) {
    if(rm != NULL) {
        throw ErrMsg(RESOURCE_ERROR, "Resource manager instance already created");
    }

    ResourceManager::rm = new ResourceManager(renderer);
}

ResourceManager *ResourceManager::instance() {
    if(rm == NULL) {
        throw ErrMsg(RESOURCE_ERROR, "Resource manager has not been initalized");
    }
    return rm;
}

Texture *ResourceManager::loadTexture(string name) {
    map<string, Texture*>::iterator it;
    it = this->textures.find(name);
    if(it != this->textures.end()) {
        return it->second;
    }

    SDL_Surface *image = IMG_Load(name.c_str());
    // TODO switch to load default texture
    if(image == NULL) {
        throw ErrMsg(RESOURCE_ERROR, "Could not load image: "+name);
    }
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
