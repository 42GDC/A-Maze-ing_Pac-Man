#include "PacmanMenuState.hpp"
#include "PacmanGameState.hpp"
#include "engine/Engine.hpp"

PacmanMenuState::PacmanMenuState(Engine& eng) : engine(eng) {
    engine.getAudio().playMusic("menu", -1);
}

void PacmanMenuState::handleInput(InputKey input) {
    if (input == InputKey::ENTER) {
        engine.getAudio().stopMusic();
        engine.setState(std::make_unique<PacmanGameState>(engine));
    }
    else if (input == InputKey::ESCAPE || input == InputKey::QUIT) {
        engine.stop();
    }
}

void PacmanMenuState::update(double) {}

void PacmanMenuState::render(IRenderer& renderer) {
    renderer.drawText("PACMAN\nPress ENTER\nQ to quit");
}