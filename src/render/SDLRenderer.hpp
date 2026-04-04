#pragma once

#include "IRenderer.hpp"
#include <SDL3/SDL.h>
#include <string>

class SDLRenderer : public IRenderer
{
public:
    SDLRenderer();
    ~SDLRenderer();

    bool init();
    void shutdown();

    void clear() override;
    void present() override;
    void drawTile(int x, int y, char c) override;
    void drawText(const std::string& text) override;

private:
    SDL_Window* window;
    SDL_Renderer* renderer;


    bool loadTexture(const std::string& path, SDL_Texture*& outTexture);
    SDL_Texture* pelletTexture;
    SDL_Texture* powerPelletTexture;
    SDL_Texture* wallTexture;
    SDL_Texture* pacmanTexture;
    // sprites and fonts would go here, but we don't have any yet
    // pacman 4 directions, 3 frames each = 12 sprites
    // 4 ghosts, 4 directions, 2 frames each = 32 sprites
    // ghost eyes, 4 directions = 4 sprites
    // frightened ghost, 2 frames = 2 sprites
    // white ghost, 2 frames = 2 sprites
    // pellets, powerpellets, fruits
    // ghost targets, pacman target
    // walls
    // paths
    // fonts (score, lives, level, etc.)
    // Ready msg, point sprites (100, 200, 400, 800, 1600...)
    int tileSize = 16; //not used, initialised in constructor
};