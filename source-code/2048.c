/*
    GAME2048
    version 4
    2048.cpp
*/

#include <time.h>
#include <direct.h>

#include "input.h"
#include "screen.h"

#include "ScoSavLoad.h"
#include "GamePart.h"
#include "Setting.h"
#include "MainPart.h"


// Initial the program
void init()
{
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
