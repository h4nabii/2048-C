/*
    GAME2048
    version 4
    ScoSavLoad.h
*/

#include <windows.h>
#include <math.h>
#include <stdio.h>

void createFileStructures(); // 添加资源保存文件夹
void saveScore(int score);   // 保存分数
void loadScore();            // 读取分数

// 保存相关函数声明
void fileInit()
{
    // Test if runing the first time, create necessary files
    FILE *file;
    if (fopen_s(&file, "TEST\\HaveDone.txt", "r"))
    {
        // file not exist, generate structures
        _mkdir("TEST");
        if (!fopen_s(&file, "TEST\\HaveDone.txt", "w"))
        {
            fprintf(file, "HavePrepared\n");
            fclose(file);
            createFileStructures();
        }
        else
        {
            printf("Unable to write files");
        }
    }
}

//******************************************************************************************

// 保存分数
void saveScore(int score)
{
    struct tm t;           // tm结构指针
    time_t now;            // 声明time_t类型变量
    time(&now);            // 获取系统日期和时间
    localtime_s(&t, &now); // 获取当地日期和时间

    FILE *scoreFile;
    errno_t fileErr;
    fileErr = fopen_s(&scoreFile, "SAVE\\SCORE\\score.txt", "r+");

    // 0L, convert to long before overflow
    fseek(scoreFile, 0 - (long)sizeof(int), SEEK_END);
    fprintf(scoreFile, "%-8d %-4d %-2d %-2d   %-2d %-2d %-2d\n0000", score, t.tm_year + 1900, t.tm_mon + 1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
    fclose(scoreFile);
}

// 读取分数
void loadScore()
{
    FILE *scoreFile;
    errno_t fileErr;

    int counter;                     // 测试数据数量时读取数据的储存变量
    int quantityOfData = 0;          // 数据数量
    int printedNumbers[15][7] = {0}; // 需打印的数据
    int page = 0;                    // 总页数
    int currentPage = 1;             // 记录当前页数
    int choice;                      // 存储选择
    int blanks;                      // 记录不需打印的行数

    fileErr = fopen_s(&scoreFile, "SAVE\\SCORE\\score.txt", "r");

    fscanf_s(scoreFile, "%d", &counter);
    while (counter != 0) // 计数据数量
    {
        for (int i = 0; i < 6; i++)
            fscanf_s(scoreFile, "%d", &counter);

        quantityOfData++;
        fscanf_s(scoreFile, "%d", &counter);
    }

    fclose(scoreFile);

    if (quantityOfData != 0) // 若有数据
    {
        page = (int)ceil(quantityOfData / 15.0);

        int *scoreData = (int *)malloc(7 * 15 * page * sizeof(int));

        fileErr = fopen_s(&scoreFile, "SAVE\\SCORE\\score.txt", "r");

        for (int i = 0; i < quantityOfData; i++) // 读取数据
        {
            fscanf_s(scoreFile, "%d", scoreData + 7 * i);

            if (scoreData + 7 * i != 0)
                for (int j = 1; j < 7; j++)
                    fscanf_s(scoreFile, "%d", scoreData + (7 * i + j));
        }

        fclose(scoreFile);

        do
        {

            if (currentPage == page)
                blanks = 15 * page - quantityOfData;
            else
                blanks = 0;

            for (int i = 0; i < 15; i++)
                for (int j = 0; j < 7; j++)
                    if (i <= 15 - blanks)
                        printedNumbers[i][j] =
                            *(scoreData + 7 * (quantityOfData - i - 1) - 15 * 7 * (currentPage - 1) + j);
                    else
                        printedNumbers[i][j] = 0;

            system("cls");

            printf("                                          \n"); // 打印页面
            printf("|****************************************|\n");
            for (int i = 0; i < 15; i++)
                if (printedNumbers[i][0] != 0)
                {
                    printf("| %-8d %-4d.%-2d.%-2d   %-2d:%-2d:%-2d         |\n",
                           printedNumbers[i][0],
                           printedNumbers[i][1],
                           printedNumbers[i][2],
                           printedNumbers[i][3],
                           printedNumbers[i][4],
                           printedNumbers[i][5],
                           printedNumbers[i][6]);
                }
                else
                {
                    printf("|                                        |\n");
                }

            printf("|                                        |\n");
            printf("|                               %3d/%-3d  |\n", currentPage, page);
            printf("| 1:上一页 2:下一页 0:退出               |\n");
            printf("|****************************************|\n\n");

            choice = waitDigitKeyDown(0, 2);

            switch (choice) // 判断选择
            {
            case (2):
                if (currentPage < page)
                {
                    currentPage++;
                }
                break;
            case (1):
                if (currentPage > 1)
                {
                    currentPage--;
                }
                break;
            }
        } while (choice != 0);

        free(scoreData);
    }

    else
    { // 若无数据
        system("cls");
        printf("                                          \n");
        printf("|****************************************|\n");
        printf("|                                        |\n");
        printf("|                                        |\n");
        printf("|               游戏：2048               |\n");
        printf("|                                        |\n");
        printf("|             你还未玩过游戏呢           |\n");
        printf("|                                        |\n");
        printf("|             快去玩几把吧               |\n");
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
        choice = waitDigitKeyDown(0, 0);
    }
}

// 添加资源保存文件夹
void createFileStructures()
{
    _mkdir("SAVE");
    _mkdir("SCREEN");

    _mkdir("SAVE\\SCORE");
    _mkdir("SAVE\\GAME_SAVE");
    _mkdir("SCREEN\\STYLE");
    _mkdir("SCREEN\\CONTROL_WAY");

    errno_t err;
    FILE *pFile;

    err = fopen_s(&pFile, "SAVE\\SCORE\\score.txt", "w");
    fprintf(pFile, "0000");
    fclose(pFile);
    err = fopen_s(&pFile, "SAVE\\SCORE\\highest score.txt", "w");
    fclose(pFile);
}
