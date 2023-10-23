#pragma once
#include <conio.h>

// get digit input
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