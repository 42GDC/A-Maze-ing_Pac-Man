#include <vector>
#include <array>
#include <cstddef>
#include <cstdint>
#include <random>
#include <iostream>
#include "Maze.hpp" 



Maze::Maze(uint8_t width, uint8_t height, uint32_t seed) {
    m_width = width;
    m_height = height;
    m_seed = seed; // set seed separately
    m_maze.resize(width * height);
    m_maze_history.push_back(m_maze);
}

uint8_t Maze::width()  const { return m_width; }
uint8_t Maze::height() const { return m_height; }
uint32_t Maze::seed() const { return m_seed; }

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

std::vector<std::vector<Cell>> Maze::share_history() const {
    return m_maze_history;
}

void Maze::generate_maze() {
    // hunt and kill algorithm implementation
    // walk phase
    // hunt phase
    // at each step, update m_maze_history  
    int todo = m_height * m_width;
    // ... maze generation logic here ...
    // After each significant step in the algorithm, store the current maze state
    int y = m_seed % m_height;
    int x = m_seed % m_width;
    std::mt19937 rng(m_seed);
    std::uniform_int_distribution<uint32_t> dist(0, 3);
    while (todo > 0) {
        int walking = 1;
        //walk
        std::cout << "Walking from (" << x << ", " << y << ") todos: " << todo << "\n";
        while (walking) {
            std::cout << "At (" << x << ", " << y << ")\n";
            // if (!m_maze[y * m_width + x].visited)
            //     todo--;
            m_maze[y * m_width + x].visited = true;
            Directions r = static_cast<Directions>(dist(rng));
            std::cout << "Trying direction " << (int)r << "\n";
            if (r == Directions::NORTH) { // North
                if (y > 0 && !m_maze[(y - 1) * m_width + x].visited) {
                    std::cout << "Moving North\n";
                    m_maze[y * m_width + x].connections |= 1; // North
                    m_maze[(y - 1) * m_width + x].connections |= 4; // South
                    y--;
                    m_maze_history.push_back(m_maze);
                }
            }
            else if (r == Directions::EAST ) { // East
                if (x < m_width - 1 && !m_maze[y * m_width + (x + 1)].visited) {
                    std::cout << "Moving East\n";
                    m_maze[y * m_width + x].connections |= 2; // East
                    m_maze[y * m_width + (x + 1)].connections |= 8; // West
                    x++;
                    m_maze_history.push_back(m_maze);
                }
            }
            else if (r == Directions::SOUTH) { // South
                if (y < m_height - 1 && !m_maze[(y + 1) * m_width + x].visited) {
                    std::cout << "Moving South\n";
                    m_maze[y * m_width + x].connections |= 4; // South
                    m_maze[(y + 1) * m_width + x].connections |= 1; // North
                    y++;
                    m_maze_history.push_back(m_maze);
                }
            }
            else if (r == Directions::WEST) { // West
                if (x > 0 && !m_maze[y * m_width + (x - 1)].visited) {
                    std::cout << "Moving West\n";
                    m_maze[y * m_width + x].connections |= 8; // West
                    m_maze[y * m_width + (x - 1)].connections |= 2; // East
                    x--;
                    m_maze_history.push_back(m_maze);
                }
            }
            if (// no unvisited neighbors
                (y == 0 || m_maze[(y - 1) * m_width + x].visited) &&
                (x == m_width - 1 || m_maze[y * m_width + (x + 1)].visited) &&
                (y == m_height - 1 || m_maze[(y + 1) * m_width + x].visited) &&
                (x == 0 || m_maze[y * m_width + (x - 1)].visited)
            )
            {
                m_maze[y * m_width + x].visited = true;
                walking = 0;
                //todo--;
                std::cout << "No unvisited neighbors, stopping walk.\n";
            }
        }
        int hunting = 1;
        //hunt
        while (hunting) {
            std::cout << "Hunting...\n";
            bool found = false;
            for (uint8_t yy = 0U; !found && yy < m_height; ++yy) {
                for (uint8_t xx = 0U; !found && xx < m_width; ++xx) {
                    if (!m_maze[yy * m_width + xx].visited) { // unvisited cell found
                        // check for visited neighbors
                        if (yy > 0 && m_maze[(yy - 1) * m_width + xx].visited) { // North
                            m_maze[yy * m_width + xx].connections |= 1; // North
                            m_maze[(yy - 1) * m_width + xx].connections |= 4; // South
                            found = true;  
                        }
                        else if (xx < m_width - 1 && m_maze[yy * m_width + (xx + 1)].visited) { // East
                            m_maze[yy * m_width + xx].connections |= 2; // East
                            m_maze[yy * m_width + (xx + 1)].connections |= 8; // West
                            found = true;
                        }
                        else if (yy < m_height - 1 && m_maze[(yy + 1) * m_width + xx].visited) { // South
                            m_maze[yy * m_width + xx].connections |= 4; // South
                            m_maze[(yy + 1) * m_width + xx].connections |= 1; // North
                            found = true;
                        }
                        else if (xx > 0 && m_maze[yy * m_width + (xx - 1)].visited) { // West
                            m_maze[yy * m_width + xx].connections |= 8; // West
                            m_maze[yy * m_width + (xx - 1)].connections |= 2; // East
                            found = true;
                        }
                        if (found) {
                            std::cout << "Found new starting point at (" << (int)xx << ", " << (int)yy << ")\n";
                            // move to that cell
                            y = yy;
                            x = xx;
                        }
                    }
                }
            }
            hunting = 0;
            if (!found) {
               todo = 0; // no unvisited cells found, maze generation complete
            }
        }
        m_maze_history.push_back(m_maze);
    }
    // Final state

    m_maze_history.push_back(m_maze);
}
