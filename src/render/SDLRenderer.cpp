#include "SDLRenderer.hpp"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>

SDLRenderer::SDLRenderer()
    : window(nullptr), renderer(nullptr), tileSize(15) {}

SDLRenderer::~SDLRenderer() {
    shutdown();
}

bool SDLRenderer::loadTexture(const std::string& path, SDL_Texture*& outTexture) {
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (!surface) {
        std::cerr << "IMG_Load failed (" << path << "): " << SDL_GetError() << std::endl;
        return false;
    }

    outTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    if (!outTexture) {
        std::cerr << "SDL_CreateTextureFromSurface failed (" << path << "): " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
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


    // Load textures here (pelletTexture, etc.)
    if (!loadTexture("assets/sprites/other/pellet.png", pelletTexture)) {
        return false;
    }
    if (!loadTexture("assets/sprites/other/power_pellet.png", powerPelletTexture[0])) {
        return false;
    }
    if (!loadTexture("assets/sprites/other/power_pellet2.png", powerPelletTexture[1])) {
        return false;
    }
    if (!loadTexture("assets/sprites/pacman/pacman_full.png", pacmanTexture)) {
        return false;
    }
    if (!loadTexture("assets/sprites/walls/wall_empty.png", wallTexture[1])) { 
        return false;
    }
    if (!loadTexture("assets/sprites/walls/wall_full.png", wallTexture[0])) {
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

void SDLRenderer::drawTile(uint32_t x, uint32_t y, uint8_t dir, TileType tile) {
    SDL_FRect dst;
    dst.x = x;
    dst.y = y;
    dst.w = tileSize;
    dst.h = tileSize;
    (void)dir; // Suppress unused parameter warning
    SDL_Texture* texture = nullptr;

    // Choose color based on tile
    switch (tile) {
        case TileType::Wall: // wall
            texture = wallTexture[dir % 12];
            break;

        case TileType::Pellet: // pellet
            texture = pelletTexture;
            break;

        case TileType::PowerPellet: // powerPellet
            texture = powerPelletTexture[dir & 1]; // Alternate between two textures for animation
            break;

        case TileType::Player: // player
            texture = pacmanTexture;
            break;

        default: // empty
            texture = nullptr;
            break;
    }

    SDL_RenderTexture(renderer, texture, nullptr, &dst);
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

    if (pelletTexture) {
        SDL_DestroyTexture(pelletTexture);
        pelletTexture = nullptr;
    }

}