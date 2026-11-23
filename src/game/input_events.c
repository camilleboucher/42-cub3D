/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 17:10:01 by yben-dje          #+#    #+#             */
/*   Updated: 2026/11/23 17:10:28 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	handle_key_down(int key, void *param)
{
	t_app	*app;

	app = param;
	input_handler_set_down(&app->input_handler, key);
	if (key == MLX_KEY_ESCAPE)
		mlx_loop_end(app->ctx);
}

void	handle_key_up(int key, void *param)
{
	t_app	*app;

	app = param;
	input_handler_set_up(&app->input_handler, key);
}

void	handle_controler_up(mlx_controller_event_code event, void *param)
{
	t_app			*app;
	t_input_device	*device;

	app = param;
	device = &app->input_handler.devices[2 + event.controller_id];
	if (device->action_key && event.button == MLX_CONTROLLER_X)
		device->action_key = false;
	if (device->sprint_key && event.button == MLX_CONTROLLER_A)
		device->sprint_key = false;
}

void	handle_controller_connections(mlx_controller_event_code event,
	t_app *app)
{
	if (event.button == MLX_CONTROLLER_CONNECT)
	{
		if (app->game_state != ingame
			&& app->input_handler.controller_count < 4)
		{
			app->input_handler.controller_count += 1;
			init_devices(&app->input_handler);
			init_input_select_menu(app);
		}
	}
	if (event.button == MLX_CONTROLLER_DISCONNECT)
	{
		if (app->input_handler.controller_count > 0)
		{
			if (app->game_state != ingame
				&& app->input_handler.controller_count > 0)
			{
				app->input_handler.controller_count -= 1;
				init_devices(&app->input_handler);
				init_input_select_menu(app);
			}
		}
	}
}

void	handle_controler_down(mlx_controller_event_code event, void *param)
{
	t_app			*app;
	t_input_device	*device;

	app = param;
	device = &app->input_handler.devices[2 + event.controller_id];
	handle_controller_connections(event, app);
	if (!device->action_key && event.button == MLX_CONTROLLER_X)
		device->action_key = true;
	if (!device->sprint_key && event.button == MLX_CONTROLLER_A)
		device->sprint_key = true;
}
