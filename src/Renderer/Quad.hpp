#ifndef QUAD_HPP
#define QUAD_HPP
#include <string>
#include <glm/glm.hpp>
#include "gl_33.hpp"
#include "Texture.hpp"
#include "Renderer.hpp"

class Quad {
    public:
        glm::vec3 position;

        Quad(const std::string &texture);

        void draw(Uniforms unis);
    private:
        static GLuint vbo;
        static GLuint vao;

        Texture *tex;
};

#endif
