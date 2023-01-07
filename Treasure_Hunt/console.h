#ifndef __CONSOLE_H__
#define __CONSOLE_H__
#include "struct.h"

void Goto(int x, int y);
void SetConsoleSize(int col, int lines);
void RemoveCursor(void);
void showGameStage(char** stage, int width, int height);
void showStartScreen();
void showMenu();
void showDifficultyMenu();
void showRanking(record* recordp, int count);
void showEndGameMenu(char difficulty, int time);
void showGameInfo();
void showGameOverMenu();

#endif