#define _CRT_SECURE_NO_WARNINGS

#include "common.h"
#include "struct.h"
#include "gameData.h"
#include <string.h>

extern int currentDifficulty;

void Goto(int x, int y) {
    COORD pos = { x, y };

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void SetConsoleSize(int col, int lines) {
    char setText[100];
    sprintf(setText, "mode con cols=%d lines=%d", col, lines);
    system(setText);
}

void RemoveCursor(void) {
    CONSOLE_CURSOR_INFO curInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
    curInfo.bVisible = 0;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

void setColor(unsigned short text) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text);
}

void showMenu() {
    system("cls");
    printf("\t일감호 아래 보물을 찾아라!\n\n");
    Sleep(1000);
    printf("========================================\n\n");
    printf("1. 게임 시작\n");
    printf("2. 기록표\n");
    printf("3. 게임 방법\n");
    printf("4. 게임 종료\n");
    printf("========================================\n\n");
}

void showRanking(record* recordp, int count) {
    // 구조체 배열 포인터 인자로 받음
    //record sorted_record[1000];
    system("cls");
    // record 구조체 내 time 비교로 최솟값부터 오름차순 정렬
    printf("\t일감호 아래 보물을 찾아라!\n");
    Sleep(100);
    short minimum, i, last;
    if (count == 1) {
        printf("========================================\n\n");
        printf("\t닉네임 : %s\n\n", recordp[0].user);
        switch (recordp[0].level) {
        case 0:
            printf("\t난이도 : 초급\n\n");
            break;
        case 1:
            printf("\t난이도 : 중급\n\n");
            break;
        case 2:
            printf("\t난이도 : 고급\n\n");
            break;
        }
        printf("\t점수 : %d\n\n", recordp[0].time);
    }
    else if (count == 0) {
        printf("========================================\n\n\t기록이 존재하지 않습니다!\n\n");
    }
    else {
        for (int i = 0; i < count; ++i) {
            printf("========================================\n\n");
            printf("\t닉네임 : %s\n\n", recordp[i].user);
            switch (recordp[i].level) {
            case 0:
                printf("\t난이도 : 초급\n\n");
                break;
            case 1:
                printf("\t난이도 : 중급\n\n");
                break;
            case 2:
                printf("\t난이도 : 고급\n\n");
                break;
            }
            printf("\t점수 : %d\n\n", recordp[i].time);
        }
    }


    printf("========================================\n");
    printf("메뉴 나가기\t");
    printf("←");
}


void showStartScreen() {
    char story[] = "건국대학교 22학번 신입생으로 입학한 당신.\n당신은 우연히 일감호 어딘가에 보물이 숨겨져 있다는 사실을 알게 됩니다.\n과연 당신은 제한시간 내에 보물을 찾을 수 있을까요?";
    int length = strlen(story);
    int i;
    for (i = 0; i <= length; i++) //스토리 한 글자씩 출력
    {
        printf("%c", story[i]);
        Sleep(50);
    }
    Sleep(1500);
    system("cls");
    printf("\n");
    setColor(GREEN);
    SetConsoleSize(124, 35);
    printf("###########################################################################################################################\n");
    printf("#                                                                                                                         #\n");
    printf("#                                                                                                                         #\n");
    printf("#                                                                                                                         #\n");
    printf("#    ###    #    #####    #         #              ###   #     #####  # #                                                 #\n");
    printf("#   #   #   #        #    #      #######          #   #  #         #  # #                                                 #\n");
    printf("#   #   #   #        #    #        # #            #   #  ###   #####  ###                                                 #\n");
    printf("#    ###    #        #    ####    #   #            ###   #     #      # #                                                 #\n");
    printf("#           #       #     #        ###                   #     #####  # #                                                 #\n");
    printf("#     #####                         #                    #            # #                                                 #\n");
    printf("#         #         #######      #######                                                                                  #\n");
    printf("#     #####         #     #                                                                                               #\n");
    printf("#     #             #     #                                                                                               #\n");
    printf("#     #####         #######            #   #      #####       ###          ##    #      ###    #     #####  #      ###    #\n");
    printf("#                                      #####      #   #      #   #        ####   #     #   #   #         #  #      ###    #\n");
    printf("#                                      #   #      #   #      #   #         ##    ###   #   #   ###   #####  ###    ###    #\n");
    printf("#                                      #####      #####       ###         #  #   #      ###    #     #      #      ##     #\n");
    printf("#                                        #                                                     #     #####  #      ##     #\n");
    printf("#                                        #       #######    #######         #####              #            #      #      #\n");
    printf("#                                     #######       #                         #                                           #\n");
    printf("#                                                 #####      #####           # #                                          #\n");
    printf("#                                                     #          #          #   #                                  ##     #\n");
    printf("#                                                 #####      #####                                                        #\n");
    printf("#                                                 #          #                                                            #\n");
    printf("#                                                 #####      #####                                                        #\n");
    printf("#                                                                                                                         #\n");
    printf("#                                                                                                                         #\n");
    printf("#                                                                                                                         #\n");
    printf("#");
    setColor(WHITE);
    printf("\t\t\t\t\t★  시작하려면 아무 키나 누르세요  ★                                             ");
    setColor(GREEN);
    printf("#\n");
    printf("#                                                                                                                         #\n");
    printf("#                                                                                                                         #\n");
    printf("#                                                                                                                         #\n");
    printf("#                                                                                                                         #\n");
    printf("###########################################################################################################################");
    setColor(WHITE);
    getch();
    system("cls");
}

