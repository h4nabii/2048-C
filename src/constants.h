#pragma once

#define BOARD_SIZE 4

typedef enum {
  COMMAND_MOVE_UP = 1,
  COMMAND_MOVE_LEFT = 2,
  COMMAND_MOVE_DOWN = 3,
  COMMAND_MOVE_RIGHT = 4,
  COMMAND_QUIT = 0
} MoveDirection;
