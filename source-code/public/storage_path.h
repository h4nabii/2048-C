#pragma once
#include <windows.h>

// 资源文件与文件夹的绝对路径（与 exe 同级）
struct StoragePath {
  char testDir[MAX_PATH];       // <exeDir>\TEST
  char testMark[MAX_PATH];      // <exeDir>\TEST\HaveDone.txt
  char saveDir[MAX_PATH];       // <exeDir>\SAVE
  char gameSaveDir[MAX_PATH];   // <exeDir>\SAVE\GAME_SAVE
  char scoreDir[MAX_PATH];      // <exeDir>\SAVE\SCORE
  char score[MAX_PATH];         // <exeDir>\SAVE\SCORE\score.txt
  char highestScore[MAX_PATH];  // <exeDir>\SAVE\SCORE\highest score.txt
  char screenDir[MAX_PATH];     // <exeDir>\SCREEN
  char styleDir[MAX_PATH];      // <exeDir>\SCREEN\STYLE
  char controlWayDir[MAX_PATH]; // <exeDir>\SCREEN\CONTROL_WAY
};

// 全局路径表，由 initStoragePaths() 填充
struct StoragePath storagePaths;

// 拼接 base\sub 到 out
static void joinPath(char *out, const char *base, const char *sub) {
  strcpy_s(out, MAX_PATH, base);
  strcat_s(out, MAX_PATH, "\\");
  strcat_s(out, MAX_PATH, sub);
}

// 取 exe 所在目录填充路径表，程序启动时调用一次
void initStoragePaths() {
  char exeDir[MAX_PATH];
  GetModuleFileNameA(NULL, exeDir, MAX_PATH);

  // 去掉文件名，只留目录
  char *fileName = strrchr(exeDir, '\\');
  if (fileName)
    *fileName = '\0';

  joinPath(storagePaths.testDir, exeDir, "TEST");
  joinPath(storagePaths.testMark, storagePaths.testDir, "HaveDone.txt");
  joinPath(storagePaths.saveDir, exeDir, "SAVE");
  joinPath(storagePaths.gameSaveDir, storagePaths.saveDir, "GAME_SAVE");
  joinPath(storagePaths.scoreDir, storagePaths.saveDir, "SCORE");
  joinPath(storagePaths.score, storagePaths.scoreDir, "score.txt");
  joinPath(storagePaths.highestScore, storagePaths.scoreDir, "highest score.txt");
  joinPath(storagePaths.screenDir, exeDir, "SCREEN");
  joinPath(storagePaths.styleDir, storagePaths.screenDir, "STYLE");
  joinPath(storagePaths.controlWayDir, storagePaths.screenDir, "CONTROL_WAY");
}