#ifndef RESOURCEMANAGER_HPP_
#define RESOURCEMANAGER_HPP_

#include <cstdint>
#include <map>
#include "../Renderer/Renderer.hpp"
#include "../Renderer/Texture.hpp"
#include "../Renderer/ModelData.hpp"

class ResourceManager {
    private:
        static ResourceManager *rm;
        std::map<std::string, Texture*> textures;
        std::map<std::string, ModelData*> models;
        Renderer *renderer;

    public:
        ResourceManager(Renderer &renderer);
        Texture *loadTexture(std::string name);
        ModelData *loadIqmModel(std::string name);

        static void createInstance(Renderer &renderer);
        static ResourceManager *instance();
};
#endif
