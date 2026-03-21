#pragma once

#include <memory>
#include "IGameState.hpp"
#include "render/IRenderer.hpp"

class Engine {
public:
    Engine(IRenderer& renderer);

    void setState(std::unique_ptr<IGameState> newState);
    void run();
    void stop();

    IRenderer& getRenderer();

private:
    std::unique_ptr<IGameState> currentState;
    IRenderer& renderer;

    bool running = true;
};