#ifndef SHARED_HPP
#define SHARED_HPP

#include <cstdint>

uint32_t colours[5] = {
    0x333333FF, // EMPTY
    0x007F00FF, // PROCESSING
    0x0000FFFF, // PATH
    0xFFFF0000, // START
    0xFFFFFFFF  // END
};

enum class CellType {
    EMPTY,
    PROCESSING,
    PATH,
    START,
    END
};

enum class ConnectionNumber : uint8_t {
    NONE,
    ONE,
    TWO,
    THREE,
    FOUR
};

enum class Direction : uint8_t {
    North = 1,
    East  = 2,
    South = 4,
    West  = 8
};

#define BLOCKS " ║═╚║║╔╠═╝═╩╗╣╦╬"

struct Cell {
    bool visited = false;
    uint8_t status = 0; // 0 = new, 1 = working, 2 = finished
    uint8_t connectionNumber = 0;
    uint8_t connections = 0;  // bitmask for connections: 1 = North, 2 = East, 4 = South, 8 = West
};

struct Cell {
    CellType type;
    bool visited;
    int x, y;

    Cell(CellType type, int x, int y) : type(type), visited(false), x(x), y(y) {}
};

#endif // SHARED_HPP