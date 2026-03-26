
#include "PacmanGameState.hpp"
#include "PacmanMenuState.hpp"
#include "engine/Engine.hpp"

PacmanGameState::PacmanGameState(Engine& eng) : engine(eng) {
    game.init("assets/maps/map.txt");
}

void PacmanGameState::handleInput(InputKey input) {
    if (input == InputKey::QUIT || input == InputKey::ESCAPE) {
        engine.setState(std::make_unique<PacmanMenuState>(engine));
        return;
    }
    game.handleInput(input);
}

void PacmanGameState::update(double dt) {
    game.update(dt);
    for (auto event : game.events) {
        engine.getAudio().playEvent(event);
    }
    game.events.clear();
}

void PacmanGameState::render(IRenderer& renderer) {
    game.render(renderer);
}