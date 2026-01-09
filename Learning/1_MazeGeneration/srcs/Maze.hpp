#ifndef MAZE_HPP
#define MAZE_HPP

#include <vector>
#include <array>
#include <cstddef>
#include <cstdint>

enum class Direction : uint8_t {
    North = 1,
    East  = 2,
    South = 4,
    West  = 8
};

struct Cell {
    bool visited = false;
    uint8_t connections = 0;  // bitmask for connections: 1 = North, 2 = East, 4 = South, 8 = West
};

class Maze {
public:
    Maze() = delete;
    Maze(uint8_t width, uint8_t height);
    ~Maze() = default;

    uint8_t width()  const;
    uint8_t height() const;

    Cell& get_cell(uint8_t x, uint8_t y);

    const Cell& get_cell(uint8_t x, uint8_t y) const;

    bool in_bounds(uint8_t x, uint8_t y) const;
    std::vector<Cell> get_maze() const;

private:
    uint8_t m_width;
    uint8_t m_height;
    std::vector<Cell> m_maze;
};

#endif // MAZE_HPP