/*
    GAME2048
    version 4
    Setting.h
*/

// 设置相关函数
void settingGreeting();    // 打印设置界面
int toMakeSureColorTest(); // 询问是否打开测试模式

//******************************************************************************************

void runSetting()
{
    int settingChoice;
    do
    {
        settingGreeting();
        settingChoice = waitDigitKeyDown(0, 1);
        if (settingChoice == 1)
            testMode = toMakeSureColorTest();
    } while (settingChoice);
}

// 打印设置界面
void settingGreeting()
{
    system("cls");
    printf("                                          \n");
    printf("|****************************************|\n");
    printf("|                                        |\n");
    printf("|                                        |\n");
    printf("|               游戏：2048               |\n");
    printf("|                                        |\n");
    printf("|               1：颜色测试模式          |\n");
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
    printf("|                                        |\n");
    printf("|****************************************|\n\n");
}

// 询问是否打开测试模式
int toMakeSureColorTest()
{
    int Choice;
    system("cls");
    printf("                                          \n");
    printf("|****************************************|\n");
    printf("|                                        |\n");
    printf("|                                        |\n");
    printf("|               游戏：2048               |\n");
    printf("|                                        |\n");
    printf("|           确认打开颜色测试？           |\n");
    printf("|                                        |\n");
    printf("|           1：是        0：否           |\n");
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
    Choice = waitDigitKeyDown(0, 1);
    return Choice;
}
