#ifndef TEXTURE_HPP
#define TEXTURE_HPP
#include "gl_33.hpp"

class Texture {
    private:
        int width, height;
        GLuint glName;

    public:
        Texture(int width, int height, GLuint glName);
        int getWidth();
        int getHeight();
        GLuint getGlName();
};

#endif
