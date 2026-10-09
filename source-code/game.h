/*
    GAME2048
    version 4
    GamePart.h
*/

#include <math.h>
#include <stdio.h>
#include <windows.h>

#include "public/data.h"
#include "public/global.h"
#include "public/input.h"
#include "public/screen.h"

#define MOVE_UP 1
#define MOVE_LEFT 2
#define MOVE_DOWN 3
#define MOVE_RIGHT 4

// ======================================
// BOARD
// ======================================

#define BOARD_SIZE 4

typedef struct {
  int cell[BOARD_SIZE][BOARD_SIZE];
} Board;

Board *board_create();
int board_destroy(Board *board);
void board_cast(Board *board, int numbers[][4]);
void board_setup(Board *board, int test_mode);
int board_check_pos_range(int i, int j);
int board_get(Board *board, int i, int j);
int board_set(Board *board, int i, int j, int value);
int board_is_full(Board *board);
int board_random_add(Board *board);

// ======================================
// 游戏相关函数声明
// ======================================

void numberInit(int numbers[][4]);
void game2048();                                   // 游戏主函数
void addBlocks(int N[][4]);                        // 添加方块
int moveBlocks(int N[][4], int mode);              // 移动方块
int addUpBlocks(int N[][4], int mode, int *score); // 加和方块
int testIfEnd(int N[][4]);                         // 测试结束
void setMode(int mode, int *up, int *down, int *left, int *right);

// 添加方块
void addBlocks(int N[][4]) {
  int dup = 1;

  while (dup) {
    dup = 0;
    int addBlockNumber;
    int randBlockNumber = rand() % 20;

    if (randBlockNumber >= 0 && randBlockNumber <= 15)
      addBlockNumber = 2;
    if (randBlockNumber >= 16 && randBlockNumber <= 20)
      addBlockNumber = 4;

    int i = (rand() % 4);
    int j = (rand() % 4);

    if (N[i][j] == 0)
      N[i][j] = addBlockNumber;
    else
      dup = 1;
  }
}

// 移动方块
int moveBlocks(int N[][4], int mode) {
  int prev, cur, moved = 0;

  int up, down, left, right;
  setMode(mode, &up, &down, &left, &right);

  for (int j = 0; j < 4; j++)
    for (int i = 0; i < 3; i++) {
      prev = N[j * (up + down) + i * left + (3 - i) * right][j * (right + left) + i * up + (3 - i) * down];
      cur = N[j * (up + down) + (i + 1) * left + (2 - i) * right][j * (right + left) + (i + 1) * up + (2 - i) * down];

      if (prev == 0 && cur != 0) {
        prev = cur;
        cur = 0;
        N[j * (up + down) + i * left + (3 - i) * right][j * (right + left) + i * up + (3 - i) * down] = prev;
        N[j * (up + down) + (i + 1) * left + (2 - i) * right][j * (right + left) + (i + 1) * up + (2 - i) * down] = cur;
        moved++;
      }
    }
  return moved;
}

// 加和方块
int addUpBlocks(int N[][4], int mode, int *score) {
  int prev, cur, added = 0;

  int up, down, left, right;
  setMode(mode, &up, &down, &left, &right);

  for (int j = 0; j < 4; j++) {
    for (int i = 0; i < 3; i++) {
      prev = N[j * (up + down) + i * left + (3 - i) * right][j * (right + left) + i * up + (3 - i) * down];
      cur = N[j * (up + down) + (i + 1) * left + (2 - i) * right][j * (right + left) + (i + 1) * up + (2 - i) * down];

      if (prev == cur && prev != 0 && cur != 0) {
        added++;
        prev = 2 * cur;
        *score += (2 * cur);
        cur = 0;
        N[j * (up + down) + i * left + (3 - i) * right][j * (right + left) + i * up + (3 - i) * down] = prev;
        N[j * (up + down) + (i + 1) * left + (2 - i) * right][j * (right + left) + (i + 1) * up + (2 - i) * down] = cur;
      }
    }
  }
  return added;
}

