/*
    GAME2048
    version 4
    2048.cpp
*/

#include <time.h>
#include <direct.h>

#include "public/screen.h"
#include "public/data.h"

#include "main.h"

// Initial the program
void init()
{
    // Set the random seed and initialize the screen and file system
    srand((unsigned int)time(NULL));
    screenInit();
    fileInit();
}

int main()
{
    init();
    runHome();
    return 0;
}
