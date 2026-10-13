#pragma once
#include <windows.h>

// 单屏宽度（列），以及盒子内部内容区的宽度（列）
#define SCREEN_WIDTH 42
#define SCREEN_INNER 40

// 控制台窗口尺寸（列 × 行）：放得下最宽的一行（棋盘行的 45 列）与最高的界面
#define WINDOW_WIDTH 45
#define WINDOW_HEIGHT 25

// 界面配置项：在初始化列表里按行号定义一行内容，未定义的行留空
#define defineLine(row, text) [row] = text

void screen_init();

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

/**
 * 读取终端可见窗口的尺寸（列 × 行）；无控制台（输出被重定向）时返回 0 × 0。
 */
void get_window_size(int *width, int *height);

/**
 * 退出备用屏幕，恢复进入前的终端内容；正常退出与 Ctrl+C 都会调用，重复调用无副作用。
 */
void leave_alternate_screen();