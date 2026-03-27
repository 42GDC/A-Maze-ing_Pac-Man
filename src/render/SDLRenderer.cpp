#include "SDLRenderer.hpp"
#include <SDL3/SDL.h>
#include <iostream>

SDLRenderer::SDLRenderer()
    : window(nullptr), renderer(nullptr), tileSize(15) {}

SDLRenderer::~SDLRenderer() {
    shutdown();
}

bool SDLRenderer::init() {
    if (SDL_Init(SDL_INIT_VIDEO) == false) {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("Pacman", 1024, 1024, 0);
    if (!window) {
        std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, nullptr);
    if (!renderer) {
        std::cerr << "SDL_CreateRenderer failed: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void SDLRenderer::clear() {
    // Set background to black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void SDLRenderer::present() {
    SDL_RenderPresent(renderer);
}

void SDLRenderer::drawTile(int x, int y, char c) {
    SDL_FRect rect;
    rect.x = x;
    rect.y = y;
    rect.w = tileSize;
    rect.h = tileSize;

    // Choose color based on tile
    switch (c) {
        case '#': // wall
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
            break;

        case '.': // pellet
            rect.w = 8;
            rect.h = 8;
            rect.x += 4;
            rect.y += 4;
            SDL_SetRenderDrawColor(renderer, 127, 0, 0, 255);
            break;

        case 'P': // player
            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
            break;

        default: // empty
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            break;
    }

    SDL_RenderFillRect(renderer, &rect);
}

void SDLRenderer::drawText(const std::string& text) {
    // Temporary fallback (same behavior as terminal)
    // std::cout << text << std::endl;
    (void)text; // Suppress unused parameter warning
}

void SDLRenderer::shutdown() {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }

    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    // SDL_Quit(); quit SDL in audio for now
}