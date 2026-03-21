#include <thread>
#include <chrono>
#include "Engine.hpp"
#include "input/TerminalInput.hpp"

Engine::Engine(IRenderer& renderer)
    : renderer(renderer) {}

void Engine::setState(std::unique_ptr<IGameState> newState) {
    currentState = std::move(newState);
}

IRenderer& Engine::getRenderer() {
    return renderer;
}

void Engine::run() {
    TerminalInput input;

    while (running) {
        InputKey key = input.pollInput();

        if (currentState) {
            currentState->handleInput(key);
            currentState->update(0.016);

            renderer.clear();
            currentState->render(renderer);
            renderer.present();
            std::this_thread::sleep_for(std::chrono::milliseconds(200)); // ~5 FPS
        }
    }
}

void Engine::stop() {
    running = false;
}