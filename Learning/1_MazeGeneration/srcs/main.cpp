#include <cstdint>
#include <iostream>
#include "shared.hpp"
#include "Maze.hpp"

void    visualise_maze(std::vector<std::vector<Cell>>& maze_history, uint8_t width, uint8_t height);

int	main(void)
{
	uint8_t		height;
	uint8_t		width;
	uint32_t	seed;
	int			temp;

	std::cout << "Input width: ";
	std::cin >> temp;
	width = static_cast<uint8_t>(temp);
	std::cout << "Input height: ";
	std::cin >> temp;
	height = static_cast<uint8_t>(temp);
	std::cout << "Input seed: ";
	std::cin >> seed;
	// std::cout << std::endl;
	std::cout << "Generating maze of size " << (int)width << "x" << (int)height << " with seed " << seed << std::endl;

	Maze		maze(width, height, seed);

	maze.generate_maze();
	std::vector<std::vector<Cell>> maze_history = maze.share_history();
	visualise_maze(maze_history, width, height);
	// generate maze
	// remove dead ends
	// increase connectivity (add loops)
	// decrease connectivity (remove loops)
	// double and flip horizontally/vertically

	// convert maze to map
	// add ghost area
	// add portals
	return (0);
}