#pragma once

#include <vector>
#include "map/Map.hpp"
#include "input/Input.hpp"
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
    int score = 0;

    std::vector<PacmanEvent> events;

    void init(const std::string& mapPath);

    void handleInput(InputKey input);
    void update(double dt);
    void render(IRenderer& renderer);

private:
    void movePlayer(int dx, int dy);
};