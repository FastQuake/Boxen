#include "Game.hpp"
#include "Error.hpp"
#include "Renderer/Quad.hpp"
#include "ResourceManager/ResourceManager.hpp"

#define SDL_ERROR "SDL_ERROR"
#define BITS_PER_PIXEL 8

Game::Game() {
    if(SDL_Init(SDL_INIT_EVERYTHING) == -1) {
        throw ErrMsg(SDL_ERROR, "Failed to initalize SDL");
    }
    checkSDLError();

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, BITS_PER_PIXEL);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, BITS_PER_PIXEL);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, BITS_PER_PIXEL);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, BITS_PER_PIXEL);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3); 

    window = SDL_CreateWindow("Boxen",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          800, 600,
                                          SDL_WINDOW_OPENGL);
    checkSDLError();

    context = SDL_GL_CreateContext(window);
    checkSDLError();

    renderer.init();

    ResourceManager::createInstance(renderer);
}

void Game::run() {
    Quad quad("./data/textures/box.png");
    bool running = true;
    SDL_Event e;
    while(running) {
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) {
                running = false;
            }
        }

        renderer.clear(false);
        quad.draw(renderer.shaderUnis);

        SDL_GL_SwapWindow(window);
    }
}

void Game::checkSDLError() {
    const char *errorMessage = SDL_GetError();

    if(*errorMessage != '\0') {
        throw ErrMsg(SDL_ERROR, errorMessage);
    }
}
