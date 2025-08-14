#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define NUM_PLAYERS 4
#define NUM_CELLS 101
#define NUM_SNAKES 6
#define NUM_LADDERS 6

enum CELL_STATE
{
    EMPTY,
    CAPTURED_P1,
    CAPTURED_P2,
    CAPTURED_P3,
    CAPTURED_P4
};

enum CELL_TYPE
{
    NORMAL,
    SNAKE_HEAD,
    LADDER_START
};

typedef struct 
{
    int cell_ID;
    int cell_state;
    int cell_type;
    union
    {
        int destination;
    }special;
    
} Cell;

typedef struct 
{
    char name[10];
    Cell *position;
    int roll_value;
} Player;

typedef struct
{
    int from;
    int to;
}Jump;

extern Player players[NUM_PLAYERS];
extern Cell cells[NUM_CELLS];
extern Jump ladders[NUM_LADDERS];
extern Jump snakes[NUM_SNAKES]; 
extern int game_over;

void init_objects(Player *plyr_array, Cell *cell_array);
void move_player(Player *plyr);

#endif