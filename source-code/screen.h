#pragma once
#include <windows.h>
#include <stdio.h>

// initial screen
void screenInit() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    // Set window size (useless when using Windows Terminal)
    system("mode con cols=45 lines=25");
    
    SetConsoleTitleA("2048");
    
    SetConsoleTextAttribute(
        hOut,
        BACKGROUND_BLUE |
            BACKGROUND_GREEN |
            BACKGROUND_RED |
            BACKGROUND_INTENSITY);
    
    system("cls");
}

// show greeting screen
void showHome(int ifColorTest)
{
	system("cls");
	printf("                                          \n");
	printf("|****************************************|\n");
	printf("|                                        |\n");
	printf("|                                        |\n");
	printf("|               游戏：2048               |\n");
	printf("|                                        |\n");

	printf(ifColorTest == 1 ? "|         1：开始(颜色测试模式)          |\n" : "|                1：开始                 |\n");

	printf("|                                        |\n");
	printf("|                2：菜单                 |\n");
	printf("|                                        |\n");
	printf("|                0：退出                 |\n");
	printf("|                                        |\n");
	printf("|                                        |\n");
	printf("|                                        |\n");
	printf("|                                        |\n");
	printf("|                                        |\n");
	printf("|                                        |\n");
	printf("|                                        |\n");
	printf("|                                        |\n");
	printf("|                                        |\n");
	printf("|                                        |\n");
	printf("|****************************************|\n\n");
}

// show menu screen
void showMenu()
{
	system("cls");
	printf("                                          \n");
	printf("|****************************************|\n");
	printf("|                                        |\n");
	printf("|                                        |\n");
	printf("|               游戏：2048               |\n");
	printf("|                                        |\n");
	printf("|               1：分数记录              |\n");
	printf("|                                        |\n");
	printf("|               2：设置                  |\n");
	printf("|                                        |\n");
	printf("|               0：退出                  |\n");
	printf("|                                        |\n");
	printf("|                                        |\n");
	printf("|                                        |\n");
	printf("|                                        |\n");
	printf("|                                        |\n");
	printf("|                                        |\n");
	printf("|                                        |\n");
	printf("|                                        |\n");
	printf("|                                        |\n");
	printf("|                                        |\n");
	printf("|****************************************|\n\n");
}