void showDifficultyMenu() {
    system("cls");
    printf("\t난이도를 선택하세요\n\n");
    printf("========================================\n\n");
    printf("\t초급 \n\n\t중급 \n\n\t고급 \n\n");
    printf("========================================\n\n");
}

void showEndGameMenu(char difficulty, int time) {
    char level[10];

    printf("========================================\n\n");
    switch (difficulty) {
    case 0: // EASY
        strcpy(level, "쉬움");
        break;
    case 1: // COMMON
        strcpy(level, "보통");
        break;
    case 2: // HARD
        strcpy(level, "어려움");
        break;
    }
    printf("\t난이도 : %s\n\t플레이 시간 : %d\n\n", level, time);
    if (currentDifficulty < 2) printf("다음 단계로 넘어가시겠습니까?\n========================================\n");
    else printf("다시 시작하시겠습니까?\n========================================\n");

    printf("예\t\t아니오");
    Goto(4, 10);
    printf("←");
}

void showGameOverMenu() {
    printf("다시 시작하시겠습니까?\n========================================\n");
    printf("예\t\t아니오");
    Goto(4, 2);
    printf("←");
}

void showGameInfo() {
    system("cls");
    printf("\t일감호 아래 보물을 찾아라!\n\n");
    printf("========================================\n\n");
    printf("≫ 플레이어를 방향키를 이용해 이동시켜 제한 시간내 보물을 모두 찾는 게임입니다.\n");
    printf("≫ 깃발을 획득하면 각종 버프/디버프중 하나가 적용됩니다.\n\t버프 : 「보물 하나 보이기」 / 「제한 시간 추가(15초)」/ 「방어막 1개 추가(디버프 깃발 획득시 자동 사용)」\n\t디버프 : 「플레이어 처음 위치로 이동」 / 「제한 시간 감소(15초)」 / 「속박(5초)」 / 「방향키 반전(5초)」/ 「즉시 게임오버」\n");
    printf("\t버프 : 「보물 하나 보이기」\n");
    printf("\t       「제한 시간 추가(15초)」\n");
    printf("\t       「방어막 1개 추가(디버프 깃발 획득시, 건덕이와 충돌 시 자동 사용)」\n");
    printf("\t디버프 : 「플레이어 처음 위치로 이동」\n");
    printf("\t         「제한 시간 감소(15초)」\n");
    printf("\t         「속박(5초)」\n");
    printf("\t         「방향키 반전(5초)」\n");
    printf("\t         「즉시 게임오버」\n");
    printf("≫ 고급 단계에서는 건덕이가 출몰합니다.");
    printf("≫ 제한 시간 초과, 게임오버 깃발 획득, 건덕이와 충돌시 게임 실패됩니다.\n");
    printf("========================================\n=\n");
    printf("메뉴 나가기\t");
    printf("←");
}