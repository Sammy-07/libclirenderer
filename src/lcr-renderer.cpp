#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <thread>
#include <chrono>

#ifdef _WIN32
#include <windows.h>
#endif

//Main h file
#include "../include/libclirenderer/libclirenderer.h"

void winAnsiInit(bool winAnsiEnable){

    #ifdef _WIN32
    // Set console code page to UTF-8 so box-drawing characters render correctly
    //system("chcp 65001 > nul");

    // Get the standard output handle for Windows
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole != INVALID_HANDLE_VALUE) {
        DWORD mode = 0;
        GetConsoleMode(hConsole, &mode);
        
        if (winAnsiEnable) {
            // Enable ANSI escape code processing
            SetConsoleMode(hConsole, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
        } else {
            // Disable ANSI escape code processing
            SetConsoleMode(hConsole, mode & ~ENABLE_VIRTUAL_TERMINAL_PROCESSING);
        }
    }
    #endif
}

//Clear the terminal using ANSI codes
void clearScreen() {
    winAnsiInit(true);
    // \033[H   -> Moves cursor to top-left
    // \033[2J  -> Clears visible viewport
    // \033[3J  -> Wipes out scrollback history
    std::cout << "\033[H\033[2J\033[3J" << std::flush;
    winAnsiInit(false);
}

//wait with support for a floating point number
void waitFloat(double waitTime) {
    // Define a duration type that uses 'double' for seconds
    using duration_seconds = std::chrono::duration<double>;

    // Now you can pass decimals perfectly!
    std::this_thread::sleep_for(duration_seconds(waitTime));
}


//Render a square based on parameters
void renderSquare(int width, int height) {
    int lineHeightCounterStorage = height;
    int lineWidthCounterStorage = width;

    #if defined(__APPLE__) || defined(__linux__)
    std::cout << "┌" << std::flush;
    #endif
    
    #ifdef _WIN32
    std::cout << "+" << std::flush;
    #endif

    while (width > 2) {

        #if defined(__APPLE__) || defined(__linux__)
        std::cout << "─" << std::flush;
        #endif

        #ifdef _WIN32
        std::cout << "-" << std::flush;
        #endif

        width = width - 1;
    }

    #if defined(__APPLE__) || defined(__linux__)
    std::cout << "┐" << std::flush;
    #endif
    
    #ifdef _WIN32
    std::cout << "+" << std::flush;
    #endif
    
    width = lineWidthCounterStorage;
    std::cout << "\n" << std::flush;

    while (height > 2) {

        #if defined(__APPLE__) || defined(__linux__)
        std::cout << "│" << std::flush;
        #endif

        #ifdef _WIN32
        std::cout << "|" << std::flush;
        #endif

        while (width > 2) {
            std::cout << " " << std::flush;
            width = width - 1;
        }
        width = lineWidthCounterStorage;

        #if defined(__APPLE__) || defined(__linux__)
        std::cout << "│" << std::flush;
        #endif

        #ifdef _WIN32
        std::cout << "|" << std::flush;
        #endif

        std::cout << "\n" << std::flush;
        height = height - 1;
    }
    height = lineHeightCounterStorage;

    #if defined(__APPLE__) || defined(__linux__)
    std::cout << "└" << std::flush;
    #endif

    #ifdef _WIN32
    std::cout << "+" << std::flush;
    #endif

    while (width > 2) {

        #if defined(__APPLE__) || defined(__linux__)
        std::cout << "─" << std::flush;
        #endif

        #ifdef _WIN32
        std::cout << "-" << std::flush;
        #endif
        width = width - 1;
    }

    #if defined(__APPLE__) || defined(__linux__)
    std::cout << "┘" << std::flush;
    #endif

    #ifdef _WIN32
    std::cout << "+" << std::flush;
    #endif

    
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
