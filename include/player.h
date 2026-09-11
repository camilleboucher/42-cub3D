#ifndef PLAYER_H
#define PLAYER_H

#include "vector.h"
#include "input_handler.h"

typedef struct s_player
{
	t_vec2f	pos;
	double		angle;
	t_vec2f	forward;
	t_vec2f right;
	t_vec2f speed;
}	t_player;

void player_input(t_player *player, t_input_handler *input_handler, double delta_time, unsigned int index);

#endif