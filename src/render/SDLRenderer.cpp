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
    // 0: right, 1: down, 2: left, 3: up
    if (!loadTexture("assets/sprites/pacman/pacman_right3.png", pacmanTextures[0][0])) {
        return false;
    }
    if (!loadTexture("assets/sprites/pacman/pacman_right2.png", pacmanTextures[0][1])) {
        return false;
    }
    pacmanTextures[0][3] = pacmanTextures[0][1];
    pacmanTextures[0][2] = pacmanTexture; //full
    if (!loadTexture("assets/sprites/pacman/pacman_down3.png", pacmanTextures[1][0])) {
        return false;
    }
    if (!loadTexture("assets/sprites/pacman/pacman_down2.png", pacmanTextures[1][1])) {
        return false;
    }
    pacmanTextures[1][3] = pacmanTextures[1][1];
    pacmanTextures[1][2] = pacmanTexture; //full
    if (!loadTexture("assets/sprites/pacman/pacman_left3.png", pacmanTextures[2][0])) {
        return false;
    }
    if (!loadTexture("assets/sprites/pacman/pacman_left2.png", pacmanTextures[2][1])) {
        return false;
    }
    pacmanTextures[2][3] = pacmanTextures[2][1];
    pacmanTextures[2][2] = pacmanTexture; //full
    if (!loadTexture("assets/sprites/pacman/pacman_up3.png", pacmanTextures[3][0])) {
        return false;
    }
    if (!loadTexture("assets/sprites/pacman/pacman_up2.png", pacmanTextures[3][1])) {
        return false;
    }
    pacmanTextures[3][3] = pacmanTextures[3][1];
    pacmanTextures[3][2] = pacmanTexture; //full

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

        case TileType::Player: { // player 
            uint8_t frame = (x + y) % 16 / 4;
            texture = pacmanTextures[dir % 4][frame];
            break;
        }

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

    if (pacmanTexture) {
        SDL_DestroyTexture(pacmanTexture);
        pacmanTexture = nullptr;
    }


    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 2; j++) {
            if (pacmanTextures[i][j]) {
                SDL_DestroyTexture(pacmanTextures[i][j]);
                pacmanTextures[i][j] = nullptr;
            }
        }
    }
}