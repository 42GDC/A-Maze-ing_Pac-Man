
#pragma once
#include "engine/IGameState.hpp"
#include "games/pacman/PacmanGame.hpp"

class Engine;

class PacmanGameState : public IGameState {
private:
    Engine& engine;
    PacmanGame game;

public:
    PacmanGameState(Engine& eng);

    void handleInput(InputKey input) override;
    void update(double dt) override;
    void render(IRenderer& renderer) override;
};