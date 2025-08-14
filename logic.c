#include "header.h"

int game_over = 0;
Player players[NUM_PLAYERS];
Cell cells[NUM_CELLS];
Jump ladders[] = {
    {5,58},
    {14,49},
    {42,60},
    {53,72},
    {64,83},
    {75,94}
};
Jump snakes[] = {
    {38,20},
    {45,7},
    {51,10},
    {65,54},
    {91,73},
    {99,61}
};

void init_objects(Player *plyr_array, Cell *cell_array)
{
    //init cells
    for(int i = 0; i<NUM_CELLS; i++)
    {
        cell_array[i].cell_ID = i;
        cell_array[i].cell_state = EMPTY;
        cell_array[i].cell_type = NORMAL;
    }
    //init players
    for(int i = 0; i<NUM_PLAYERS; i++)
    {
        sprintf(plyr_array[i].name, "P%d", i + 1);
        plyr_array[i].roll_value = 0;
        plyr_array[i].position = &cells[0];
    }
    
    // Init special cells
    for(int i = 0; i < NUM_LADDERS; i++)
    {
        cell_array[ladders[i].from].cell_type = LADDER_START;
        cell_array[ladders[i].from].special.destination = ladders[i].to;
    }

    for(int i = 0; i < NUM_SNAKES; i++)
    {
        cell_array[snakes[i].from].cell_type = SNAKE_HEAD;
        cell_array[snakes[i].from].special.destination = snakes[i].to;
    }

}

void print_state(const Player *plyr_array) //ptr is a pointer to a Player
{
    for (int i = 0; i < NUM_PLAYERS; i++) {
        printf("%s: %d\n", plyr_array[i].name, plyr_array[i].position->cell_ID);
    }
    printf("\n");
}

int dice_roll()
{
    return (rand() % 6)+1;
}

void move_player(Player *plyr)
{
    printf("---------------------------------------------------------------\n");
    plyr->roll_value = dice_roll();
    printf("The %s takes the chance and rolled the value %d\n", plyr->name, plyr->roll_value);
    int new_index = plyr->position->cell_ID + plyr->roll_value;
    if(new_index<NUM_CELLS-1)
    {
        printf("The %s moves to %d from %d\n", plyr->name, new_index, plyr->position->cell_ID);
        plyr->position = &cells[new_index];
        //check for a sanke head or a ladder start and make the updates
        if(cells[new_index].cell_type == SNAKE_HEAD || cells[new_index].cell_type == LADDER_START)
        {
            new_index = cells[new_index].special.destination;
            if(plyr->position->cell_type == LADDER_START)
            {
                printf("The %s lands on a ladder and will move to the ladder end at %d\n", plyr->name, new_index);
            }
            else
            {
                printf("The %s lands on a snake and will move to the snake tail at %d\n", plyr->name, new_index);
            }
            plyr->position = &cells[new_index];
        }
    }
    else
    {
        if(new_index>NUM_CELLS-1)
        {
            printf("The %s can't move beyond the last cell.\n", plyr->name);
        }
        else
        {
            printf("The %s moves to %d from %d\n", plyr->name, new_index, plyr->position->cell_ID);
            plyr->position = &cells[new_index];
            printf("The %s won!\n", plyr->name);
            game_over = 1;
            
        }
    }
}
