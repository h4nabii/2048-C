#pragma once
#include <windows.h>

// 单屏宽度（列），以及盒子内部内容区的宽度（列）
#define SCREEN_WIDTH 42
#define SCREEN_INNER 40

// 界面配置项：在初始化列表里按行号定义一行内容，未定义的行留空
#define defineLine(row, text) [row] = text

void screenInit();

/**
 * 渲染一个界面：可选清屏，随后输出顶边留白、上下边框，内容行按内容区居中。
 * lines 为界面内容行（不含左右边框），空串或 NULL 表示空行。
 */
void renderScreen(const char *const *lines, int lineCount, int clearScreen);

/**
 * 渲染游戏棋盘：4x4 棋盘 + 分数/最高分。
 */
void printBlocks(int numbers[][4], int score, int highestScore);

/**
 * 渲染分数记录分页界面：每页 15 行，行首为 0 表示该行留空。
 */
void renderScoreTable(int rows[][7], int page, int currentPage);