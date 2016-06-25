#include <SDL2/SDL_image.h>
#include "ResourceManager.hpp"
#include "../Error.hpp"
using namespace std;

#define RESOURCE_ERROR "RESOURCE MANAGER ERROR"

#define BASE_DIR "./data/"
#define MODEL_DIR BASE_DIR "models/"
#define TEX_DIR BASE_DIR "textures/"

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

    string filename = TEX_DIR + name;
    SDL_Surface *image = IMG_Load(filename.c_str());
    // TODO switch to load default texture
    if(image == NULL) {
        throw ErrMsg(RESOURCE_ERROR, "Could not load image: "+filename);
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

ModelData *ResourceManager::loadIqmModel(string name) {
    map<string, ModelData*>::iterator it;
    it = this->models.find(name);
    if(it != this->models.end()) {
        return it->second;
    }

    string filename = MODEL_DIR + name;
    IQMModelData data;
    if(loadIQM(filename, data) == false) {
        throw ErrMsg(RESOURCE_ERROR, "IQM file does not exists: "+filename);
    }

    ModelData *md = new ModelData(data);
    models.insert(pair<string, ModelData*>(name, md));
    return md;
}
