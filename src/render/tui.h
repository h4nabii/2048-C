#pragma once
#include <windows.h>

/**
 * 基于单元格缓冲的渲染：先用 tui_put 按“列”构图，再由 tui_flush 整帧发成 VT 文本。
 *
 * 为什么不是直接把单元格写进控制台：CHAR_INFO 表达不了“宽字符的后半格”，
 * ConPTY 会把那一格也当作字符发出去，而终端又把汉字按两列渲染，整行就会宽一列、
 * 边框错位。改成发文本后，位置由我们按列算，宽度交给终端，中文才是两格宽。
 *
 * 屏幕生命周期（备用屏幕、VT 开关、光标、格式化缓冲）仍由 render.c 的
 * screenInit/leave_alternate_screen 负责，等渲染函数全部迁完再考虑搬进来。
 *
 * 约定：每帧从 tui_clear 开始，窗口尺寸也在那时跟随。
 */

void tui_init();                                         // 按当前窗口尺寸分配单元格缓冲
void tui_clear(WORD attr);                               // 整屏填成 attr
void tui_put(int x, int y, const char *utf8, WORD attr); // 在第 y 行第 x 列写字符串，超出右边界截断
void tui_flush();                                        // 整屏一次写进控制台

int tui_cols(); // 当前列数
int tui_rows(); // 当前行数
