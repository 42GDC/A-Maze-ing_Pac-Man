#pragma once
#include "input/Input.hpp"
#include "render/IRenderer.hpp"

class IGameState {
public:
    virtual ~IGameState() = default;

    virtual void handleInput(InputKey input) = 0;
    virtual void update(double dt) = 0;
    virtual void render(IRenderer& renderer) = 0;
};