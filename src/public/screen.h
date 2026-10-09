#pragma once
#include <string.h>

#include "global.h"

#include "render/render.h"

void showHome();
void showMenu();
void showGameOver();
void showQuitCheck();

// 界面内容行按行号定义，未定义的行为空行；居中与边框由 render 负责
#define HOME_ROWS 19

static const char *homeLines[HOME_ROWS] = {
    defineLine(2, "游戏：2048"),
    defineLine(4, "1：开始"),
    defineLine(6, "2：菜单"),
    defineLine(8, "0：退出"),
};

// 显示首页；颜色测试模式下开始项文案不同
void showHome() {
  const char *lines[HOME_ROWS];

  memcpy(lines, homeLines, sizeof(lines));
  if (testMode == 1)
    lines[4] = "1：开始(颜色测试模式)";

  renderScreen(lines, HOME_ROWS, 1);
}

#define MENU_ROWS 19

static const char *menuLines[MENU_ROWS] = {
    defineLine(2, "游戏：2048"),
    defineLine(4, "1：分数记录"),
    defineLine(6, "2：设置"),
    defineLine(8, "0：退出"),
};

// 显示菜单界面
void showMenu() { renderScreen(menuLines, MENU_ROWS, 1); }

#define GAME_OVER_ROWS 7

static const char *gameOverLines[GAME_OVER_ROWS] = {
    defineLine(1, "你输了！"),
    defineLine(3, "1：再来一次"),
    defineLine(5, "0：返回主页"),
};

// 显示失败界面（跟随显示，不清屏）
void showGameOver() { renderScreen(gameOverLines, GAME_OVER_ROWS, 0); }

#define QUIT_CHECK_ROWS 18

static const char *quitCheckLines[QUIT_CHECK_ROWS] = {
    defineLine(2, "确定退出？"),
    defineLine(4, "1：退出"),
    defineLine(6, "0：返回"),
};

// 显示退出确认界面
void showQuitCheck() { renderScreen(quitCheckLines, QUIT_CHECK_ROWS, 1); }

#define NO_DATA_ROWS 18

static const char *noDataLines[NO_DATA_ROWS] = {
    defineLine(2, "游戏：2048"),
    defineLine(4, "你还未玩过游戏呢"),
    defineLine(6, "快去玩几轮吧"),
    defineLine(8, "0：我知道了"),
};

// 显示无数据界面
void showNoData() { renderScreen(noDataLines, NO_DATA_ROWS, 1); }
