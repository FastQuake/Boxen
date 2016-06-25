#include <iostream>
#include <SDL2/SDL.h>

#define BITS_PER_PIXEL 8

using namespace std;

void initSDL();

int main(int argc, char **argv) {
    cout << "Hello World!" << endl;

    initSDL();
    SDL_Window *window = SDL_CreateWindow("Hello World!",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          800, 600,
                                          SDL_WINDOW_OPENGL);

    SDL_GLContext context = SDL_GL_CreateContext(window);
    if(context == NULL) {
        cout << "Context creation failed: " << SDL_GetError() << endl;
    }

    return 0;
}

void initSDL() {
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, BITS_PER_PIXEL);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, BITS_PER_PIXEL);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, BITS_PER_PIXEL);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, BITS_PER_PIXEL);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
}
