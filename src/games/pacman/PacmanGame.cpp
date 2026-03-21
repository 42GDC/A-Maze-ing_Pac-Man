#include "PacmanGame.hpp"
#include "map/MapEditor.hpp"
#include "render/IRenderer.hpp"

void PacmanGame::init(const std::string& mapPath) {
    MapEditor editor(map);
    editor.buildFromPath(mapPath);

    // find spawn
    for (uint32_t y = 0; y < map.height(); y++) {
        for (uint32_t x = 0; x < map.width(); x++) {
            if (map.get(x, y) == TileType::PlayerSpawn) { // TODO: rename to getTile
                playerPos = {(int)x, (int)y};
            }
        }
    }

    events.push_back(PacmanEvent::GAME_STARTED);
}

void PacmanGame::handleInput(InputKey input) {
    switch (input) {
        case InputKey::UP: movePlayer(0, -1); break;
        case InputKey::DOWN: movePlayer(0, 1); break;
        case InputKey::LEFT: movePlayer(-1, 0); break;
        case InputKey::RIGHT: movePlayer(1, 0); break;
        default: break;
    }
}

void PacmanGame::movePlayer(int dx, int dy) {
    int nx = playerPos.x + dx;
    int ny = playerPos.y + dy;

    if (map.get(nx, ny) == TileType::Wall)
        return;

    playerPos = {nx, ny};
    events.push_back(PacmanEvent::PLAYER_MOVED);

    if (map.get(nx, ny) == TileType::Pellet) {
        score += 10;
        events.push_back(PacmanEvent::PELLET_EATEN);
    }
}

void PacmanGame::update(double) {}

void PacmanGame::render(IRenderer& renderer) {
    for (uint32_t y = 0; y < map.height(); y++) {
        for (uint32_t x = 0; x < map.width(); x++) {
            char c = ' ';

            switch (map.get(x, y)) {
                case TileType::Wall: c = '#'; break;
                case TileType::Pellet: c = '.'; break;
                default: break;
            }

            if (playerPos.x == (int)x && playerPos.y == (int)y)
                c = 'P';

            renderer.drawTile(x, y, c);
        }
    }
}