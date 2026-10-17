#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>

//Main h file
#include "../include/libclirenderer/libclirenderer.h"


/*
Functions that are tool used to assist with drawing in the
terminal Window
*/


//Clear the terminal using ANSI codes
void clearScreen() {
    winAnsiInit(true);
    // \033[H   -> Moves cursor to top-left
    // \033[2J  -> Clears visible viewport
    // \033[3J  -> Wipes out scrollback history
    std::cout << "\033[H\033[2J\033[3J" << std::flush;
    winAnsiInit(false);
}

//Offset terminal text cursor
void offsetCursor(int x, int y) {
    while (y > 0) {
        std::cout << "\n";
        y = y - 1;
    }
    while (x > 0) {
        std::cout << " ";
        x = x - 1;
    }
}

//Offset the terminal cursor using ANSI codes
void offsetCursorAnsi(int x, int y) {
    winAnsiInit(true);
    // ANSI escape code to move cursor to row (y + 1) and column (x + 1)
    std::cout << "\033[" << (y + 1) << ";" << (x + 1) << "H" << std::flush;
    winAnsiInit(false);
}

//hide or show the terminal cursor based on a bool input
void showCursor(bool cursorState) {
    winAnsiInit(true);
    if (cursorState == true) {
        std::cout << "\033[?25h" << std::flush;
    } else if (cursorState == false) {
        std::cout << "\033[?25l" << std::flush;
    }
    winAnsiInit(false);
}