/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboucher <private_mail>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 14:10:04 by cboucher          #+#    #+#             */
/*   Updated: 2026/10/28 18:20:11 by cboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include "cub3D.h"

//objects.c
bool	create_objects(t_app *app);
int		get_door_id(int cell, int nb_doors, t_app *app);
void	update_doors(t_app *app, t_door *door, int nb_doors);

//game.c
void	main_loop(t_app *app);

//player.c
bool	playerbox_in_door(t_map *map, t_vec2f test_pos);
void	move_input(t_player *player, t_input_handler *input_handler,
			double delta_time, t_map *map);

#endif
