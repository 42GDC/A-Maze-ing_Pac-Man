#include "PacmanGame.hpp"
#include "map/MapEditor.hpp"
#include "render/IRenderer.hpp"

#include <iostream>

void PacmanGame::init(const std::string& mapPath) {
    MapEditor editor(map);
    editor.buildFromPath(mapPath);

    // find spawn
    for (uint32_t y = 0; y < map.height(); y++) {
        for (uint32_t x = 0; x < map.width(); x++) {
            if (map.get(x, y) == TileType::PlayerSpawn) { // TODO: rename to getTile
                playerPos = {(int)x * tileSize, (int)y * tileSize};
            }
        }
    }

    events.push_back(PacmanEvent::GAME_STARTED);
}

void PacmanGame::handleInput(InputKey input) {
    switch (input) {
        case InputKey::UP: playerNextDir = 3; break;
        case InputKey::DOWN: playerNextDir = 1; break;
        case InputKey::LEFT: playerNextDir = 2; break;
        case InputKey::RIGHT: playerNextDir = 0; break;
        default: break;
    }
}

void PacmanGame::movePlayer(void) {
    int dx = 0;
    int dy = 0;
    // std::cout << "Handling player movement..." << std::endl;
    // std::cout << "Player direction: " << playerDir << ", next direction: " << playerNextDir << std::endl;
    // std::cout << "Player position: (" << playerPos.x << ", " << playerPos.y << ")" << std::endl;

    switch (playerDir) {
        case 0: dx = playerSpeed; break; // right
        case 1: dy = playerSpeed; break; // down
        case 2: dx = -playerSpeed; break; // left
        case 3: dy = -playerSpeed; break; // up
    }
    //try to move in old direction
    int nx = playerPos.x + tileSize * dx / playerSpeed;
    int ny = playerPos.y + tileSize * dy / playerSpeed;
    //check if new tile is not wall
    if (playerPos.x % tileSize || playerPos.y % tileSize || map.get(nx / tileSize, ny / tileSize) != TileType::Wall) {
        if (map.get(nx / tileSize, ny / tileSize) == TileType::Pellet && playerPos.x % tileSize == 0 && playerPos.y % tileSize == 0) {
            score += 10;
            events.push_back(PacmanEvent::PELLET_EATEN);
            map.set(nx / tileSize, ny / tileSize, TileType::Empty);
        }
        if (map.get(nx / tileSize, ny / tileSize) == TileType::PowerPellet && playerPos.x % tileSize == 0 && playerPos.y % tileSize == 0) {
            score += 50;
            events.push_back(PacmanEvent::POWER_PELLET_EATEN);
            map.set(nx / tileSize, ny / tileSize, TileType::Empty);
        }
        playerPos.x += dx;
        playerPos.y += dy;
        events.push_back(PacmanEvent::PLAYER_MOVED);
    }
    if (playerPos.x < tileSize * 2)
        playerPos.x = (map.width() - 3) * tileSize;
    else if ((uint32_t)playerPos.x >= (map.width() - 3) * tileSize)
        playerPos.x = tileSize * 2;
    if (playerPos.y < tileSize * 2)
        playerPos.y = (map.height() - 3) * tileSize;
    else if ((uint32_t)playerPos.y >= (map.height() - 3) * tileSize)
        playerPos.y = tileSize * 2;

    dx = 0;
    dy = 0;
    // try to move in new direction if possible
    switch (playerNextDir) {
        case 0: dx = playerSpeed; break; // right
        case 1: dy = playerSpeed; break; // down
        case 2: dx = -playerSpeed; break; // left
        case 3: dy = -playerSpeed; break; // up
    }
    nx = playerPos.x + tileSize * dx / playerSpeed;
    ny = playerPos.y + tileSize * dy / playerSpeed;
    // std::cout << "Trying to change direction to " << playerNextDir << "..." << std::endl;
    // std::cout << "Tile position in new direction: (" << nx << ", " << ny << ")" << std::endl;
    // std::cout << "Next tile in new direction: (" << nx / tileSize << ", " << ny / tileSize << ") - " << (int)map.get(nx / tileSize, ny / tileSize) << std::endl;
    // std::cout << "Player position mod tileSize: (" << playerPos.x % tileSize << ", " << playerPos.y % tileSize << ")" << std::endl;
    if (map.get(nx / tileSize, ny / tileSize) != TileType::Wall && playerPos.x % tileSize == 0 && playerPos.y % tileSize == 0) {
        playerDir = playerNextDir;
    }
    
    // std::cout << "After handling player movement..." << std::endl;
    // std::cout << "Player direction: " << playerDir << ", next direction: " << playerNextDir << std::endl;
    // std::cout << "Player position: (" << playerPos.x << ", " << playerPos.y << ")" << std::endl;
}

void PacmanGame::update(double) {
    movePlayer();
    // push events?
}

void PacmanGame::render(IRenderer& renderer) {
    static int frameCount = 0;
    frameCount++;
    uint8_t dir = 0;
    for (uint32_t y = 0; y < map.height(); y++) {
        for (uint32_t x = 0; x < map.width(); x++) {
            dir = 0;
            TileType tile = map.get(x, y);
            if (tile == TileType::PowerPellet) {
                dir = (frameCount / 16) % 2; // Alternate between two textures for animation
            }
            renderer.drawTile(x * tileSize, y * tileSize, dir, tile);
        }
    }
    renderer.drawTile(playerPos.x, playerPos.y, playerDir, TileType::Player);
    // draw ghosts, tunnel...
}
