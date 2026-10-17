#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>

//Main h file
#include "../include/libclirenderer/libclirenderer.h"


/*
Functions that do what they do by running commands
in terminal or cmd
*/


//Clears the Terminal Screen Functions across operating systems
void clearScreenSys() {
    
    #ifdef _WIN32
        std::system("cls");
    #endif

    #ifdef __linux__
        std::system("clear");
    #endif

    #ifdef __APPLE__
        std::system("clear");
    #endif


}