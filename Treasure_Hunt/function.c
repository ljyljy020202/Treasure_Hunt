#define _CRT_SECURE_NO_WARNINGS

#include "common.h"
#include "console.h"
#include "gameData.h"
#include "struct.h"
#include "function.h"

#define MAX_BLOCK_NUM 10
#define MAX_FLAG_NUM 10
#define MAX_KON_DUCK_MOVE 10
#define HIGH_LEVEL_MAP_SIZE 50
#define MID_LEVEL_MAP_SIZE 40
#define LOW_LEVEL_MAP_SIZE 30
#define START_CONS_WIDTH 40
#define START_CONS_HEIGHT 25
#define STATE_WIN_WIDTH 20
//#define TIME_LIMIT_SEC 60
#define FPS 60
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define START_X 2
#define START_Y 2

#define LOW_LEVEL_ROL 1
#define LOW_LEVEL_PLU 1
#define LOW_LEVEL_MIN 1
#define MID_LEVEL_GAM 1
#define MID_LEVEL_SPE 1
#define MID_LEVEL_REV 1
#define MID_LEVEL_SHI 1

char stage[HIGH_LEVEL_MAP_SIZE][HIGH_LEVEL_MAP_SIZE];
//init
int blocksNum = 10;
int flagsNum = 5;
//setDifficulty
char currentDifficulty; // 0 = EASY, 1 = COMMON, 2 = HARD
//Record
int RecordCount = 0;
char running = 1;
//currentDifficulty랑 중복, 하나 삭제 요함
char currentLevel;
char is_reverse = 0;
char is_stop = 0;
char shield = 0; // 디버프 아이템 혹은 건덕이를 막을 수 있는 방어막 개수
//디폴트 시간제한 60초
int time_limit_sec = 60;
int size;
int is_success;
short stop_time = 0, reverse_time = 0;
char is_timeset, plmitime; // 시간 추가시 출력 위한 변수
char is_rollback, rollback_time; // 시간 추가시 출력 위한 변수

double gameTime;

record records[1000];
player P;
konDuck duck1 = { 25, 25 };
konDuck duck2 = { 26, 26 };
konDuck duck3 = { 27, 27 };

int count = 30;

void gameLoop() {
    processkey();
    spawn_konduck();
    checkPlayerState();
}

char gameStage() {
    long end;
    long last;

    gameTime = 0;


    initGameStage(); // 블럭, 플레이어, 플래그, 건덕 초기화

    //게임 루프
    //시간을 입력받아 1/FPS 초마다 게임을 업데이트 (FPS = 초당 60 프레임)
    //running이 0이면 종료
    last = clock();
    while (running) {
        end = clock();
        if (end - last >= 1000 / FPS) {
            gameLoop();
            gameTime += end - last;
            last = end;
            if (gameTime > time_limit_sec * 1000) {
                running = 0;
                is_success = 0;
            }
        }
    }
    return endGameMenu((int)(gameTime / 10)); // 시간이 곧 점수이므로, * 8.5 곱하겠음
}

