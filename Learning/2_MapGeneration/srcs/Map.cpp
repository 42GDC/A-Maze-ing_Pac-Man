//converts Maze to map
#include <cstdint> 
#include <vector>

enum class Direction : uint8_t {
    None = 0,
    North = 1,
    East  = 2,
    South = 4,
    West  = 8,
    NorthEast = 16,
    SouthEast = 32,
    SouthWest = 64,
    NorthWest = 128
};

struct Cell {
    int     type; // 0 = wall, 1 = path, etc.
    int     item; // 0 = none, 1 = dot, 2 = power pellet, etc.
    uint8_t walls;  // bitmask for walls: 1 = North, 2 = East, 4 = South, 8 = West
};

class Map {
public:
    Map(uint8_t width, uint8_t height)
        : m_width(width), m_height(height),
          m_cells(width * height) {}

    uint8_t width()  const { return m_width; }
    uint8_t height() const { return m_height; }

    Cell& get_cell(uint8_t x, uint8_t y) {
        return m_cells[y * m_width + x];
    }

    const Cell& get_cell(uint8_t x, uint8_t y) const {
        return m_cells[y * m_width + x];
    }

    bool in_bounds(uint8_t x, uint8_t y) const {
        return x < m_width && y < m_height;
    }

private:
    uint8_t m_width;
    uint8_t m_height;
    std::vector<Cell> m_cells;
};