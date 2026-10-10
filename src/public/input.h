#pragma once
#include "constants.h"
#include <conio.h>

// wait digit input
int waitDigitKeyDown(int start, int end) {
  int input;
  while (input = _getch()) {
    input -= '0';
    if ((start <= input) && (input <= end))
      return input;
  }
  return -1;
}

// wait game command
MoveDirection wait_game_key_down() {
  int input;
  do {
    input = _getch();
  } while ((input != 'w') && (input != 's') && (input != 'a') && (input != 'd') && (input != 'q'));

  switch (input) {
  case ('w'):
    return COMMAND_MOVE_UP;
  case ('s'):
    return COMMAND_MOVE_DOWN;
  case ('a'):
    return COMMAND_MOVE_LEFT;
  case ('d'):
    return COMMAND_MOVE_RIGHT;
  case ('q'):
  default:
    return COMMAND_QUIT;
  }
}