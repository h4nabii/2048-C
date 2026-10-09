#include "render.h"

#include <math.h>
#include <stdio.h>

#define DEFAULT_COLOR (BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY)

// 内容的显示宽度：ASCII 记 1 列，汉字与全角标点记 2 列
static int displayWidth(const char *text) {
  int width = 0;

  for (; *text; text++)
    // 跳过 UTF-8 续接字节，一个字符只计一次
    if (((unsigned char)*text & 0xC0) != 0x80)
      width += ((unsigned char)*text >= 0x80) ? 2 : 1;

  return width;
}

// 输出一行内容行，左侧留 leftPad 列，右侧补足到内容区宽度
static void printPaddedLine(const char *text, int leftPad) {
  int remain = SCREEN_INNER - leftPad - displayWidth(text);

  printf("|");
  for (int i = 0; i < leftPad; i++)
    putchar(' ');
  printf("%s", text);
  for (int i = 0; i < remain; i++)
    putchar(' ');
  printf("|\n");
}

// 内容区居中的一行
static void printCenterLine(const char *text) { printPaddedLine(text, (SCREEN_INNER - displayWidth(text)) / 2); }

// 上下边框
static void printBorder() {
  printf("|");
  for (int i = 0; i < SCREEN_INNER; i++)
    putchar('*');
  printf("|\n");
}

// 顶边留白，把盒子下移一行
static void printTopMargin() {
  for (int i = 0; i < SCREEN_WIDTH; i++)
    putchar(' ');
  putchar('\n');
}

void screenInit() {
  HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

  // Set window size (useless when using Windows Terminal)
  system("mode con cols=45 lines=25");

  // 界面文案为 UTF-8，控制台需按 UTF-8 解释，否则中文乱码并撑破边框
  SetConsoleOutputCP(CP_UTF8);

  SetConsoleTitleA("2048");

  SetConsoleTextAttribute(hOut, DEFAULT_COLOR);

  system("cls");
}

void renderScreen(const char *const *lines, int lineCount, int clearScreen) {
  if (clearScreen)
    system("cls");

  printTopMargin();
  printBorder();

  for (int i = 0; i < lineCount; i++)
    printCenterLine(lines[i] ? lines[i] : "");

  printBorder();
  putchar('\n');
}

static WORD getColorOf(int number) {
  if (number <= 0 || number > 4096)
    return (DEFAULT_COLOR);

  number = (int)log2(number);
  WORD colors[] = {
      0,
      (BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED |
       FOREGROUND_INTENSITY),
      (BACKGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY),
      (BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY | FOREGROUND_BLUE),
      (BACKGROUND_RED | BACKGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY),
      (BACKGROUND_GREEN | BACKGROUND_INTENSITY | FOREGROUND_BLUE),
      (BACKGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY),
      (BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED |
       FOREGROUND_INTENSITY),
      (BACKGROUND_BLUE | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY),
      (BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_BLUE),
      (BACKGROUND_RED | BACKGROUND_BLUE | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY),
      (BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY | FOREGROUND_BLUE),
      (BACKGROUND_BLUE | BACKGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED |
       FOREGROUND_INTENSITY)};
  return colors[number];
}

void printBlocks(int numbers[][4], int score, int highestScore) {
  HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
  system("cls");
  printf("|******|******|******|******|  最高分：%d\n", ((highestScore > score) ? (highestScore) : (score)));
  for (int j = 0; j < 4; j++) {
    for (int i = 0; i < 4; i++) {
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

void renderScoreTable(int rows[][7], int page, int currentPage) {
  char line[SCREEN_INNER + 1];
  char footer[SCREEN_INNER + 1];

  system("cls");

  printTopMargin();
  printBorder();

  for (int i = 0; i < 15; i++) {
    if (rows[i][0] != 0) {
      snprintf(line, sizeof(line), " %-8d %-4d.%-2d.%-2d   %-2d:%-2d:%-2d", rows[i][0], rows[i][1], rows[i][2],
               rows[i][3], rows[i][4], rows[i][5], rows[i][6]);
      printPaddedLine(line, 0);
    } else {
      printCenterLine("");
    }
  }
  printCenterLine("");

  snprintf(footer, sizeof(footer), "%3d/%-3d", currentPage, page);
  printPaddedLine(footer, SCREEN_INNER - 2 - displayWidth(footer));
  printPaddedLine("1:上一页 2:下一页 0:退出", 1);

  printBorder();
  putchar('\n');
}
