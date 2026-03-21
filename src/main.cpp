#include "engine/Engine.hpp"
#include "render/TerminalRenderer.hpp"
#include "games/pacman/states/PacmanMenuState.hpp"

int main() {
    TerminalRenderer renderer;
    Engine engine(renderer);

    engine.setState(std::make_unique<PacmanMenuState>(engine));
    engine.run();

    return 0;
}
