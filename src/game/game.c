/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboucher <private_mail>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 14:15:33 by cboucher          #+#    #+#             */
/*   Updated: 2026/11/23 17:10:28 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	start_game(t_app *app)
{
	app->players[0].device_id = 0;
	app->input_handler.player_count = 1;
	app->input_handler.devices[0].angle
		= app->players[0].angle;
	app->input_handler.devices[0].initial_angle
		= app->players[0].angle;

	app->input_handler.total_mouse_pos = (t_vec2f){0, 0};
	app->input_handler.mouse_pos = (t_vec2i){app->frame_buffer.width / 2,
		app->frame_buffer.height / 2};
	app->input_handler.old_mouse_pos = app->input_handler.mouse_pos;
	mlx_mouse_move(app->ctx, app->window, app->frame_buffer.width / 2,
		app->frame_buffer.height / 2);
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
	app->input_handler.registered_click = false;
}

void	main_loop(t_app *app)
{
	init_devices(&app->input_handler);
	start_game(app);
	mlx_add_loop_hook(app->ctx, &game_update, app);
	mlx_on_event(app->ctx, app->window, MLX_WINDOW_EVENT, &window_event_handle,
		app);
	mlx_on_event(app->ctx, app->window, MLX_KEYDOWN, &handle_key_down, app);
	mlx_on_event(app->ctx, app->window, MLX_KEYUP, &handle_key_up, app);
	mlx_loop(app->ctx);
}
