#ifndef RESOURCEMANAGER_HPP_
#define RESOURCEMANAGER_HPP_

#include <cstdint>
#include <map>
#include "../Renderer/gl_33.hpp"
#include "../Renderer/Renderer.hpp"

class Texture { // Will be moved elsewhere
    private:
        int width, height;
        GLuint glName;

    public:
        Texture(int width, int height, GLuint glName);
        int getWidth();
        int getHeight();
        GLuint getGlName();
};

class ResourceManager {
    private:
        std::map<std::string, Texture*> textures;
        Renderer *renderer;

    public:
        ResourceManager(Renderer &renderer);
        Texture *loadTexture(std::string name);
};
#endif