void initGameStage() {
    // 매 게임 마다 초기화
    running = 1;
    is_reverse = 0;
    is_stop = 0;
    shield = 0;
    is_success = 0;
    stop_time = 0;
    reverse_time = 0;
    //디폴트 시간제한 60초
    char sum = blocksNum + flagsNum;

    char x[25] = { 0, };
    char y[25] = { 0, };

    int i, j;

    int blocksNum;

    //0: TRE, 1: ROL, 2: PLU, 3: MIN, 4: GAM, 5: SPE, 6: REV, 7:SHI
    int flag[8] = { 1, LOW_LEVEL_ROL, LOW_LEVEL_PLU, LOW_LEVEL_MIN, };


    srand(time(NULL));
    system("cls");

    if (currentDifficulty == 0) {
        blocksNum = MAX_BLOCK_NUM;

        size = LOW_LEVEL_MAP_SIZE;
    }
    else if (currentDifficulty == 1) {
        blocksNum = MAX_BLOCK_NUM;
        flag[4] = MID_LEVEL_GAM;
        flag[5] = MID_LEVEL_SPE;
        flag[6] = MID_LEVEL_REV;
        flag[7] = MID_LEVEL_SHI;

        size = MID_LEVEL_MAP_SIZE;
    }
    else {
        blocksNum = MAX_BLOCK_NUM;
        flag[4] = MID_LEVEL_GAM;
        flag[5] = MID_LEVEL_SPE;
        flag[6] = MID_LEVEL_REV;
        flag[7] = MID_LEVEL_SHI;

        size = HIGH_LEVEL_MAP_SIZE;
    }

    SetConsoleSize(2 * (size + STATE_WIN_WIDTH), size);

    for (i = 0; i < sum; i++) {
        y[i] = rand() % (size - 3) + 1;
        x[i] = rand() % (size - 3) + 1;
        if ((x[i] != 1) && (y[i] != 1) || (x[i] != 25) && (y[i] != 25) || (x[i] != 26) && (y[i] != 26) ||
            (x[i] != 27) && (y[i] != 27)) {
            for (j = 0; j < i; j++) {  //중복은 없으므로 중복 제거를 위한 포문
                if (y[i] == y[j]) {
                    if (x[i] == x[j]) {
                        i--;  //중복이 발견될 경우 i번째 숫자를 다시 뽑는다.
                        break;
                    }
                }
            }
        }
        else {
            i--;
        }
    }


    stage[START_X][START_Y] = PLAYER;
    P.x = START_X;
    P.y = START_Y;
    Goto(2 * START_X, START_Y);
    printf("◆");

    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++)
            stage[i][j] = BLANK;
    }

    for (i = 0; i < size; i++) {
        stage[i][0] = BLOCK;
        stage[i][size - 1] = BLOCK;
    }

    for (i = 0; i < size; i++) {
        stage[0][i] = BLOCK;
        stage[size - 1][i] = BLOCK;
    }

    for (i = 0; i < blocksNum; i++) {
        stage[x[i]][y[i]] = BLOCK;
    }

    for (i = blocksNum; i < blocksNum + flagsNum; i++) {
        stage[x[i]][y[i]] = rand() % (FLAG_SHIELD - FLAG_TREASURE) + FLAG_ROLLBACK; // 보물 제외 깃발 랜덤 설정
    }

    i = rand() % (size - 3) + 1;
    j = rand() % (size - 3) + 1;
    stage[i][j] = FLAG_TREASURE; // 랜덤 위치에 보물 1개만 설정

    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            if (stage[i][j] != BLANK) {
                if (stage[i][j] == BLOCK) {
                    Goto(2 * i, j);
                    printf("■");
                }
                else if ((stage[i][j] >= FLAG_TREASURE) && (stage[i][j] <= FLAG_SHIELD)) {
                    Goto(2 * i, j);
                    // printf("%d", stage[i][j]);
                    printf("▶"); //시연시 이 줄 주석 해제후 바로 윗 줄 주석처리하세요.
                }
            }
        }
    }
}

void gameInfo() {
    short ch;
    showGameInfo();

    ch = _getch();
    if (ch == '\r') {
        //버퍼 '\n' 지우기
        fflush(stdin);
        return;
    }
}


char menu() {
    short ch;
    char cursor_pos = 1, x = 20, y = 4;
    showMenu();
    Goto(x, y);
    printf("←");
    while (1) {
        // 게임 시작==1, 랭킹표==2, 게임 방법==3, 게임 종료==4
        if (_kbhit()) {
            ch = _getch();
            if (ch == 224) {
                ch = _getch();
                switch (ch) {
                case UP:
                    if (cursor_pos > 1) {
                        y--;
                        cursor_pos--;
                        printf("\b\b  ");
                        Goto(x, y);
                        printf("←");
                    }
                    break;

                case DOWN:
                    if (cursor_pos < 4) {
                        y++;
                        cursor_pos++;
                        printf("\b\b  ");
                        Goto(x, y);
                        printf("←");
                    }
                    break;
                }
            }

            //window에서 엔터키는 '\n'이 아니라 '\r\n'입니다.
            if (ch == '\r') {
                //버퍼 '\n' 지우기
                fflush(stdin);
                return cursor_pos;
            }
        }
    }
}

void ranking() {
    short ch;
    showRanking(records, RecordCount); // 구조체 배열 포인터로 넘김
    while (1) {
        if ((ch = _getch()) == '\r') {
            rewind(stdin);
            break;
        }
    }
}


