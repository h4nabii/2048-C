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
  // Set the random seed and initialize the screen and file system
  srand((unsigned int)time(NULL));
  initStoragePaths();
  screenInit();
  fileInit();
}

int main() {
  init();
  runHome();
  return 0;
}
