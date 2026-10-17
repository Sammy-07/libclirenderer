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


/*
Functions that are related to drawing premade objects
into terminal
*/

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

//Loading wheel spawned at location
void loadingWheelAt(int x, int y, int cycles) {
    int addyOneOld = 0;
    int addxOneOld = 0;
    while (cycles > 0) {
        showCursor(false);
        auto printLoadingSectionAtOffsetAdd = [&](int addx, int addy) {
            offsetCursorAnsi((x + addx), (y + addy));
            std::cout << "o" << std::flush;
            waitFloat(0.1);
            offsetCursorAnsi((x + addxOneOld), (y + addyOneOld));
            std::cout << " " << std::flush;
            addxOneOld = addx;
            addyOneOld = addy;
        };

        printLoadingSectionAtOffsetAdd(1, 0);
        printLoadingSectionAtOffsetAdd(2, 0);
        printLoadingSectionAtOffsetAdd(3, 0);
        printLoadingSectionAtOffsetAdd(4, 1);
        printLoadingSectionAtOffsetAdd(4, 2);
        printLoadingSectionAtOffsetAdd(3, 3);
        printLoadingSectionAtOffsetAdd(2, 3);
        printLoadingSectionAtOffsetAdd(1, 3);
        printLoadingSectionAtOffsetAdd(0, 2);
        printLoadingSectionAtOffsetAdd(0, 1);

        cycles = cycles - 1;
    }

    offsetCursor(x, (y + 1));
    std::cout << " " << std::flush;

    showCursor(true);
}