char endGameMenu(int elapsed_time) {
    // 닉네임 입력 받기 - DONE
    // 랭킹 기록하기 - DONE
    // showEndGameMenu 인자로 난이도, 점수, 플레이 시간, 닉네임 전달 - DONE
    char nickname[100];
    short ch, x = 10, y = 10;
    char cursor_pos = 1; // 1 == 예, 0 == 아니오
    char buffer[2000] = { 0 };
    system("cls");
    if (is_success) { // 성공 여부에 따라 출력 다름
        SetConsoleSize(110, START_CONS_HEIGHT);
        for (int i = 0; i < 5; ++i) {
            FILE* fp = fopen("success.txt", "r");
            fread(buffer, 1, 2000, fp);
            printf("%s", buffer);
            fclose(fp);
            memset(buffer, 0, sizeof(buffer));
            Sleep(500);
            system("cls");
            Sleep(500);
        }
        SetConsoleSize(2 * START_CONS_WIDTH, START_CONS_HEIGHT);
        printf("========================================\n\n");
        printf("닉네임 입력 (30자 이내) : \n");
        printf("========================================\n");
        Goto(26, 2);
        gets_s(nickname, 100);
        rewind(stdin);
        strcpy(records[RecordCount].user, nickname);
        records[RecordCount].time = elapsed_time;
        records[RecordCount].level = currentDifficulty;
        ++RecordCount;
        showEndGameMenu(currentDifficulty, elapsed_time);
    }
    else {
        for (int i = 0; i < 5; ++i) {
            FILE* fp = fopen("gameover.txt", "r");
            fread(buffer, 1, 2000, fp);
            printf("%s", buffer);
            fclose(fp);
            memset(buffer, 0, sizeof(buffer));
            Sleep(500);
            system("cls");
            Sleep(500);
        }
        SetConsoleSize(2 * START_CONS_WIDTH, START_CONS_HEIGHT);
        showGameOverMenu();
        y = 2;
    }

    while (1) { // EndGameMenu 예 아니오 선택용 while문
        ch = _getch();
        if (ch == 224) {
            ch = _getch();
            switch (ch) {

            case LEFT:
                if (cursor_pos != 1) {
                    x = 4;
                    cursor_pos = 1;
                }
                break;

            case RIGHT:
                if (cursor_pos != 0) {
                    x = 25;
                    cursor_pos = 0;
                }
                break;
            }
        }
        printf("\b\b  ");
        Goto(x, y);
        printf("←");
        // main.c 0 == while loop 종료후 메인 메뉴로 돌아감, 1 == while loop 종료후 난이도 선택으로 돌아감
        if (ch == '\r') {
            if (is_success && cursor_pos) {
                if (currentDifficulty < 2) currentDifficulty++;
            }
            rewind(stdin);
            return cursor_pos;
        }
    }
}


void startScreen() {
    RemoveCursor();
    showStartScreen();
    SetConsoleSize(2 * START_CONS_WIDTH, START_CONS_HEIGHT);
}

void selectDifficulty() {
    short ch;
    char cursor_pos = 0, x = 4, y = 4; //화살표 위치 - 초급: 1, 중급: 2, 고급: 3
    showDifficultyMenu();
    Goto(x, y);
    while (1) {

        printf("\b\b  ");
        Goto(x, y);
        printf("→");

        ch = _getch();
        if (ch == 224) {
            ch = _getch();
            switch (ch) {

            case UP:
                if (cursor_pos > 0) {
                    y -= 2;
                    cursor_pos--;
                }
                break;

            case DOWN:
                if (cursor_pos < 2) {
                    y += 2;
                    cursor_pos++;
                }
                break;
            }
        }
        //menu 탈출과 동일
        else if (ch == '\r') {
            fflush(stdin);
            currentDifficulty = cursor_pos;
            return;
        }
    }
}

