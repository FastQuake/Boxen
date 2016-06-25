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
}

void Renderer::clear(bool depth) {
    int flags = GL_COLOR_BUFFER_BIT;
    if(depth) {
        flags |= GL_DEPTH_BUFFER_BIT;
    }

    glClear(flags);
}
