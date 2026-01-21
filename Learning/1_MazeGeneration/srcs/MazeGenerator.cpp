#include <vector>
#include <array>
#include <cstddef>
#include <cstdint>
#include <random>
#include <iostream>
#include "MazeGenerator.hpp" 



MazeGenerator::MazeGenerator(uint8_t width, uint8_t height, uint32_t seed) : m_maze2(width, height) {
    m_width = width;
    m_height = height;
    m_seed = seed; // set seed separately
    m_maze.resize(width * height);
    m_maze_history.push_back(m_maze);
    m_maze2_history.push_back(m_maze2);
}

uint8_t MazeGenerator::width()  const { return m_width; }
uint8_t MazeGenerator::height() const { return m_height; }
uint32_t MazeGenerator::seed() const { return m_seed; }

Cell& MazeGenerator::get_cell(uint8_t x, uint8_t y) {
    return m_maze[y * m_width + x];
}

const Cell& MazeGenerator::get_cell(uint8_t x, uint8_t y) const {
    return m_maze[y * m_width + x];
}

bool MazeGenerator::in_bounds(uint8_t x, uint8_t y) const {
    return x < m_width && y < m_height;
}

std::vector<Cell> MazeGenerator::get_maze() const {
    return m_maze;
}

std::vector<std::vector<Cell>> MazeGenerator::share_history() const {
    return m_maze_history;
}

std::vector<Maze> MazeGenerator::share_maze2_history() const {
    return m_maze2_history;
}

