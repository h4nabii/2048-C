/*
    GAME2048
    version 4
    MainPart.h
*/

#include "public/global.h"

#include "public/screen.h"
#include "public/input.h"

#include "game.h"
#include "menu.h"

#define QUIT 0

#define MAIN_GAME 1
#define MAIN_MENU 2


void runHome()
{
    int command;

    int stillPlay;

    do
    {
        showHome();
        command = waitDigitKeyDown(0, 2);

        if (command == MAIN_GAME)
        {
            do
            {
                game2048();
                showGameOver();
                stillPlay = waitDigitKeyDown(0, 1);
            } while (stillPlay);
        }
        else if (command == MAIN_MENU)
        {
            runMenu();
        }
    } while (command);
}
