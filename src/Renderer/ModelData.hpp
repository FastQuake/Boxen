#ifndef MODELDATA_HPP
#define MODELDATA_HPP
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include "gl_33.hpp"
#include "Texture.hpp"
#include "../ResourceManager/iqmloader.hpp"

class ModelData {
    public:
        ModelData(const IQMModelData &model);
        
        GLuint getVao();
        std::vector<Texture*> &getTextures();
        std::vector<iqmmesh> &getMeshes();
    private:
        GLuint vbo, ebo;
        GLuint vao;
        std::vector<Texture*> textures;
        std::vector<iqmmesh> meshes;
};

#endif