void MazeGenerator::generate_maze() {
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
        if (DEBUG) {
            std::cout << "Walking from (" << x << ", " << y << ") todos: " << todo << "\n";
        }
        while (walking) {
            if (DEBUG) {
                std::cout << "At (" << x << ", " << y << ")\n";
            }
            // if (!m_maze[y * m_width + x].visited)
            //     todo--;
            m_maze[y * m_width + x].visited = true;
            m_maze2.get_cell(x, y).visited = true;
            Directions r = static_cast<Directions>(dist(rng));
            if (DEBUG) {
                std::cout << "Trying direction " << (int)r << "\n";
            }
            // OPTIMISATION1: ABSTRACT JOINING NEIGHBOURS TO A FUNCTION
            // OPTIMISATION2: CHECK NUMBER OF NEIGHBOURS AND RANDOMLY JOIN ONE OF THEM
            if (r == Directions::NORTH) { // North
                if (y > 0 && !m_maze[(y - 1) * m_width + x].visited) { // 
                    if (DEBUG) {
                        std::cout << "Moving North\n";
                    }
                    m_maze[y * m_width + x].connections |= 1; // North
                    m_maze[(y - 1) * m_width + x].connections |= 4; // South
                    m_maze[y * m_width + x].connectionNumber += 1; // North
                    m_maze[(y - 1) * m_width + x].connectionNumber += 1; // South
                    m_maze2.connectNorth(x, y);
                    y--;
                    m_maze_history.push_back(m_maze);
                    m_maze2_history.push_back(m_maze2);
                }
            }
            else if (r == Directions::EAST ) { // East
                if (x < m_width - 1 && !m_maze[y * m_width + (x + 1)].visited) {
                    if (DEBUG) {
                        std::cout << "Moving East\n";
                    }
                    m_maze[y * m_width + x].connections |= 2; // East
                    m_maze[y * m_width + (x + 1)].connections |= 8; // West
                    m_maze[y * m_width + x].connectionNumber += 1; // East
                    m_maze[y * m_width + (x + 1)].connectionNumber += 1; // West    
                    m_maze2.connectEast(x, y);
                    x++;
                    m_maze_history.push_back(m_maze);
                    m_maze2_history.push_back(m_maze2);
                }
            }
            else if (r == Directions::SOUTH) { // South
                if (y < m_height - 1 && !m_maze[(y + 1) * m_width + x].visited) {
                    if (DEBUG) {
                        std::cout << "Moving South\n";
                    }
                    m_maze[y * m_width + x].connections |= 4; // South
                    m_maze[(y + 1) * m_width + x].connections |= 1; // North
                    m_maze[y * m_width + x].connectionNumber += 1; // South
                    m_maze[(y + 1) * m_width + x].connectionNumber += 1; // North
                    m_maze2.connectSouth(x, y);
                    y++;
                    m_maze_history.push_back(m_maze);
                    m_maze2_history.push_back(m_maze2);
                }
            }
            else if (r == Directions::WEST) { // West
                if (x > 0 && !m_maze[y * m_width + (x - 1)].visited) {
                    if (DEBUG) {
                        std::cout << "Moving West\n";
                    }
                    m_maze[y * m_width + x].connections |= 8; // West
                    m_maze[y * m_width + (x - 1)].connections |= 2; // East
                    m_maze[y * m_width + x].connectionNumber += 1; // West
                    m_maze[y * m_width + (x - 1)].connectionNumber += 1; // East
                    m_maze2.connectWest(x, y);
                    x--;
                    m_maze_history.push_back(m_maze);
                    m_maze2_history.push_back(m_maze2);
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
                m_maze2.get_cell(x, y).visited = true;
                walking = 0;
                //todo--;
                if (DEBUG) {
                    std::cout << "No unvisited neighbors, stopping walk.\n";
                }
            }
        }
        int hunting = 1;
        //hunt
        while (hunting) {
            if (DEBUG) {
                std::cout << "Hunting...\n";
            }
            bool found = false;
            // could use just one loop since maze is stored linearly
            for (uint8_t yy = 0U; !found && yy < m_height; ++yy) {
                for (uint8_t xx = 0U; !found && xx < m_width; ++xx) {
                    if (!m_maze[yy * m_width + xx].visited) { // unvisited cell found
                        // check for visited neighbors
                        // SHOULD JOIN RANDOMLY ANY NEIGHBOUR THAT IS VISITED
                        if (yy > 0 && m_maze[(yy - 1) * m_width + xx].visited) { // North
                            m_maze[yy * m_width + xx].connections |= 1; // North
                            m_maze[(yy - 1) * m_width + xx].connections |= 4; // South
                            m_maze[yy * m_width + xx].connectionNumber += 1; // North
                            m_maze[(yy - 1) * m_width + xx].connectionNumber += 1; // South
                            m_maze2.connectNorth(xx, yy);
                            found = true;  
                        }
                        else if (xx < m_width - 1 && m_maze[yy * m_width + (xx + 1)].visited) { // East
                            m_maze[yy * m_width + xx].connections |= 2; // East
                            m_maze[yy * m_width + (xx + 1)].connections |= 8; // West
                            m_maze[yy * m_width + xx].connectionNumber += 1; // East
                            m_maze[yy * m_width + (xx + 1)].connectionNumber += 1; // West
                            m_maze2.connectEast(xx, yy);
                            found = true;
                        }
                        else if (yy < m_height - 1 && m_maze[(yy + 1) * m_width + xx].visited) { // South
                            m_maze[yy * m_width + xx].connections |= 4; // South
                            m_maze[(yy + 1) * m_width + xx].connections |= 1; // North
                            m_maze[yy * m_width + xx].connectionNumber += 1; // South
                            m_maze[(yy + 1) * m_width + xx].connectionNumber += 1; // North
                            m_maze2.connectSouth(xx, yy);
                            found = true;
                        }
                        else if (xx > 0 && m_maze[yy * m_width + (xx - 1)].visited) { // West
                            m_maze[yy * m_width + xx].connections |= 8; // West
                            m_maze[yy * m_width + (xx - 1)].connections |= 2; // East
                            m_maze[yy * m_width + xx].connectionNumber += 1; // West
                            m_maze[yy * m_width + (xx - 1)].connectionNumber += 1; // East
                            m_maze2.connectWest(xx, yy);
                            found = true;
                        }
                        if (found) {
                            if (DEBUG) {
                                std::cout << "Found new starting point at (" << (int)xx << ", " << (int)yy << ")\n";
                            }
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
        m_maze2_history.push_back(m_maze2);
    }
    // Final state
    m_maze_history.push_back(m_maze);
    m_maze2_history.push_back(m_maze2);
}
