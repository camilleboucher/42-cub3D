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

void	window_event_handle(int event, void *param);
void	handle_resize_event(t_app *app);

bool	has_collision(t_map *map, t_vec2f test_pos);
bool	playerbox_in_door(t_map *map, t_vec2f test_pos);

void	action_input(t_app *app, t_player *player);
void	check_door_activation(t_app *app, t_vec2f target, t_player *player);

void	player_count_menu_window_update(t_app *app);
void	init_player_count_menu(t_app *app);

void	handle_mouse_up(int button, void *param);
void	handle_mouse_down(int button, void *param);
void	mouse_jail(t_app *app);

void	init_main_menu(t_app *app);
void	main_menu_window_update(t_app *app);

void	init_input_select_menu(t_app *app);
void	input_select_menu_window_update(t_app *app);

void	handle_key_down(int key, void *param);
void	handle_key_up(int key, void *param);
void	handle_controler_up(mlx_controller_event_code event, void *param);
void	handle_controler_down(mlx_controller_event_code event, void *param);

void	ingame_update(t_app *app);
void	start_game(t_app *app);

//player.c
bool	playerbox_in_door(t_map *map, t_vec2f test_pos);
void	move_input(t_player *player, t_input_handler *input_handler,
			double delta_time, t_map *map);
bool	has_collision(t_map *map, t_vec2f test_pos);
bool	playerbox_in_door(t_map *map, t_vec2f test_pos);

#endif
