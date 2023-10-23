/*
    GAME2048
    version 4
    MainPart.h
*/

#include "screen.h"
#include "input.h"

#define QUIT 0

#define MAIN_GAME 1
#define MAIN_MENU 2

#define MENU_LOAD       1
#define MENU_SETTING    2

void runHome()
{
    int command;

    int score = 0;

    int isTest = 0;
    int stillPlay;

    do
    {
        showHome(isTest);
        command = waitDigitKeyDown(0, 2);

        if (command == MAIN_GAME)
        {
            do
            {
                game2048(&score, isTest);
                printEnd();
                stillPlay = waitDigitKeyDown(0, 1);
            } while (stillPlay);
        }
        else if (command == MAIN_MENU)
        {
            int menuChoice;
            do
            {
                showMenu();
                menuChoice = waitDigitKeyDown(0, 2);

                if (menuChoice == MENU_LOAD)
                {
                    loadScore();
                }
                else if (menuChoice == MENU_SETTING)
                {
                    int settingChoice;
                    do
                    {
                        settingGreeting();
                        settingChoice = waitDigitKeyDown(0, 1);
                        if (settingChoice == 1)
                            isTest = toMakeSureColorTest();
                    } while (settingChoice);
                }
            } while (menuChoice);
        }
    } while (command);
}
