#include "tui.h"

#include <stdio.h>
#include <stdlib.h>

static HANDLE tui_out;
static CHAR_INFO *cells; // cols * rows 个格子，按“列”排；一个宽字符占两格（后一格是它的后半格）
static char *frame;      // 每帧拼好的 VT 文本
static size_t frame_size;
static int cols, rows;

// 每格在最坏情况下的字节数：改一次颜色 "\e[107;100m" 11 字节 + 一个 UTF-8 字符 4 字节
#define CELL_BYTES 16
// 每行一次光标定位 "\e[999;1H" 12 字节
#define ROW_BYTES 16

// 窗口尺寸变了就按新尺寸重建缓冲，内容不保留
static void sync_size() {
  CONSOLE_SCREEN_BUFFER_INFO info;
  int new_cols, new_rows;
  size_t need;

  if (!GetConsoleScreenBufferInfo(tui_out, &info))
    return;

  new_cols = info.srWindow.Right - info.srWindow.Left + 1;
  new_rows = info.srWindow.Bottom - info.srWindow.Top + 1;

  if (new_cols == cols && new_rows == rows)
    return;

  free(cells);
  free(frame);
  cols = new_cols;
  rows = new_rows;
  cells = malloc((size_t)cols * rows * sizeof(CHAR_INFO));

  need = (size_t)rows * ROW_BYTES + (size_t)cols * rows * CELL_BYTES + 1;
  frame = malloc(need);
  frame_size = need;
}

void tui_init() {
  tui_out = GetStdHandle(STD_OUTPUT_HANDLE);
  sync_size();
}

void tui_clear(WORD attr) {
  sync_size();

  for (int i = 0; i < cols * rows; i++) {
    cells[i].Char.UnicodeChar = L' ';
    cells[i].Attributes = attr;
  }
}

void tui_put(int x, int y, const char *utf8, WORD attr) {
  WCHAR wide[256];
  int count;

  if (x < 0 || y < 0 || y >= rows)
    return;

  count = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wide, 256) - 1; // 结尾的 L'\0' 不计

  for (int i = 0; i < count && x < cols; i++) {
    int width = wide[i] >= 0x80 ? 2 : 1; // 汉字与全角标点按两列算

    cells[y * cols + x].Char.UnicodeChar = wide[i];
    cells[y * cols + x].Attributes = attr;

    if (width == 2 && x + 1 < cols) { // 后半格填个空格占位，flush 时不会单独发出去
      cells[y * cols + x + 1].Char.UnicodeChar = L' ';
      cells[y * cols + x + 1].Attributes = attr;
    }

    x += width;
  }
}

// 控制台属性 → SGR 颜色号。Windows 的位序是 B=1/G=2/R=4，SGR 的序号是 R=1/G=2/B=4
static int ansi_fg(WORD attr) {
  return ((attr & FOREGROUND_INTENSITY) ? 90 : 30) + ((attr & FOREGROUND_RED) ? 1 : 0) +
         ((attr & FOREGROUND_GREEN) ? 2 : 0) + ((attr & FOREGROUND_BLUE) ? 4 : 0);
}

static int ansi_bg(WORD attr) {
  return ((attr & BACKGROUND_INTENSITY) ? 100 : 40) + ((attr & BACKGROUND_RED) ? 1 : 0) +
         ((attr & BACKGROUND_GREEN) ? 2 : 0) + ((attr & BACKGROUND_BLUE) ? 4 : 0);
}

/**
 * 整帧发成 VT 文本：每行先定位，再按属性分段转成 UTF-8 发出去。
 * 不能直接写单元格缓冲——CHAR_INFO 表达不了“宽字符的后半格”，
 * ConPTY 会把那一格也当成字符发出去，终端再按两列渲染汉字，整行就宽了一列。
 * 交给终端排版则宽度天然正确：位置由我们按列算，宽度由终端定。
 */
void tui_flush() {
  size_t len = 0;
  WORD shown = 0;
  int have_shown = 0;

  for (int y = 0; y < rows; y++) {
    len += (size_t)sprintf(frame + len, "\x1b[%d;1H", y + 1);

    for (int x = 0; x < cols;) {
      WORD attr = cells[y * cols + x].Attributes;
      WCHAR run[256];
      int count = 0;

      // 同一属性的连续格子合成一段；宽字符的后半格不参与（它是上半格的两列之延展）
      while (x < cols && count < 256) {
        WCHAR ch = cells[y * cols + x].Char.UnicodeChar;

        run[count++] = ch;
        x++;

        if (ch >= 0x80 && x < cols && cells[y * cols + x].Attributes == attr)
          x++; // 跳过后半格
      }

      if (!have_shown || attr != shown) {
        len += (size_t)sprintf(frame + len, "\x1b[%d;%dm", ansi_fg(attr), ansi_bg(attr));
        shown = attr;
        have_shown = 1;
      }

      len += (size_t)WideCharToMultiByte(CP_UTF8, 0, run, count, frame + len, (int)(frame_size - len), NULL, NULL);
    }
  }

  fwrite(frame, 1, len, stdout);
  fflush(stdout);
}

int tui_cols() { return cols; }

int tui_rows() { return rows; }

