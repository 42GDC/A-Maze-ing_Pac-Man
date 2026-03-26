#pragma once

#include <vector>
#include "map/Map.hpp"
#include "input/InputKey.hpp"
#include "render/IRenderer.hpp"
#include "PacmanEvent.hpp"

struct Vec2 {
    int x;
    int y;
};

class PacmanGame {
public:
    Map map;

    Vec2 playerPos{};
    int playerDir = 2; // 0: right, 1: down, 2: left, 3: up
    int playerNextDir = 2;
    int playerSpeed = 2; // pixels per frame
    int score = 0;
    int tileSize = 16;

    std::vector<PacmanEvent> events;

    void init(const std::string& mapPath);

    void handleInput(InputKey input);
    void update(double dt);
    void render(IRenderer& renderer);

private:
    void movePlayer(void);
};