#pragma once

#include <string>

class IRenderer {
public:
    virtual ~IRenderer() = default;

    virtual void clear() = 0;
    virtual void present() = 0;

    virtual void drawTile(int x, int y, char c) = 0;
    virtual void drawText(const std::string& text) = 0;
};