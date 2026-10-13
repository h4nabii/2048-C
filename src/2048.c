/*
    GAME2048
    version 4
    2048.cpp
*/

#include <direct.h>
#include <time.h>

#include "public/data.h"
#include "public/screen.h"

#include "main.h"

// Initial the program
void init() {
  // Set the random seed and initialize the screen, input and file system
  srand((unsigned int)time(NULL));
  initStoragePaths();
  screen_init();
  input_init();
  fileInit();
}

int main() {
  init();
  runHome();
  leave_alternate_screen();
  return 0;
}
