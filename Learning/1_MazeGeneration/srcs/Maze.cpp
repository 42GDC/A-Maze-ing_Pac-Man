#include <vector>
#include <array>
#include <cstddef>
#include <cstdint> 
#include <Maze.hpp> 

enum class Direction : uint8_t {
    North = 1,
    East  = 2,
    South = 4,
    West  = 8
};

struct Cell {
    bool visited = false;
    int status = 0; // 0 = new, 1 = working, 2 = finished
    uint8_t connections = 0;  // bitmask for connections: 1 = North, 2 = East, 4 = South, 8 = West
};

Maze::Maze(uint8_t width, uint8_t height)
        : m_width(width), m_height(height),
          m_maze(width * height) {}

uint8_t Maze::width()  const { return m_width; }
uint8_t Maze::height() const { return m_height; }

Cell& Maze::get_cell(uint8_t x, uint8_t y) {
    return m_maze[y * m_width + x];
}

const Cell& Maze::get_cell(uint8_t x, uint8_t y) const {
    return m_maze[y * m_width + x];
}

bool Maze::in_bounds(uint8_t x, uint8_t y) const {
    return x < m_width && y < m_height;
}

std::vector<Cell> Maze::get_maze() const {
    return m_maze;
}


