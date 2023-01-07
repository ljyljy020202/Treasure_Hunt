#define _CRT_SECURE_NO_WARNINGS
#include "function.h"

int main() {
	char end = 0;

	startScreen();

	while (1) {
		end = menu();
		switch (end) {
		case 1:
			selectDifficulty();
			while (1) {
				while (1) {
					end = gameStage();
					if (end == 0)
						break;
					else if (end == 1)
						break;
				}
				if (end == 0)
					break;
			}
			break;
		case 2:
			ranking();
			break;
		case 3:
			gameInfo();
			break;
		case 4:
			end = quitGame();
			break;
		}
		if (end == 4)
			break;
	}
}