#pragma once
#include <windows.h>
#include <stdio.h>
#include <math.h>

#include "global.h"

#define DEFAULT_COLOR (BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY)

void showHome();
void showMenu();
void showGameOver();
void showQuitCheck();

void screenInit();
WORD getColorOf(int number);
void printBlocks(int numbers[][4], int score, int highestScore);

// initial screen
void screenInit()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    // Set window size (useless when using Windows Terminal)
    system("mode con cols=45 lines=25");

    SetConsoleTitleA("2048");

    SetConsoleTextAttribute(hOut, DEFAULT_COLOR);

    system("cls");
}

// show greeting screen
void showHome()
{
    system("cls");
    printf("                                          \n");
    printf("|****************************************|\n");
    printf("|                                        |\n");
    printf("|                                        |\n");
    printf("|               游戏：2048               |\n");
    printf("|                                        |\n");

    printf(testMode == 1 ? "|         1：开始(颜色测试模式)          |\n" : "|                1：开始                 |\n");

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

// 打印失败界面
void showGameOver()
{
    // 跟随显示不清空
    printf("                                          \n");
    printf("|****************************************|\n");
    printf("|                                        |\n");
    printf("|                 你输了！               |\n");
    printf("|                                        |\n");
    printf("|              1：再来一次               |\n");
    printf("|                                        |\n");
    printf("|              0：返回主页               |\n");
    printf("|                                        |\n");
    printf("|****************************************|\n\n");
}

void showQuitCheck()
{
    system("cls");
    printf("                                          \n");
    printf("|****************************************|\n");
    printf("|                                        |\n");
    printf("|                                        |\n");
    printf("|               确定退出？               |\n");
    printf("|                                        |\n");
    printf("|               1：退出                  |\n");
    printf("|                                        |\n");
    printf("|               0：返回                  |\n");
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
    printf("|                                        |\n");
    printf("|****************************************|\n\n");
}

void showNoData()
{
    system("cls");
    printf("                                          \n");
    printf("|****************************************|\n");
    printf("|                                        |\n");
    printf("|                                        |\n");
    printf("|               游戏：2048               |\n");
    printf("|                                        |\n");
    printf("|             你还未玩过游戏呢           |\n");
    printf("|                                        |\n");
    printf("|             快去玩几轮吧               |\n");
    printf("|                                        |\n");
    printf("|               0：我知道了              |\n");
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

WORD getColorOf(int number)
{
    if (number <= 0 || number > 4096)
        return (DEFAULT_COLOR);

    number = (int)log2(number);
    WORD colors[] = {
        0,
        (BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY),
        (BACKGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY),
        (BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY | FOREGROUND_BLUE),
        (BACKGROUND_RED | BACKGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY),
        (BACKGROUND_GREEN | BACKGROUND_INTENSITY | FOREGROUND_BLUE),
        (BACKGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY),
        (BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY),
        (BACKGROUND_BLUE | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY),
        (BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_BLUE),
        (BACKGROUND_RED | BACKGROUND_BLUE | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY),
        (BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY | FOREGROUND_BLUE),
        (BACKGROUND_BLUE | BACKGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY)};
    return colors[number];
}

void printBlocks(int numbers[][4], int score, int highestScore)
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    system("cls");
    printf("|******|******|******|******|  最高分：%d\n", ((highestScore > score) ? (highestScore) : (score)));
    for (int j = 0; j < 4; j++)
    {
        for (int i = 0; i < 4; i++)
        {
            printf("|");
            SetConsoleTextAttribute(hOut, getColorOf(numbers[i][j]));
            if (numbers[i][j] == 0)
                printf("      ");
            else
                printf(" %-5d", numbers[i][j]);
            SetConsoleTextAttribute(hOut, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        }

        if (j == 0)
            printf("|  分数  ：%d\n", score);
        else
            printf("|\n");
        printf("|******|******|******|******|\n");
    }
    printf(" * 用WASD控制  * Q退出\n");
    printf(" * 关闭输入法或切换成英文以获得最佳游戏体验\n");
}