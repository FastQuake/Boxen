#ifndef RENDERER_HPP
#define RENDERER_HPP
#include <glm/glm.hpp>
#include "gl_33.hpp"
#include "Shader.hpp"

struct Uniforms {
    GLint model, view, projection;
    GLint tex;
};

class Renderer {
    public:
        Uniforms shaderUnis;

        void init();
        void clear(bool depth);
        GLuint genTexture(int width, int height, GLenum format, void *pixels);

        void setView(glm::mat4 view);
        void setProj(glm::mat4 proj);
    private:
        ShaderProgram shader;
};

#endif
