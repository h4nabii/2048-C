/*
	GAME2048
	version 4
	2048.cpp
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <direct.h>
#include <math.h>
#include <windows.h>

#include "MainPart.h"
#include "ScoSavLoad.h"
#include "GamePart.h"
#include "Setting.h"

int main()
{
	int mainChoice;
	int menuChoice;
	int settingChoice;
	int ifTestModel = 0;
	int * score;
	int scoreNumber = 0;
	int stillPlay;

	score = &scoreNumber;
	srand((unsigned int)time(NULL));

	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	system("mode con cols=45 lines=25"); 
	SetConsoleTitleA("2048"); 
	SetConsoleTextAttribute(hOut,
		BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY); 
	system("cls"); 
	FILE * file;
	errno_t fileErr;
	errno_t err;
	fileErr = fopen_s(&file, "TEST\\HaveDone.txt", "r");
	if (fileErr != 0)
	{
		_mkdir("TEST");
		err = fopen_s(&file, "TEST\\HaveDone.txt", "w");
		fprintf(file, "HavePrepared\n");
		fclose(file);
		addFileAddress();
	}
	do
	{
		printGreeting(ifTestModel);
		mainChoice = getNumberChoice(0, 2);
		switch (mainChoice)
		{
		case(1):													//游戏
			do
			{
				game2048(score, ifTestModel);
				printEnd();
				stillPlay = getNumberChoice(0, 1);
			}
			while (stillPlay == 1);
			break;
		case(2):													//主页
			do
			{
				menuGreeting();
				menuChoice = getNumberChoice(0, 2);
				if (menuChoice == 0)
				{
					stillPlay = 0;
				}
				else if (menuChoice == 1)
				{
					loadScore();
					stillPlay = 1;
				}
				else if (menuChoice == 2)
				{
					do
					{
						settingGreeting();
						settingChoice = getNumberChoice(0, 1);
						if (settingChoice == 1)
							ifTestModel = toMakeSureColorTest();
					}
					while (settingChoice != 0);
					stillPlay = 1;
				}
			}
			while (stillPlay == 1);
		}
	}
	while (mainChoice != 0);
	return 0;
}
