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

    int tileSize = 16; //not used, initialised in constructor
};