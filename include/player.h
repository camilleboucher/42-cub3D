/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboucher <private_mail>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 14:10:30 by cboucher          #+#    #+#             */
/*   Updated: 2026/10/07 16:06:46 by cboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
#define PLAYER_H

typedef struct s_player
{
	t_vec2f	pos;
	double		angle;
	t_vec2f	forward;
	t_vec2f right;
	t_vec2f speed;
}	t_player;

void player_input(t_player *player, t_input_handler *input_handler, double delta_time, t_map *map);

#endif
