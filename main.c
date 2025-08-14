#include "header.h"

int main()
{
    srand(time(NULL));
    init_objects(players, cells);

    int player_index = 0;
    int round = 0;
    while (!game_over)
    {
        move_player(players + (player_index % NUM_PLAYERS));
        player_index++;
    }
    return 0;
}