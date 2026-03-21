#pragma once
#include "engine/IGameState.hpp"

class Engine;

class PacmanMenuState : public IGameState {
private:
    Engine& engine;

public:
    PacmanMenuState(Engine& eng);

    void handleInput(InputKey input) override;
    void update(double dt) override;
    void render(IRenderer& renderer) override;
};