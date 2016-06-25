#include <iostream>
#include "ModelData.hpp"
#include "../ResourceManager/ResourceManager.hpp"
using namespace std;

ModelData::ModelData(const IQMModelData &model) {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.triangles.size()*sizeof(iqmtriangle), &model.triangles[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, model.verticies.size()*sizeof(Vertex), &model.verticies[0], GL_STATIC_DRAW);

    Vertex *p = NULL;
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
            0,
            3,
            GL_FLOAT,
            false,
            sizeof(Vertex),
            &p->position);
    glVertexAttribPointer(
            1,
            2,
            GL_FLOAT,
            false,
            sizeof(Vertex),
            &p->texcoord);

    ResourceManager *rm = ResourceManager::instance();

    for(size_t i = 0; i < model.textures.size(); i++) {
        textures.push_back(rm->loadTexture(model.textures[i])); 
    }

    meshes = model.meshes;
}

GLuint ModelData::getVao() {
    return vao;
}

std::vector<Texture*> &ModelData::getTextures() {
    return textures;
}

std::vector<iqmmesh> &ModelData::getMeshes() {
    return meshes;
}
