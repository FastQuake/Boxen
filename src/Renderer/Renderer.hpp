#ifndef RENDERER_HPP
#define RENDERER_HPP
#include "gl_33.hpp"
#include "Shader.hpp"

class Renderer {
    public:

        void init();
        void clear(bool depth);
    private:
        ShaderProgram shader;
};

#endif
