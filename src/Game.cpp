#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Game.hpp"
#include "Error.hpp"
#include "Renderer/Quad.hpp"
#include "Renderer/Model.hpp"
#include "Renderer/Camera.hpp"
#include "ResourceManager/ResourceManager.hpp"
#include "Timer.hpp"

#define SDL_ERROR "SDL_ERROR"
#define BITS_PER_PIXEL 8

#define MOUSE_SENSE 100.0

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
    Model fixit("mrfixit.iqm");
    Model cube("cube.iqm");
    Camera cam;
    bool running = true;
    SDL_Event e;
    renderer.setProj(glm::perspective<float>(M_PI/2.0, 800/600, 0.1, 1000.0));
    Timer timer;
    float dt = 0.0;

    const uint8_t *keystate = SDL_GetKeyboardState(NULL);
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
                cam.turn(e.motion.yrel*dt*MOUSE_SENSE, e.motion.xrel*dt*MOUSE_SENSE);
            }
        }

        if(keystate[SDL_GetScancodeFromKey(SDLK_w)]) {
            cam.move(10*dt);
        }
        if(keystate[SDL_GetScancodeFromKey(SDLK_s)]) {
            cam.move(-10*dt);
        }
        if(keystate[SDL_GetScancodeFromKey(SDLK_a)]) {
            cam.strafe(-10*dt);
        }
        if(keystate[SDL_GetScancodeFromKey(SDLK_d)]) {
            cam.strafe(10*dt);
        }

        renderer.setView(cam.view());
        renderer.clear(true);
        cube.draw(renderer.shaderUnis);
        fixit.draw(renderer.shaderUnis);

        SDL_GL_SwapWindow(window);

        dt = timer.getElapsedTime();
        timer.reset();
    }
}

void Game::checkSDLError() {
    const char *errorMessage = SDL_GetError();

    if(*errorMessage != '\0') {
        throw ErrMsg(SDL_ERROR, errorMessage);
    }
}
