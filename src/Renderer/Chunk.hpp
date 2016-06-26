#ifndef CHUNK_HPP
#define CHUNK_HPP
#include <cstdint>
#include "gl_33.hpp"

#define SIZEX 16
#define SIZEY 64
#define SIZEZ 16

class Chunk {
    public:

        uint8_t get(int x, int y, int z);
        void set(int x, int y, int z, uint8_t type);
    private:
        uint8_t blocks[SIZEX][SIZEY][SIZEZ];
        GLuint vbo;
        GLuint vao;
        

        void update();
};

#endif
