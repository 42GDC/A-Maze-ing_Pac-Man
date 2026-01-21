// print based on the state
// print based on number of connections
// move left/right by 1/10/100/1000 iterations
// display which iteration of how many
// display seed
#include <vector>
#include <iostream>
#include "shared.hpp"
// #include "Maze.hpp"


#include <termios.h>
#include <unistd.h>
#include <cstdio>

class RawTerminal {
    termios old_;
public:
    RawTerminal() {
        tcgetattr(STDIN_FILENO, &old_);
        termios raw = old_;
        raw.c_lflag &= ~(ICANON | ECHO);   // disable line buffering & echo
        raw.c_cc[VMIN]  = 1;
        raw.c_cc[VTIME] = 0;
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
        std::cout << ANSII_ENTER_ALTERNATE_SCREEN << std::flush;
    }

    ~RawTerminal() {
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &old_);
        std::cout << ANSII_EXIT_ALTERNATE_SCREEN << std::flush;
    }
};


void    visualise_maze(std::vector<std::vector<Cell>>& maze_history, uint8_t width, uint8_t height)
{
    RawTerminal rt; // Enable raw mode for terminal input
    int n = maze_history.size();
    int i = n - 1;
    if (n == 0) {
        std::cout << "No maze history to display.\n";
        return ;
    }
    while (true) {
        std::cout << ANSI_CLEAR_SCREEN << ANSI_CURSOR_HOME;
        std::cout << "Press 'q' to exit: ";
        if (i < 0) {
            i = 0;
        }
        else if (i >= n) {
            i = n - 1;
        }
        std::cout << "Displaying slice " << i << " of " << (n - 1) << ":\n";
        std::vector<Cell> maze = maze_history[i];
        for (uint8_t y = 0; y < height; ++y) {
            for (uint8_t x = 0; x < width; ++x) {
                if (maze[y * width + x].connectionNumber == static_cast<uint8_t>(ConnectionNumber::NONE)) {
                    std::cout << ANSII_BG_WHITE;
                }
                else if (maze[y * width + x].connectionNumber == static_cast<uint8_t>(ConnectionNumber::ONE)) {
                    std::cout << ANSII_BG_YELLOW;
                }
                else if (maze[y * width + x].connectionNumber == static_cast<uint8_t>(ConnectionNumber::TWO)) {
                    std::cout << ANSII_BG_GREEN;
                }
                else if (maze[y * width + x].connectionNumber == static_cast<uint8_t>(ConnectionNumber::THREE)) {
                    std::cout << ANSII_BG_CYAN;
                }
                else if (maze[y * width + x].connectionNumber == static_cast<uint8_t>(ConnectionNumber::FOUR)) {
                    std::cout << ANSII_BG_RED;
                }
                if (maze[y * width + x].visited) {
                    std::cout << ANSII_BOLD ANSII_WHITE;
                }
                else {
                    std::cout << ANSII_BLACK;
                }
                std::cout << BLOCKS4[maze[y * width + x].connections];
                std::cout << ANSII_RESET;
            }
            std::cout << std::endl;
        }
        char c;
        int r = read(STDIN_FILENO, &c, 1);
        if (r < 0) {
            perror("read");
            break;
        }
        if (c == 'q')
            break;
        else if (c == 'a')
            i -= 1000;
        else if (c == 's')
            i -= 100;
        else if (c == 'd')
            i -= 10;
        else if (c == 'f')
            i -= 1;
        else if (c == 'j')
            i += 1;
        else if (c == 'k')
            i += 10;
        else if (c == 'l')
            i += 100;
        else if (c == ';')
            i += 1000;
    }
}

// count cell directions
// display counts
// compare different maze generation algorithms


void    visualise_maze2(std::vector<Maze>& maze_history)
{
    RawTerminal rt; // Enable raw mode for terminal input
    int connectionNumber[5] = {0, 0, 0, 0, 0};
    int n = maze_history.size();
    int i = n - 1;
    if (n == 0) {
        std::cout << "No maze history to display.\n";
        return ;
    }
    while (true) {
        for (int j = 0; j < 5; ++j) {
            connectionNumber[j] = 0;
        }
        std::cout << ANSI_CLEAR_SCREEN << ANSI_CURSOR_HOME;
        std::cout << "Press 'Q' to exit: ";
        if (i < 0) {
            i = 0;
        }
        else if (i >= n) {
            i = n - 1;
        }
        uint16_t width = maze_history[i].get_width();
        uint16_t height = maze_history[i].get_height();
        std::cout << "Displaying slice " << i << " of " << (n - 1) << ":\n";
        Maze maze = maze_history[i];
        for (uint8_t y = 0; y < height; ++y) {
            for (uint8_t x = 0; x < width; ++x) {
                Cell cell = maze.get_cell(x, y);
                if (cell.connectionNumber == static_cast<uint8_t>(ConnectionNumber::NONE)) {
                    connectionNumber[0]++;
                    std::cout << ANSII_BG_WHITE;
                }
                else if (cell.connectionNumber == static_cast<uint8_t>(ConnectionNumber::ONE)) {
                    connectionNumber[1]++;
                    std::cout << ANSII_BG_YELLOW;
                }
                else if (cell.connectionNumber == static_cast<uint8_t>(ConnectionNumber::TWO)) {
                    connectionNumber[2]++;
                    std::cout << ANSII_BG_GREEN;
                }
                else if (cell.connectionNumber == static_cast<uint8_t>(ConnectionNumber::THREE)) {
                    connectionNumber[3]++;
                    std::cout << ANSII_BG_CYAN;
                }
                else if (cell.connectionNumber == static_cast<uint8_t>(ConnectionNumber::FOUR)) {
                    connectionNumber[4]++;
                    std::cout << ANSII_BG_RED;
                }
                if (cell.visited) {
                    std::cout << ANSII_BOLD ANSII_WHITE;
                }
                else {
                    std::cout << ANSII_BLACK;
                }
                std::cout << BLOCKS4[maze.get_cell(x, y).connections];
                std::cout << ANSII_RESET;
            }
            std::cout << std::endl;
        }
        std::cout << "Connection numbers: ";
        for (int j = 0; j < 5; ++j) {
            std::cout << j << ": " << connectionNumber[j];
            if (j < 4)
                std::cout << ", ";
        }
        std::cout << std::endl;
        char c;
        int r = read(STDIN_FILENO, &c, 1);
        if (r < 0) {
            perror("read");
            break;
        }
        if (c == 'q')
            break;
        else if (c == 'a')
            i -= 1000;
        else if (c == 's')
            i -= 100;
        else if (c == 'd')
            i -= 10;
        else if (c == 'f')
            i -= 1;
        else if (c == 'j')
            i += 1;
        else if (c == 'k')
            i += 10;
        else if (c == 'l')
            i += 100;
        else if (c == ';')
            i += 1000;
    }
}