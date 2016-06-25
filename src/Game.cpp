#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Game.hpp"
#include "Error.hpp"
#include "Renderer/Quad.hpp"
#include "Renderer/Model.hpp"
#include "Renderer/Camera.hpp"
#include "ResourceManager/ResourceManager.hpp"

#include <iostream>

#define SDL_ERROR "SDL_ERROR"
#define BITS_PER_PIXEL 8

using namespace std;

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
    Model cube("cube.iqm");
    Camera cam;
    bool running = true;
    SDL_Event e;
    renderer.setProj(glm::perspective<float>(M_PI/2.0, 800/600, 1.0, 1000.0));
    while(running) {
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) {
                running = false;
            }

            if(e.type == SDL_KEYDOWN) {
                switch(e.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        running = false;
                        break;
                    case SDLK_w:
                        cam.move(1);
                        break;
                    case SDLK_s:
                        cam.move(-1);
                        break;
                    case SDLK_a:
                        cam.strafe(-1);
                        break;
                    case SDLK_d:
                        cam.strafe(1);
                        break;
                    case SDLK_LEFT:
                        cam.turn(0, 0.2);
                        break;
                    case SDLK_RIGHT:
                        cam.turn(0, -0.2);
                        break;
                }
            }

            if(e.type == SDL_WINDOWEVENT) {
                switch(e.window.event) {
                    case SDL_WINDOWEVENT_FOCUS_GAINED:
                        SDL_SetRelativeMouseMode(SDL_TRUE);
                        break;
                    case SDL_WINDOWEVENT_FOCUS_LOST:
                        SDL_SetRelativeMouseMode(SDL_FALSE);
                        break;
                }
            }

            if(e.type == SDL_MOUSEMOTION && SDL_GetWindowFlags(window) & SDL_WINDOW_INPUT_FOCUS) {
                cout << "xrel: " << e.motion.xrel << " yrel: " << e.motion.yrel << endl;
                cam.turn(e.motion.yrel, e.motion.xrel);
            }
        }

        renderer.setView(cam.view());
        renderer.clear(true);
        cube.draw(renderer.shaderUnis);

        SDL_GL_SwapWindow(window);
    }
}

void Game::checkSDLError() {
    const char *errorMessage = SDL_GetError();

    if(*errorMessage != '\0') {
        throw ErrMsg(SDL_ERROR, errorMessage);
    }
}
