#include <glm/gtc/matrix_transform.hpp>
#include "Model.hpp"
#include "../ResourceManager/ResourceManager.hpp"
using namespace std;

Model::Model(const string &filename) {
    ResourceManager *rm = ResourceManager::instance();
    modelData = rm->loadIqmModel(filename);
}

void Model::draw(Uniforms unis) {
    std::vector<iqmmesh> &meshes = modelData->getMeshes();
    std::vector<Texture*> &textures = modelData->getTextures();
    glBindVertexArray(modelData->getVao());

    glm::mat4 pos = glm::translate(glm::mat4(1.0), position);
    glUniformMatrix4fv(unis.model, 1, false, &pos[0][0]);
    glUniform1i(unis.tex, 0);
    for(size_t i = 0; i < meshes.size(); i++) {
        iqmtriangle *tris = NULL;
        iqmmesh &m = meshes[i];
        glBindTexture(GL_TEXTURE_2D, textures[i]->getGlName());

        glDrawElements(GL_TRIANGLES, 3*m.num_triangles, GL_UNSIGNED_INT, &tris[m.first_triangle]);
    }
}
