#include <vector>
#include <array>
#include <cstddef>

enum class Direction : std::size_t {
    North = 0,
    East  = 1,
    South = 2,
    West  = 3
};

struct Cell {
    bool visited = false;
    std::array<bool, 4> connected = { false, false, false, false };
};

class Maze {
public:
    Maze(std::size_t width, std::size_t height)
        : m_width(width), m_height(height),
          m_cells(width * height) {}

    std::size_t width()  const { return m_width; }
    std::size_t height() const { return m_height; }

    Cell& get_cell(std::size_t x, std::size_t y) {
        return m_cells[y * m_width + x];
    }

    const Cell& get_cell(std::size_t x, std::size_t y) const {
        return m_cells[y * m_width + x];
    }

    bool in_bounds(std::size_t x, std::size_t y) const {
        return x < m_width && y < m_height;
    }

private:
    std::size_t m_width;
    std::size_t m_height;
    std::vector<Cell> m_cells;
};
