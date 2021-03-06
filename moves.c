#include "moves.h"
#include <time.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

int check_move(char map[MAP_HEIGHT][MAP_WIDTH], int nx, int ny)
{
    if(nx < 0 || nx < 0 || nx >= MAP_HEIGHT || ny >= MAP_WIDTH)
        return FALSE;
    if(map[nx][ny] == wall_symbol)
        return FALSE;

    return TRUE;
}


void player_move(struct Player *player, char ch, char map[MAP_HEIGHT][MAP_WIDTH])
{
    int nx = player->x;
    int ny = player->y;
    switch(ch)
    {
        case 'w':
            nx += dx[0];
            ny += dy[0];
            break;
        case 'd':
            nx += dx[1];
            ny += dy[1];
            break;
        case 's':
            nx += dx[2];
            ny += dy[2];
            break;
        case 'a':
            nx += dx[3];
            ny += dy[3];
            break;
        default:
            break;
    }
    if(check_move(map, nx, ny) == TRUE)
    {
	move(player->x, player->y);
	addch(empty_symbol);

    	player->x = nx;
    	player->y = ny;
    }

}

void set_new_position(Obstacle *ob, Position *pos)
{
        srand(time(NULL));
        int i = possible_direction[ob->face][rand() % 3];
        int nx = ob->x + dx[i];
        int ny = ob->y + dy[i];
        pos->x = nx;
        pos->y = ny;
	pos->face = i;
}

void print_obstacles(Obstacle* ob_array, int obstacle_number)
{
    for(int i = 0; i < obstacle_number; i++)
    {
        Obstacle *cur_ob = &ob_array[i];
        move(cur_ob->x, cur_ob->y);
        addch(obstacle_symbol);
    }
}

void move_obstacle(char map[MAP_HEIGHT][MAP_WIDTH], struct Obstacle *ob)
{
    move(ob->x, ob->y);
    addch(empty_symbol);

    struct Position pos = {ob->x, ob->y};
    set_new_position(ob, &pos);
    while(check_move(map, pos.x, pos.y) == FALSE)
    {
        set_new_position(ob, &pos);
    }
    ob->x = pos.x;
    ob->y = pos.y;
    ob->face = pos.face;
}

void print_player(struct Player* player)
{
    move(player->x, player->y);
    addch(player_symbol);
}

int check_collision_ob(struct Player *player, struct Obstacle *ob, int obstacle_number)
{
    for(int i = 0; i < obstacle_number; i++)
    {
	Obstacle* cur_ob = &ob[i];
	if(player->x == cur_ob->x && player->y == cur_ob->y)
	    return TRUE;
    }

    return FALSE;
}
