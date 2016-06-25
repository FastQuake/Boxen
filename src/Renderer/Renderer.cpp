#include "Renderer.hpp"
#include "../Error.hpp"

#define RENDER_ERROR "RENDER ERROR"

void Renderer::init() {
    if(ogl_LoadFunctions() == ogl_LOAD_FAILED) {
        throw ErrMsg(RENDER_ERROR, "Failed to load OpenGL functions");
    }

    if(ogl_IsVersionGEQ(3,3) == false) {
        throw ErrMsg(RENDER_ERROR, "OpenGL 3.3 not supported");
    }

    glClearColor(0, 0, 0, 1);


    /* Load shader in */
    shader.init("./data/shaders/vertex.glsl", "./data/shaders/fragment.glsl");
}

void Renderer::clear(bool depth) {
    int flags = GL_COLOR_BUFFER_BIT;
    if(depth) {
        flags |= GL_DEPTH_BUFFER_BIT;
    }

    glClear(flags);
}

GLuint Renderer::genTexture(int width, int height, GLenum format, void *pixels) {
    GLuint texName;
    glGenTextures(1, &texName);

    glBindTexture(GL_TEXTURE_2D, texName);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height,
                 0, format, GL_UNSIGNED_BYTE, pixels);
    glBindTexture(GL_TEXTURE_2D, 0);
    return texName;
}
