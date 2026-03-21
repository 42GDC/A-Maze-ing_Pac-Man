#pragma once

#include <cstdint>

enum class Event : std::uint8_t
{
    None = 0,
    Move,
    PelletEaten,
    PowerPelletEaten,
    Win,
    Death,
    Lose
};
