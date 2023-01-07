#ifndef __STRUCT_H__
#define __STRUCT_H__


typedef struct KonDuck {
    int x;
    int y;
} konDuck;

typedef struct Record {
    char user[100];
    int time;
    char level;
} record;

typedef struct Player {
    int x;
    int y;
} player;

#endif