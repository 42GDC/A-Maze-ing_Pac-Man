#pragma once

#include "IRenderer.hpp"

class SDLRenderer : public IRenderer
{
public:
    void clear() override;
    void present() override;
    void drawTile(int x, int y, char c) override;
    void drawText(const std::string& text) override;
};
