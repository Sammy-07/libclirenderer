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
Functions that are related to time
*/

//wait with support for a floating point number
void waitFloat(double waitTime) {
    // Define a duration type that uses 'double' for seconds
    using duration_seconds = std::chrono::duration<double>;

    // Now you can pass decimals perfectly!
    std::this_thread::sleep_for(duration_seconds(waitTime));
}