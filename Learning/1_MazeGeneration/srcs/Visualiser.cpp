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
    while (true)
    {
        int n = maze_history.size();
        std::cout << "Maze slices: " << n << "\nEnter slice number (0 to " << (n - 1) << ") or -1 to exit: ";
        int temp;
        if (!(std::cin >> temp)) {  // input validation
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number.\n";
            continue ;
        }
        if (temp == -1)
            break ;
        if (temp < 0 || temp >= n)
        {
            std::cout << "Invalid slice number.\n";
            continue ;
        }
        std::vector<Cell> maze = maze_history[temp];
        for (uint8_t y = 0; y < height; ++y)
        {
            for (uint8_t x = 0; x < width; ++x)
            {
                std::cout << BLOCKS4[maze[y * width + x].connections];
            }
            std::cout << std::endl;
        }
    }
}