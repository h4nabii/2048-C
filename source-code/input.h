#pragma once
#include <conio.h>

#define CMD_W 1
#define CMD_A 2
#define CMD_S 3
#define CMD_D 4
#define CMD_Q 0

// wait digit input
int waitDigitKeyDown(int start, int end)
{
	int input;
    while (input = _getch())
    {
		input -= '0';
		if ((start <= input) && (input <= end)) return input;	
    }
    return -1;
}

// wait game command
int waitGameKeyDown()
{
    int input;
    do
    {
        input = _getch();
    } while ((input != 'w') && (input != 's') && (input != 'a') && (input != 'd') && (input != 'q'));

    switch (input)
    {
    case ('w'):
        return CMD_W;
        break;
    case ('s'):
        return CMD_S;
        break;
    case ('a'):
        return CMD_A;
        break;
    case ('d'):
        return CMD_D;
        break;
    case ('q'):
    default:
        return CMD_Q;
    }
}