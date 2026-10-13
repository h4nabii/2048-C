#pragma once
#include "constants.h"
#include <windows.h>

// 每帧最多等待的毫秒数：没有输入时循环也按这个节奏醒来
#define FRAME_MS 16

// poll_key 的特殊返回：无输入 / 窗口尺寸变化（与按键字符区分开）
#define KEY_NONE (-1)
#define KEY_RESIZE (-2)

// 关闭行缓冲与快速编辑，并确保窗口尺寸变化会作为输入事件送达
void input_init() {
  HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
  DWORD mode;

  if (!GetConsoleMode(hIn, &mode))
    return;

  mode &= ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT | ENABLE_QUICK_EDIT_MODE);
  mode |= ENABLE_EXTENDED_FLAGS | ENABLE_PROCESSED_INPUT | ENABLE_WINDOW_INPUT;
  SetConsoleMode(hIn, mode);
}

// 取一个输入事件：最多等 timeout_ms 毫秒。按键返回其字符，窗口尺寸变化返回 KEY_RESIZE，无输入返回 KEY_NONE
int poll_key(int timeout_ms) {
  HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
  INPUT_RECORD rec;
  DWORD read, queued;

  switch (WaitForSingleObject(hIn, timeout_ms)) {
  case WAIT_OBJECT_0:
    break;
  case WAIT_TIMEOUT:
    return KEY_NONE;
  default:
    Sleep(timeout_ms); // 没有控制台，别空转烧 CPU
    return KEY_NONE;
  }

  // 一次只取一个事件，其余留给下一帧：按键不会丢，顺序也不乱
  while (GetNumberOfConsoleInputEvents(hIn, &queued) && queued > 0) {
    if (!ReadConsoleInputA(hIn, &rec, 1, &read) || read != 1)
      break;

    if (rec.EventType == WINDOW_BUFFER_SIZE_EVENT)
      return KEY_RESIZE;

    if (rec.EventType == KEY_EVENT && rec.Event.KeyEvent.bKeyDown && rec.Event.KeyEvent.uChar.AsciiChar != 0)
      return (unsigned char)rec.Event.KeyEvent.uChar.AsciiChar;
  }

  return KEY_NONE;
}

// 等一个 [start, end] 范围内的数字键；等待期间窗口尺寸变化则调用 redraw（可为 NULL）重绘
int waitDigitKeyDown(int start, int end, void (*redraw)(void)) {
  for (;;) {
    int key = poll_key(FRAME_MS);

    if (key == KEY_RESIZE) {
      if (redraw)
        redraw();
    } else if (key >= '0' && key <= '9') {
      int digit = key - '0';

      if (start <= digit && digit <= end)
        return digit;
    }
  }
}

// 是否游戏指令键
int is_game_key(int key) { return key == 'w' || key == 'a' || key == 's' || key == 'd' || key == 'q'; }

// 游戏指令键翻译成指令
MoveDirection key_to_command(int key) {
  switch (key) {
  case 'w':
    return COMMAND_MOVE_UP;
  case 's':
    return COMMAND_MOVE_DOWN;
  case 'a':
    return COMMAND_MOVE_LEFT;
  case 'd':
    return COMMAND_MOVE_RIGHT;
  }

  return COMMAND_QUIT; // 调用前已由 is_game_key 过滤，这里只剩 'q'
}
