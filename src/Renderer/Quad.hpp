#ifndef QUAD_HPP
#define QUAD_HPP
#include <string>
#include "gl_33.hpp"

class Quad {
    public:
        Quad(const std::string &texture);

        void draw();
    private:
        static GLuint vbo;
        static GLuint vao;

};

#endif