void processkey() // 방향키 값을 받고, 벽이나 블럭에 부딪히지 않았을 때 맵 상의 플레이어 위치를 변경(출력은 맵과 함께)
{
    short ch, mapnum; //mapnum은 stage 배열에 저장된 맵 값을 저장
    int _x = 0, _y = 0; //좌표 이동 값
    if (_kbhit() && (count >= 10)) { //게임루프 30번에 한 번씩 이동
        ch = _getch();
        if (ch == 224) {
            ch = _getch();
            switch (ch) {
            case UP:
                _y = -1 + is_reverse * 2;
                break;
            case DOWN:
                _y = 1 - is_reverse * 2;
                break;
            case LEFT:
                _x = -1 + is_reverse * 2;
                break;
            case RIGHT:
                _x = 1 - is_reverse * 2;
                break;
            default:
                break;
            }

            //속박이면 움직임 없음
            if (is_stop) {
                _x = 0;
                _y = 0;
            }

            mapnum = stage[P.x + _x][P.y + _y];
            if (mapnum != BLOCK) {
                //빈칸일 때만 P의 좌표 재설정, 배열상의 위치에 해당하는 값 변경
                //->BLOCK이 아니면 P의 좌표 재설정 (flag, konduck의 위치로 갈 수 있어야함)
                stage[P.x][P.y] = BLANK;
                Goto(2 * P.x, P.y);
                printf("  ");
                P.x += _x;
                P.y += _y;
                Goto(2 * P.x, P.y);
                printf("◆");
                collision();
                stage[P.x][P.y] = PLAYER;
                count = 0;
            }
        }
    }
    else if (count < 10)
        count++;

    //속박, 반전 처리
    if (is_reverse) reverse_time++;
    if (is_stop) stop_time++;
    if (is_timeset) plmitime++;
    if (is_rollback) rollback_time++;

    if (reverse_time > 300) {
        is_reverse = 0;
        reverse_time = 0;
    }

    if (stop_time > 300) {
        is_stop = 0;
        stop_time = 0;
    }

    if (plmitime > 120) {
        is_timeset = 0;
        plmitime = 0;
    }

    if (rollback_time > 120) {
        is_rollback = 0;
        rollback_time = 0;
    }
}

void collision() { // 충돌에 따른 동작
    if (stage[P.x][P.y] != BLOCK) { // map 좌표가 블럭(0)이 아닌 경우
        switch (stage[P.x][P.y]) {
        case KONDUCK:
            // 즉시 게임 종료 (실패)
            is_success = 0;
            running = 0;
            break;

        case FLAG_TREASURE:
            // 보물 찾는 즉시 게임 종료 (성공)
            is_success = 1;
            running = 0;
            break;
        case FLAG_ROLLBACK:
            // 플레이 처음 위치로
            if (shield) {
                shield--;
                break;
            }
            stage[P.x][P.y] = BLANK;
            Goto(2 * P.x, P.y);
            printf("  ");
            stage[START_X][START_Y] = PLAYER;
            P.x = START_X;
            P.y = START_Y;
            Goto(2 * START_X, START_Y);
            printf("◆");
            is_rollback = 1;
            break;
        case FLAG_PLUSTIME:
            // 시간 추가
            time_limit_sec = 75; // 전역 변수인 기준 시간을 1.5배
            is_timeset = 1;
            break;
        case FLAG_MINUSTIME:
            // 시간 감소
            if (shield) {
                shield--;
                break;
            }
            time_limit_sec = 45; // 전역 변수인 기준 시간을 0.75배
            is_timeset = 2;
            break;
        case FLAG_GAMEOVER:
            // 즉시 게임오버
            if (shield) {
                shield--;
                break;
            }
            running = 0; // true일시 게임 실패
            is_success = 0;
            break;
        case FLAG_SPEEDZERO:
            // 이동 속도 = 0 (5초간)
            if (shield) {
                shield--;
                break;
            }
            is_stop = 1;
            break;
        case FLAG_REVERSE:
            // 방향키 반대로
            if (shield) {
                shield--;
                break;
            }
            is_reverse = 1;
            break;
        case FLAG_SHIELD:
            // 방어막 추가
            shield++;
            break;

        default:
            break;
        }
    }
}

/*
 * flag
 * 1. 보물
 * 2. 처음 위치로 되돌아가기
 * 3. 시간 증감
 * 4. 즉시 게임 오버
 * 6. 속도 증감(약 2초?)
 */

char quitGame() {
    short ch = 0, x = 5, y = 8;
    char cursor_pos = 0; // 4 == 예, 0 == 아니오

    system("cls");
    printf("\t일감호 아래 보물을 찾아라!\n\n");
    printf("========================================\n\n");
    printf("정말로 게임을 종료하시겠습니까?\n");
    printf("게임 종료시 모든 기록은 리셋됩니다.\n");
    printf("========================================\n\n");
    printf("예\t\t아니오    ");
    printf("←");

    while (1) { // 예 아니오 선택 while문
        if (_kbhit()) {
            ch = _getch();
            if (ch == 224) {
                ch = _getch();
                switch (ch) {

                case LEFT:
                    if (cursor_pos == 0) {
                        x = 5;
                        cursor_pos = 4;
                    }
                    break;

                case RIGHT:
                    if (cursor_pos == 4) {
                        x = 26;
                        cursor_pos = 0;
                    }
                    break;
                }
                printf("\b\b  ");
                Goto(x, y);
                printf("←");
            }
        }

        if (ch == '\r') {
            //버퍼 '\n' 지우기
            fflush(stdin);
            return cursor_pos;
        }
    }
}

