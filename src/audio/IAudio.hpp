#pragma once

#include "games/pacman/PacmanEvent.hpp"
#include <string>

class IAudio {
public:
    virtual ~IAudio() = default;

    virtual void playEvent(PacmanEvent event) = 0;

    virtual void playMusic(const std::string& path, bool loop) = 0;
    virtual void stopMusic() = 0;
};
