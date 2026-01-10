// print based on the state
// print based on number of connections
// move left/right by 1/10/100/1000 iterations
// display which iteration of how many
// display seed
#include <vector>
#include <iostream>
#include "shared.hpp"
#include "Maze.hpp"
void    visualise_maze(std::vector<std::vector<Cell>>& maze_history, uint8_t width, uint8_t height)
{
    
    std::vector<Cell> maze = maze_history.back();
    for (uint8_t y = 0; y < height; ++y)
    {
        for (uint8_t x = 0; x < width; ++x)
        {
            
            std::cout << BLOCKS2[maze[y * width + x].connections];
        }
        std::cout << std::endl;
    }
}