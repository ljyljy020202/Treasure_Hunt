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
    printf("\t�ϰ�ȣ �Ʒ� ������ ã�ƶ�!\n\n");
    Sleep(1000);
    printf("========================================\n\n");
    printf("1. ���� ����\n");
    printf("2. ���ǥ\n");
    printf("3. ���� ���\n");
    printf("4. ���� ����\n");
    printf("========================================\n\n");
}

void showRanking(record* recordp, int count) {
    // ����ü �迭 ������ ���ڷ� ����
    //record sorted_record[1000];
    system("cls");
    // record ����ü �� time �񱳷� �ּڰ����� �������� ����
    printf("\t�ϰ�ȣ �Ʒ� ������ ã�ƶ�!\n");
    Sleep(100);
    short minimum, i, last;
    if (count == 1) {
        printf("========================================\n\n");
        printf("\t�г��� : %s\n\n", recordp[0].user);
        switch (recordp[0].level) {
        case 0:
            printf("\t���̵� : �ʱ�\n\n");
            break;
        case 1:
            printf("\t���̵� : �߱�\n\n");
            break;
        case 2:
            printf("\t���̵� : ���\n\n");
            break;
        }
        printf("\t���� : %d\n\n", recordp[0].time);
    }
    else if (count == 0) {
        printf("========================================\n\n\t����� �������� �ʽ��ϴ�!\n\n");
    }
    else {
        for (int i = 0; i < count; ++i) {
            printf("========================================\n\n");
            printf("\t�г��� : %s\n\n", recordp[i].user);
            switch (recordp[i].level) {
            case 0:
                printf("\t���̵� : �ʱ�\n\n");
                break;
            case 1:
                printf("\t���̵� : �߱�\n\n");
                break;
            case 2:
                printf("\t���̵� : ���\n\n");
                break;
            }
            printf("\t���� : %d\n\n", recordp[i].time);
        }
    }


    printf("========================================\n");
    printf("�޴� ������\t");
    printf("��");
}


void showStartScreen() {
    char story[] = "�Ǳ����б� 22�й� ���Ի����� ������ ���.\n����� �쿬�� �ϰ�ȣ ��򰡿� ������ ������ �ִٴ� ����� �˰� �˴ϴ�.\n���� ����� ���ѽð� ���� ������ ã�� �� �������?";
    int length = strlen(story);
    int i;
    for (i = 0; i <= length; i++) //���丮 �� ���ھ� ���
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
    printf("\t\t\t\t\t��  �����Ϸ��� �ƹ� Ű�� ��������  ��                                             ");
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
    printf("\t���̵��� �����ϼ���\n\n");
    printf("========================================\n\n");
    printf("\t�ʱ� \n\n\t�߱� \n\n\t��� \n\n");
    printf("========================================\n\n");
}

void showEndGameMenu(char difficulty, int time) {
    char level[10];

    printf("========================================\n\n");
    switch (difficulty) {
    case 0: // EASY
        strcpy(level, "����");
        break;
    case 1: // COMMON
        strcpy(level, "����");
        break;
    case 2: // HARD
        strcpy(level, "�����");
        break;
    }
    printf("\t���̵� : %s\n\t�÷��� �ð� : %d\n\n", level, time);
    if (currentDifficulty < 2) printf("���� �ܰ�� �Ѿ�ðڽ��ϱ�?\n========================================\n");
    else printf("�ٽ� �����Ͻðڽ��ϱ�?\n========================================\n");

    printf("��\t\t�ƴϿ�");
    Goto(4, 10);
    printf("��");
}

void showGameOverMenu() {
    printf("�ٽ� �����Ͻðڽ��ϱ�?\n========================================\n");
    printf("��\t\t�ƴϿ�");
    Goto(4, 2);
    printf("��");
}

void showGameInfo() {
    system("cls");
    printf("\t�ϰ�ȣ �Ʒ� ������ ã�ƶ�!\n\n");
    printf("========================================\n\n");
    printf("�� �÷��̾ ����Ű�� �̿��� �̵����� ���� �ð��� ������ ��� ã�� �����Դϴ�.\n");
    printf("�� ����� ȹ���ϸ� ���� ����/������� �ϳ��� ����˴ϴ�.\n\t���� : ������ �ϳ� ���̱⡹ / ������ �ð� �߰�(15��)��/ ���� 1�� �߰�(����� ��� ȹ��� �ڵ� ���)��\n\t����� : ���÷��̾� ó�� ��ġ�� �̵��� / ������ �ð� ����(15��)�� / ���ӹ�(5��)�� / ������Ű ����(5��)��/ ����� ���ӿ�����\n");
    printf("\t���� : ������ �ϳ� ���̱⡹\n");
    printf("\t       ������ �ð� �߰�(15��)��\n");
    printf("\t       ���� 1�� �߰�(����� ��� ȹ���, �Ǵ��̿� �浹 �� �ڵ� ���)��\n");
    printf("\t����� : ���÷��̾� ó�� ��ġ�� �̵���\n");
    printf("\t         ������ �ð� ����(15��)��\n");
    printf("\t         ���ӹ�(5��)��\n");
    printf("\t         ������Ű ����(5��)��\n");
    printf("\t         ����� ���ӿ�����\n");
    printf("�� ��� �ܰ迡���� �Ǵ��̰� ����մϴ�.");
    printf("�� ���� �ð� �ʰ�, ���ӿ��� ��� ȹ��, �Ǵ��̿� �浹�� ���� ���е˴ϴ�.\n");
    printf("========================================\n=\n");
    printf("�޴� ������\t");
    printf("��");
}