// 测试结束
int testIfEnd(int N[][4]) {
  int end = 1;

  for (int j = 0; j < 4; j++)
    for (int i = 0; i < 4; i++)
      if (N[i][j] == 0) {
        return 0;
      }

  int prev, cur;
  for (int k = 1; k <= 2; k++) {
    int up, down, left, right;
    setMode(k, &up, &down, &left, &right);

    for (int j = 0; j < 4; j++)
      for (int i = 0; i < 3; i++) {
        prev = N[j * (up + down) + i * left + (3 - i) * right][j * (right + left) + i * up + (3 - i) * down];
        cur = N[j * (up + down) + (i + 1) * left + (2 - i) * right][j * (right + left) + (i + 1) * up + (2 - i) * down];
        if (prev == cur)
          end = 0;
      }
  }
  return end;
}

Board *board_create() {
  Board *board = (Board *)malloc(sizeof(Board));
  if (board) {
    for (int j = 0; j < BOARD_SIZE; j++)
      for (int i = 0; i < BOARD_SIZE; i++)
        board->cell[i][j] = 0;
  }
  return board;
}

int board_destroy(Board *board) {
  if (board) {
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
    for (int j = 0; j < BOARD_SIZE; j++)
      for (int i = 0; i < BOARD_SIZE; i++)
        board->cell[i][j] = (int)pow(2.00, (double)i + (double)j * BOARD_SIZE + 1);
    board_set(board, 3, 3, 0);
  } else {
    // 初始化棋盘为普通模式的初始状态
    board_random_add(board);
  }
}

int board_check_pos_range(int i, int j) { return i >= 0 && i < BOARD_SIZE && j >= 0 && j < BOARD_SIZE; }

int board_get(Board *board, int i, int j) {
  if (!board_check_pos_range(i, j))
    return -1;
  return board->cell[i][j];
}

int board_set(Board *board, int i, int j, int value) {
  if (!board_check_pos_range(i, j))
    return -1;
  board->cell[i][j] = value;
  return 0;
}

int board_is_full(Board *board) {
  for (int j = 0; j < BOARD_SIZE; j++)
    for (int i = 0; i < BOARD_SIZE; i++)
      if (board_get(board, i, j) == 0)
        return 0;
  return 1;
}

// 添加方块
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
    int i = (rand() % 4);
    int j = (rand() % 4);
    if (board_get(board, i, j) == 0)
      board_set(board, i, j, new_num);
    else
      dup = 1;
  }
  return 0;
}

/**
 * @deprecated Use board_create and board_setup instead.
 */
void numberInit(int numbers[][4]) {
  for (int j = 0; j < 4; j++)
    for (int i = 0; i < 4; i++)
      numbers[i][j] = 0;

  if (testMode) {
    for (int j = 0; j < 4; j++)
      for (int i = 0; i < 4; i++)
        numbers[i][j] = (int)pow(2.00, (double)i + (double)j * 4 + 1);

    numbers[3][3] = 0;
  } else {
    addBlocks(numbers);
  }
}

void game2048() {
  int score = 0;
  int highestScore = readHighestScore();

  int end;

  Board *board = board_create();
  board_setup(board, testMode);

  int blockNumbers[4][4] = {0};
  board_cast(board, blockNumbers);
  board_destroy(board);

  int quit = 0;
  int surequit = 0;

  do {
    int command;
    printBlocks(blockNumbers, score, highestScore);

    if (testMode)
      command = CMD_D;
    else
      command = waitGameKeyDown();

    if (command == CMD_Q) {
      showQuitCheck();
      surequit = waitDigitKeyDown(0, 1);

      if (surequit == 1) {
        end = 1;
        quit = 1;
      } else {
        end = 0;
        quit = 0;
      }
    }

    if (!surequit) {
      int addNumber = 0, moveNumber = 0;

      for (int i = 0; i < 4; i++) {
        if (i == 2)
          addNumber += addUpBlocks(blockNumbers, command, &score);
        else
          moveNumber += moveBlocks(blockNumbers, command);
      }
      while ((addNumber + moveNumber) != 0) {
        addBlocks(blockNumbers);
        addNumber = 0, moveNumber = 0;
      }

      if (command != 0)
        end = testIfEnd(blockNumbers);
    }

  } while (!end);

  printBlocks(blockNumbers, score, highestScore);

  if (!testMode && !quit)
    saveScore(score);
}

void setMode(int mode, int *up, int *down, int *left, int *right) {
  *up = *down = *left = *right = 0;
  switch (mode) {
  case (MOVE_UP):
    *up = 1;
    break;
  case (MOVE_DOWN):
    *down = 1;
    break;
  case (MOVE_LEFT):
    *left = 1;
    break;
  case (MOVE_RIGHT):
    *right = 1;
    break;
  default:
    break;
  }
}