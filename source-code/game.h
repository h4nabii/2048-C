/*
    GAME2048
    version 4
    GamePart.h
*/

#include <math.h>
#include <windows.h>
#include <stdio.h>

#include "public/global.h"
#include "public/screen.h"
#include "public/input.h"
#include "public/data.h"

#define MOVE_UP 1
#define MOVE_LEFT 2
#define MOVE_DOWN 3
#define MOVE_RIGHT 4

// 游戏相关函数声明
void numberInit(int numbers[][4]);
void game2048();                                   // 游戏主函数
void addBlocks(int N[][4]);                        // 添加方块
int moveBlocks(int N[][4], int mode);              // 移动方块
int addUpBlocks(int N[][4], int mode, int *score); // 加和方块
int testIfEnd(int N[][4]);                         // 测试结束
void setMode(int mode, int *up, int *down, int *left, int *right);

// 添加方块
void addBlocks(int N[][4])
{
    int dup = 1;

    while (dup)
    {
        dup = 0;
        int addBlockNumber;
        int randBlockNumber = rand() % 20;

        if (randBlockNumber >= 0 && randBlockNumber <= 15)
            addBlockNumber = 2;
        if (randBlockNumber >= 16 && randBlockNumber <= 20)
            addBlockNumber = 4;

        int i = (rand() % 4);
        int j = (rand() % 4);

        if (N[i][j] == 0)
            N[i][j] = addBlockNumber;
        else
            dup = 1;
    }
}

// 移动方块
int moveBlocks(int N[][4], int mode)
{
    int prev, cur, moved = 0;

    int up, down, left, right;
    setMode(mode, &up, &down, &left, &right);

    for (int j = 0; j < 4; j++)
        for (int i = 0; i < 3; i++)
        {
            prev = N[j * (up + down) + i * left + (3 - i) * right]
                    [j * (right + left) + i * up + (3 - i) * down];
            cur = N[j * (up + down) + (i + 1) * left + (2 - i) * right]
                   [j * (right + left) + (i + 1) * up + (2 - i) * down];

            if (prev == 0 && cur != 0)
            {
                prev = cur;
                cur = 0;
                N[j * (up + down) + i * left + (3 - i) * right]
                 [j * (right + left) + i * up + (3 - i) * down] = prev;
                N[j * (up + down) + (i + 1) * left + (2 - i) * right]
                 [j * (right + left) + (i + 1) * up + (2 - i) * down] = cur;
                moved++;
            }
        }
    return moved;
}

// 加和方块
int addUpBlocks(int N[][4], int mode, int *score)
{
    int prev, cur, added = 0;

    int up, down, left, right;
    setMode(mode, &up, &down, &left, &right);

    for (int j = 0; j < 4; j++)
    {
        for (int i = 0; i < 3; i++)
        {
            prev = N[j * (up + down) + i * left + (3 - i) * right][j * (right + left) + i * up + (3 - i) * down];
            cur = N[j * (up + down) + (i + 1) * left + (2 - i) * right][j * (right + left) + (i + 1) * up + (2 - i) * down];

            if (prev == cur && prev != 0 && cur != 0)
            {
                added++;
                prev = 2 * cur;
                *score += (2 * cur);
                cur = 0;
                N[j * (up + down) + i * left + (3 - i) * right][j * (right + left) + i * up + (3 - i) * down] = prev;
                N[j * (up + down) + (i + 1) * left + (2 - i) * right][j * (right + left) + (i + 1) * up + (2 - i) * down] = cur;
            }
        }
    }
    return added;
}

// 测试结束
int testIfEnd(int N[][4])
{
    int end = 1;

    for (int j = 0; j < 4; j++)
        for (int i = 0; i < 4; i++)
            if (N[i][j] == 0)
            {
                return 0;
            }

    int prev, cur;
    for (int k = 1; k <= 2; k++)
    {
        int up, down, left, right;
        setMode(k, &up, &down, &left, &right);

        for (int j = 0; j < 4; j++)
            for (int i = 0; i < 3; i++)
            {
                prev = N[j * (up + down) + i * left + (3 - i) * right]
                        [j * (right + left) + i * up + (3 - i) * down];
                cur = N[j * (up + down) + (i + 1) * left + (2 - i) * right]
                       [j * (right + left) + (i + 1) * up + (2 - i) * down];
                if (prev == cur)
                    end = 0;
            }
    }
    return end;
}

void numberInit(int numbers[][4])
{
    for (int j = 0; j < 4; j++)
        for (int i = 0; i < 4; i++)
            numbers[i][j] = 0;

    if (testMode)
    {
        for (int j = 0; j < 4; j++)
            for (int i = 0; i < 4; i++)
                numbers[i][j] = (int)pow(2.00, (double)i + (double)j * 4 + 1);

        numbers[3][3] = 0;
    }
    else
    {
        addBlocks(numbers);
    }
}

void game2048()
{
    int score = 0;
    int highestScore = readHighestScore();

    int end;

    int blockNumbers[4][4];
    numberInit(blockNumbers);

    int quit = 0;
    int surequit = 0;

    do
    {
        int command;
        printBlocks(blockNumbers, score, highestScore);

        if (testMode)
            command = CMD_D;
        else
            command = waitGameKeyDown();

        if (command == CMD_Q)
        {
            showQuitCheck();
            surequit = waitDigitKeyDown(0, 1);

            if (surequit == 1)
            {
                end = 1;
                quit = 1;
            }
            else
            {
                end = 0;
                quit = 0;
            }
        }

        if (!surequit)
        {
            int addNumber = 0, moveNumber = 0;
            
            for (int i = 0; i < 4; i++)
            {
                if (i == 2)
                    addNumber += addUpBlocks(blockNumbers, command, &score);
                else
                    moveNumber += moveBlocks(blockNumbers, command);
            }
            while ((addNumber + moveNumber) != 0)
            {
                addBlocks(blockNumbers);
                addNumber = 0, moveNumber = 0;
            }

            if (command != 0)
                end = testIfEnd(blockNumbers);
        }

    } while (!end);

    printBlocks(blockNumbers, score, highestScore);

    if (!testMode && !quit)
        saveScore(score);
}

void setMode(int mode, int *up, int *down, int *left, int *right)
{
    *up = *down = *left = *right = 0;
    switch (mode)
    {
    case (MOVE_UP):
        *up = 1;
        break;
    case (MOVE_DOWN):
        *down = 1;
        break;
    case (MOVE_LEFT):
        *left = 1;
        break;
    case (MOVE_RIGHT):
        *right = 1;
        break;
    default:
        break;
    }
}