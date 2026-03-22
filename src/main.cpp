#include "engine/Engine.hpp"
#include "render/TerminalRenderer.hpp"
#include "render/SDLRenderer.hpp"

#include "games/pacman/states/PacmanMenuState.hpp"

int main() {
    SDLRenderer renderer;
    if (!renderer.init())
        return 1;
    Engine engine(renderer);

    engine.setState(std::make_unique<PacmanMenuState>(engine));
    engine.run();

    renderer.shutdown();
    return 0;
}
