/*
    GAME2048
    version 4
    Setting.h
*/

#include "public/input.h"

#include "render/render.h"

// 设置相关函数
void settingGreeting();    // 打印设置界面
int toMakeSureColorTest(); // 询问是否打开测试模式

//******************************************************************************************

void runSetting() {
  int settingChoice;
  do {
    settingGreeting();
    settingChoice = waitDigitKeyDown(0, 1);
    if (settingChoice == 1)
      testMode = toMakeSureColorTest();
  } while (settingChoice);
}

#define SETTING_ROWS 18

static const char *settingLines[SETTING_ROWS] = {
    defineLine(2, "游戏：2048"),
    defineLine(4, "1：颜色测试模式"),
    defineLine(6, "0：退出"),
};

// 打印设置界面
void settingGreeting() { renderScreen(settingLines, SETTING_ROWS, 1); }

#define COLOR_TEST_ROWS 18

static const char *colorTestLines[COLOR_TEST_ROWS] = {
    defineLine(2, "游戏：2048"),
    defineLine(4, "确认打开颜色测试？"),
    defineLine(6, "1：是        0：否"),
};

// 询问是否打开测试模式
int toMakeSureColorTest() {
  int Choice;

  renderScreen(colorTestLines, COLOR_TEST_ROWS, 1);
  Choice = waitDigitKeyDown(0, 1);
  return Choice;
}
