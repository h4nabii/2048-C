#include "board.h"

#include <math.h>
#include <stdlib.h>

Board *board_create(int h, int w) {
  Board *board = (Board *)malloc(sizeof(Board));
  if (board) {
    board->height = h;
    board->width = w;
    board->cell = (int *)malloc(sizeof(int) * h * w);
    for (int j = 0; j < h; j++)
      for (int i = 0; i < w; i++)
        board->cell[i + j * w] = 0;
  }
  return board;
}

int board_destroy(Board *board) {
  if (board) {
    free(board->cell);
    free(board);
    return 0;
  }
  return -1;
}

void board_cast(Board *board, int numbers[][4]) {
  for (int j = 0; j < 4; j++)
    for (int i = 0; i < 4; i++)
      numbers[i][j] = board_get(board, i, j);
}

void board_setup(Board *board, int test_mode) {
  if (!board)
    return;
  if (test_mode) {
    // 初始化棋盘为测试模式的初始状态
    for (int j = 0; j < board->height; j++)
      for (int i = 0; i < board->width; i++)
        board->cell[i + j * board->width] = (int)pow(2.00, (double)i + (double)j * board->width + 1);
    board_set(board, 3, 3, 0);
  } else {
    // 初始化棋盘为普通模式的初始状态
    board_random_add(board);
  }
}

int board_check_pos_range(Board *board, int i, int j) {
  return i >= 0 && i < board->height && j >= 0 && j < board->width;
}

int board_get(Board *board, int i, int j) {
  if (!board_check_pos_range(board, i, j))
    return -1;
  return board->cell[i + j * board->width];
}

int board_set(Board *board, int i, int j, int value) {
  if (!board_check_pos_range(board, i, j))
    return -1;
  board->cell[i + j * board->width] = value;
  return 0;
}

int board_is_full(Board *board) {
  for (int j = 0; j < board->height; j++)
    for (int i = 0; i < board->width; i++)
      if (board_get(board, i, j) == 0)
        return 0;
  return 1;
}

int board_random_add(Board *board) {
  // 如果棋盘已满，无法添加新方块，返回 -1
  if (board_is_full(board))
    return -1;

  // 0-15 生成 2，16-19 生成 4
  const int RAND_VAL_MAX = 20;
  const int RAND_THRESHOLD = 16;
  int rand_val = rand() % RAND_VAL_MAX;
  int new_num = (rand_val < RAND_THRESHOLD) ? 2 : 4;

  int dup = 1;
  while (dup) {
    dup = 0;
    int i = (rand() % board->height);
    int j = (rand() % board->width);
    if (board_get(board, i, j) == 0)
      board_set(board, i, j, new_num);
    else
      dup = 1;
  }
  return 0;
}
