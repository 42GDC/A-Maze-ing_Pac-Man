#pragma once

#include "IRenderer.hpp"

class TerminalRenderer : public IRenderer
{
public:
    void clear() override;
    void present() override;
    void drawTile(int x, int y, char c) override;
    // void drawMap(const Map& map) override;
    void drawText(const std::string& text) override;
};
