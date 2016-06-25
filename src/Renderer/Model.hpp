#ifndef MODEL_HPP
#define MODEL_HPP
#include <string>
#include "ModelData.hpp"
#include "Renderer.hpp"

class Model {
    public:
        glm::vec3 position;

        Model(const std::string &filename);

        void draw(Uniforms unis);
    private:
        ModelData *modelData;
};

#endif
