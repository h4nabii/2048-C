#include "board.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

Board *board_create(int h, int w) {
  Board *board = (Board *)malloc(sizeof(Board));
  if (board) {
    board->height = h;
    board->width = w;
    board->cell = (int *)malloc(sizeof(int) * h * w);
    for (int row = 0; row < h; row++)
      for (int col = 0; col < w; col++)
        board->cell[row * w + col] = 0;
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
  for (int row = 0; row < 4; row++)
    for (int col = 0; col < 4; col++)
      numbers[col][row] = board_get(board, row, col);
}

void board_setup(Board *board, int test_mode) {
  if (!board)
    return;
  if (test_mode) {
    // 初始化棋盘为测试模式的初始状态
    for (int row = 0; row < board->height; row++)
      for (int col = 0; col < board->width; col++)
        board->cell[col + row * board->width] = (int)pow(2.00, (double)col + (double)row * board->width + 1);
    board_set(board, 3, 3, 0);
  } else {
    // 初始化棋盘为普通模式的初始状态
    board_random_add(board);
  }
}

int board_check_pos_range(Board *board, int row, int col) {
  return row >= 0 && row < board->height && col >= 0 && col < board->width;
}

int board_get(Board *board, int row, int col) {
  if (!board_check_pos_range(board, row, col))
    return -1;
  return board->cell[row * board->width + col];
}

int board_set(Board *board, int row, int col, int value) {
  if (!board_check_pos_range(board, row, col))
    return -1;
  board->cell[row * board->width + col] = value;
  return 0;
}

int board_is_full(Board *board) {
  for (int row = 0; row < board->height; row++)
    for (int col = 0; col < board->width; col++)
      if (board_get(board, row, col) == 0)
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
    int row = (rand() % board->height);
    int col = (rand() % board->width);
    if (board_get(board, row, col) == 0)
      board_set(board, row, col, new_num);
    else
      dup = 1;
  }
  return 0;
}

void board_print(Board *board) {
  for (int row = 0; row < board->height; row++) {
    for (int col = 0; col < board->width; col++) {
      printf("%4d ", board_get(board, row, col));
    }
    printf("\n");
  }
}

int board_move_all(Board *board, MoveDirection direction) {
  // 计算移动的长度，根据方向选择行或列的长度
  const int is_horizontal = direction == MOVE_LEFT || direction == MOVE_RIGHT;
  // 左上为负，右下为正，决定移动的方向，逆序遍历
  const int step = direction == MOVE_UP || direction == MOVE_LEFT ? -1 : 1;

  // 根据移动方向确定遍历顺序和步长
  const int len = is_horizontal ? board->width : board->height;
  const int pad = is_horizontal ? board->height : board->width;

  // 根据移动方向计算行列偏移量
  const int row_offset = is_horizontal ? 0 : step;
  const int col_offset = is_horizontal ? step : 0;

  // 标记是否有方块移动
  int move_count = 0;

  for (int p = 0; p < pad; p++) {
    for (int i = 1; i < len; i++) {
      for (int j = i; j > 0; j--) {
        // 根据移动方向进行坐标转换
        const int iter = step == -1 ? j : len - 1 - j;
        const int row = is_horizontal ? p : iter;
        const int col = is_horizontal ? iter : p;
        const int next_row = row + row_offset;
        const int next_col = col + col_offset;
        // 移动数值
        const int cur_val = board_get(board, row, col);
        const int pre_val = board_get(board, next_row, next_col);
        if (cur_val == 0 || pre_val != 0)
          break;
        board_set(board, next_row, next_col, cur_val);
        board_set(board, row, col, 0);
        move_count++;
      }
    }
  }
  return move_count;
}

int board_merge_all(Board *board, MoveDirection direction) { // 计算移动的长度，根据方向选择行或列的长度
  const int is_horizontal = direction == MOVE_LEFT || direction == MOVE_RIGHT;
  // 左上为负，右下为正，决定移动的方向，逆序遍历
  const int step = direction == MOVE_UP || direction == MOVE_LEFT ? -1 : 1;

  // 根据移动方向确定遍历顺序和步长
  const int len = is_horizontal ? board->width : board->height;
  const int pad = is_horizontal ? board->height : board->width;

  // 根据移动方向计算行列偏移量
  const int row_offset = is_horizontal ? 0 : step;
  const int col_offset = is_horizontal ? step : 0;

  // 标记合并的方块的总值
  int merge_count = 0;

  for (int p = 0; p < pad; p++) {
    for (int i = 1; i < len; i++) {
      // 根据移动方向进行坐标转换
      const int iter = step == -1 ? i : len - 1 - i;
      const int row = is_horizontal ? p : iter;
      const int col = is_horizontal ? iter : p;
      const int next_row = row + row_offset;
      const int next_col = col + col_offset;
      // 合并数值
      const int cur_val = board_get(board, row, col);
      const int pre_val = board_get(board, next_row, next_col);
      if (cur_val != 0 && pre_val != 0 && cur_val == pre_val) {
        board_set(board, next_row, next_col, cur_val * 2);
        board_set(board, row, col, 0);
        merge_count += cur_val * 2;
      }
    }
  }
  return merge_count;
}