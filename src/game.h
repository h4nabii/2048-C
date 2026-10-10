#include <stdio.h>
#include <windows.h>

#include "board/board.h"
#include "constants.h"
#include "public/data.h"
#include "public/global.h"
#include "public/input.h"
#include "public/screen.h"

// ======================================
// 游戏相关函数声明
// ======================================

void game2048();           // 游戏主函数
int testIfEnd(int N[][4]); // 测试结束
void setMode(int mode, int *up, int *down, int *left, int *right);

// 测试结束
// TODO：1. 实现 board_can_merge，用于判断棋盘是否无法合并，结合 board_is_full，优化 testIfEnd 函数
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

void game2048() {
  int score = 0;
  int highestScore = readHighestScore();

  int end;

  Board *board = board_create(BOARD_SIZE, BOARD_SIZE);
  board_setup(board, testMode);

  int blockNumbers[4][4] = {0};
  board_cast(board, blockNumbers);

  int quit = 0;
  int surequit = 0;

  do {
    MoveDirection command;
    printBlocks(blockNumbers, score, highestScore);

    if (testMode)
      command = COMMAND_MOVE_RIGHT;
    else
      command = wait_game_key_down();

    if (command == COMMAND_QUIT) {
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
      // int addNumber = 0, moveNumber = 0;

      int move_count = 0;
      move_count += board_move_all(board, command);
      int merge_count = board_merge_all(board, command);
      score += merge_count;
      move_count += board_move_all(board, command);

      if (move_count > 0 || merge_count > 0)
        board_random_add(board);

      board_cast(board, blockNumbers);

      if (command != 0)
        end = testIfEnd(blockNumbers);
    }

  } while (!end);

  printBlocks(blockNumbers, score, highestScore);

  if (!testMode && !quit)
    saveScore(score);

  board_destroy(board);
}

void setMode(int mode, int *up, int *down, int *left, int *right) {
  *up = *down = *left = *right = 0;
  switch (mode) {
  case (COMMAND_MOVE_UP):
    *up = 1;
    break;
  case (COMMAND_MOVE_DOWN):
    *down = 1;
    break;
  case (COMMAND_MOVE_LEFT):
    *left = 1;
    break;
  case (COMMAND_MOVE_RIGHT):
    *right = 1;
    break;
  default:
    break;
  }
}