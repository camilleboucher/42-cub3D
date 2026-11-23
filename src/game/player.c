/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 14:19:33 by cboucher          #+#    #+#             */
/*   Updated: 2026/11/23 17:10:28 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	move_player(t_map *map, t_player *player, t_vec2f delta_pos,
		bool sprint_key)
{
	t_vec2f	new_pos;

	if (sprint_key)
		delta_pos = (t_vec2f){delta_pos.x * PLAYER_SPRINT, delta_pos.y
			* PLAYER_SPRINT};
	new_pos = vec2f_add(player->pos, delta_pos);
	if (has_collision(map, new_pos))
	{
		if (!has_collision(map, (t_vec2f){new_pos.x, player->pos.y}))
		{
			player->pos.x = new_pos.x;
			player->speed.y = 0;
		}
		else if (!has_collision(map, (t_vec2f){player->pos.x, new_pos.y}))
		{
			player->pos.y = new_pos.y;
			player->speed.x = 0;
		}
	}
	else
		player->pos = new_pos;
}

t_vec2f	get_move_vector(t_player *player, t_input_handler *input_handler,
	double delta_time)
{
	t_vec2f	move;

	player->forward.x = cos(player->angle);
	player->forward.y = sin(player->angle);
	player->right.x = -sin(player->angle);
	player->right.y = cos(player->angle);
	move = (t_vec2f){0., 0.};
	move = vec2f_add(move, vec2f_mul(player->forward,
				-get_controler_left_vector(input_handler,
					player->device_id).y));
	move = vec2f_add(move, vec2f_mul(player->right,
				get_controler_left_vector(input_handler, player->device_id).x));
	move = vec2f_mul(move, PLAYER_FORCE);
	player->speed = vec2f_add(player->speed, vec2f_mul(move, delta_time));
	return (move);
}

void	move_input(t_player *player, t_input_handler *input_handler,
		double delta_time, t_map *map)
{
	t_vec2f	move;
	t_vec2f	invert_friction;

	move = get_move_vector(player, input_handler, delta_time);
	player->speed = vec2f_add(player->speed, vec2f_mul(move, delta_time));
	if (vec2f_length(player->speed) > PLAYER_MAX_SPEED)
		player->speed = vec2f_mul(vec2f_normalize(player->speed),
				PLAYER_MAX_SPEED);
	if (vec2f_length(player->speed) > 0.)
	{
		invert_friction = vec2f_mul(vec2f_normalize(player->speed),
				PLAYER_SPEED_DECREASE * delta_time);
		if (vec2f_length(invert_friction) > vec2f_length(player->speed))
			player->speed = (t_vec2f){0., 0.};
		else
			player->speed = vec2f_sub(player->speed, invert_friction);
	}
	move_player(map, player, vec2f_mul(player->speed, delta_time),
		input_handler->devices[player->device_id].sprint_key);
	player->angle = get_controler_angle(input_handler, player->device_id);
}
