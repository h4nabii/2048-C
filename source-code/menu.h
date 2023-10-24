#include "public/input.h"
#include "public/screen.h"

#include "public/screen.h"
#include "public/input.h"
#include "public/data.h"

#include "settings.h"

#define MENU_LOAD       1
#define MENU_SETTING    2

void runMenu()
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
            runSetting();
        }
    } while (menuChoice);
}