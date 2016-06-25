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
    glUseProgram(shader.getID());

    shaderUnis.model = shader.getUniform("model");
    shaderUnis.view = shader.getUniform("view");
    shaderUnis.projection = shader.getUniform("projection");
    shaderUnis.tex = shader.getUniform("tex");

    setProj(glm::mat4(1.0));
    setView(glm::mat4(1.0));
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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height,
                 0, format, GL_UNSIGNED_BYTE, pixels);
    glBindTexture(GL_TEXTURE_2D, 0);
    return texName;
}

void Renderer::setView(glm::mat4 view) {
    glUniformMatrix4fv(shaderUnis.view, 1, false, &view[0][0]);
}

void Renderer::setProj(glm::mat4 proj) {
    glUniformMatrix4fv(shaderUnis.projection, 1, false, &proj[0][0]);
}
