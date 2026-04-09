#include "SDLInput.hpp"
#include <SDL3/SDL.h>

InputKey SDLInput::pollInput() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            return InputKey::QUIT;
        }

        if (event.type == SDL_EVENT_KEY_DOWN) {
            switch (event.key.key) {
                case SDLK_W: return InputKey::UP;
                case SDLK_S: return InputKey::DOWN;
                case SDLK_A: return InputKey::LEFT;
                case SDLK_D: return InputKey::RIGHT;
                case SDLK_UP: return InputKey::UP;
                case SDLK_DOWN: return InputKey::DOWN;
                case SDLK_LEFT: return InputKey::LEFT;
                case SDLK_RIGHT: return InputKey::RIGHT;

                case SDLK_RETURN: return InputKey::ENTER;
                case SDLK_ESCAPE: return InputKey::ESCAPE;
                case SDLK_Q: return InputKey::QUIT;
            }
        }
    }

    return InputKey::NONE;
}