void checkPlayerState() {
    int x;
    int y = 1;
    int cs = gameTime / 10;
    if (currentDifficulty == 0)
        x = 2 * (LOW_LEVEL_MAP_SIZE + 1);
    else if (currentDifficulty == 1)
        x = 2 * (MID_LEVEL_MAP_SIZE + 1);
    else
        x = 2 * (HIGH_LEVEL_MAP_SIZE + 1);

    Goto(x, y++);
    printf("경과 시간: %d.%d // %d", cs / 100, cs % 100, time_limit_sec);
    Goto(x, y++);
    printf("보호막 : %d개", shield);

    if (is_stop) {
        Goto(x, y++);
        printf("속박 (5초)");
    }
    else {
        Goto(x, y++);
        printf("                    ");
    }

    if (is_reverse) {
        Goto(x, y++);
        printf("방향키 반전 (5초)");
    }
    else {
        Goto(x, y++);
        printf("                    ");
    }

    if (is_rollback) {
        Goto(x, y++);
        printf("플레이어 시작 위치로!");
    }
    else {
        Goto(x, y++);
        printf("                    ");
    }

    switch (is_timeset) {
    case 1:
        Goto(x, y++);
        printf("시간 추가! (15초)");
        break;
    case 2:
        Goto(x, y++);
        printf("시간 감소! (15초)");
        break;
    default:
        Goto(x, y++);
        printf("                    ");
        break;
    }

}

void spawn_konduck() {
    // 0.5 ~ 2초 간격으로 랜덤 위치에 건덕이 생성
    int x1, y1, x2, y2, x3, y3, interval;
    static int interval_count = 0;
    switch (currentDifficulty) {

    case 2:
        interval = 30;
        if (interval_count == interval) { // 초급 = 2초, 중급 = 1초, 고급 0.5초 간격 생성
            while (1) {
                x3 = rand() % (HIGH_LEVEL_MAP_SIZE - 3) + 1;
                y3 = rand() % (HIGH_LEVEL_MAP_SIZE - 3) + 1;
                if (stage[x3][y3] == BLANK || stage[x3][y3] == PLAYER) break;
            }
            stage[duck3.x][duck3.y] = BLANK;
            Goto(2 * duck3.x, duck3.y);
            printf("  ");
            Goto(2 * x3, y3);
            printf("★");
            stage[x3][y3] = KONDUCK;
            duck3.x = x3;
            duck3.y = y3;
            interval_count = 0;
        }
        else interval_count++;

    case 1:
        interval = 60;
        if (interval_count == interval) { // 0.5초 간격 건덕이 생성
            while (1) {
                x2 = rand() % (HIGH_LEVEL_MAP_SIZE - 3) + 1;
                y2 = rand() % (HIGH_LEVEL_MAP_SIZE - 3) + 1;
                if (stage[x2][y2] == BLANK || stage[x2][y2] == PLAYER) break;
            }
            stage[duck2.x][duck2.y] = BLANK;
            Goto(2 * duck2.x, duck2.y);
            printf("  ");
            Goto(2 * x2, y2);
            printf("★");
            stage[x2][y2] = KONDUCK;
            duck2.x = x2;
            duck2.y = y2;
            interval_count = 0;
        }
        else interval_count++;

    case 0:
        interval = 120;
        if (interval_count == interval) { // 2초 간격 건덕이 생성
            while (1) {
                x1 = rand() % (HIGH_LEVEL_MAP_SIZE - 3) + 1;
                y1 = rand() % (HIGH_LEVEL_MAP_SIZE - 3) + 1;
                if (stage[x1][y1] == BLANK || stage[x1][y1] == PLAYER) break;
            }
            stage[duck1.x][duck1.y] = BLANK;
            Goto(2 * duck1.x, duck1.y);
            printf("  ");
            Goto(2 * x1, y1);
            printf("★");
            stage[x1][y1] = KONDUCK;
            duck1.x = x1;
            duck1.y = y1;
            interval_count = 0;
        }
        else interval_count++;
        break;
    }
}