#ifndef RESOURCEMANAGER_HPP_
#define RESOURCEMANAGER_HPP_

#include <cstdint>
#include <map>
#include "../Renderer/Renderer.hpp"
#include "../Renderer/Texture.hpp"

class ResourceManager {
    private:
        static ResourceManager *rm;
        std::map<std::string, Texture*> textures;
        Renderer *renderer;

    public:
        ResourceManager(Renderer &renderer);
        Texture *loadTexture(std::string name);

        static void createInstance(Renderer &renderer);
        static ResourceManager *instance();
};
#endif
