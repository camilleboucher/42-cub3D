/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboucher <private_mail>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 14:15:33 by cboucher          #+#    #+#             */
/*   Updated: 2026/11/23 17:10:28 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static void	setup_all_players(t_app *app)
{
	unsigned int	i;
	int				card_id;

	i = 0;
	while (i < app->input_handler.player_count)
	{
		card_id = app->input_select_menu.card_slots[i].docked_card_id;
		app->players[i].device_id
			= app->input_select_menu.cards[card_id].device_id;
		app->input_handler.devices[app->players[i].device_id].angle
			= app->players[i].angle;
		app->input_handler.devices[app->players[i].device_id].initial_angle
			= app->players[i].angle;
		if (app->input_handler.devices[app->players[i++].device_id].type
			== device_keyboard_and_mouse)
			mlx_mouse_hide(app->ctx);
	}
}

void	start_game(t_app *app)
{
	setup_all_players(app);
	app->input_handler.total_mouse_pos = (t_vec2f){0, 0};
	app->input_handler.mouse_pos = (t_vec2i){app->frame_buffer.width / 2,
		app->frame_buffer.height / 2};
	app->input_handler.old_mouse_pos = app->input_handler.mouse_pos;
	mlx_mouse_move(app->ctx, app->window, app->frame_buffer.width / 2,
		app->frame_buffer.height / 2);
	app->minimap.showed = true;
	app->game_state = ingame;
	if (app->input_handler.player_count > 1)
		handle_resize_event(app);
}

void	game_update(void *param)
{
	t_app	*app;

	app = param;
	if (app->request_immediate_abort)
		return ;
	mlx_mouse_get_pos(app->ctx, &app->input_handler.mouse_pos.x,
		&app->input_handler.mouse_pos.y);
	if (app->game_state == ingame)
		ingame_update(app);
	else if (app->game_state == main_menu)
		main_menu_window_update(app);
	else if (app->game_state == player_count_select)
		player_count_menu_window_update(app);
	else if (app->game_state == input_select)
		input_select_menu_window_update(app);
	app->input_handler.registered_click = false;
}

void	main_loop(t_app *app)
{
	app->game_state = main_menu;
	init_devices(&app->input_handler);
	init_main_menu(app);
	init_player_count_menu(app);
	mlx_add_loop_hook(app->ctx, &game_update, app);
	mlx_on_event(app->ctx, app->window, MLX_WINDOW_EVENT, &window_event_handle,
		app);
	mlx_on_event(app->ctx, app->window, MLX_MOUSEUP, &handle_mouse_up, app);
	mlx_on_event(app->ctx, app->window, MLX_MOUSEDOWN, &handle_mouse_down, app);
	mlx_on_event(app->ctx, app->window, MLX_KEYDOWN, &handle_key_down, app);
	mlx_on_event(app->ctx, app->window, MLX_KEYUP, &handle_key_up, app);
	mlx_on_event(app->ctx, app->window, MLX_CONTROLLERDOWN,
		(void (*)(int, void *))handle_controller_down, app);
	mlx_on_event(app->ctx, app->window, MLX_CONTROLLERUP,
		(void (*)(int, void *))handle_controller_up, app);
	mlx_loop(app->ctx);
}
