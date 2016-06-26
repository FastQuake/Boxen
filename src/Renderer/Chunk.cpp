#include "Chunk.hpp"


uint8_t Chunk::get(int x, int y, int z) {
    return blocks[x][y][z];
}

void Chunk::set(int x, int y, int z, uint8_t type) {
    blocks[x][y][z] = type;
}

