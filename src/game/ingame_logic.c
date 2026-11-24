/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ingame_logic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 17:10:01 by yben-dje          #+#    #+#             */
/*   Updated: 2026/11/23 17:10:28 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_screens(t_app *app)
{
	t_raycaster			raycaster;
	unsigned int		player_index;

	player_index = 0;
	while (player_index < app->input_handler.player_count)
	{
		raycaster = (t_raycaster){0};
		raycaster.camera_pos = app->players[player_index].pos;
		raycaster.camera_dir.x = cos(app->players[player_index].angle);
		raycaster.camera_dir.y = sin(app->players[player_index].angle);
		move_input(&app->players[player_index], &app->input_handler,
			app->time.delta, &app->map);
		draw_raycast(app, &raycaster);
		push_buffer_to_screen_image(app, player_index);
		player_index++;
	}
}

void	ingame_update(t_app *app)
{
	app->time.now = get_time();
	app->time.delta = app->time.now - app->time.last;
	if (app->time.last == 0.)
		app->time.last = app->time.now;
	printf("FPS: %d\n", (int)(1.0 / app->time.delta));
	input_handler_update(&app->input_handler, app->time.delta);
	app->input_handler.total_mouse_pos.x += app->input_handler.mouse_pos.x
		- app->input_handler.old_mouse_pos.x;
	app->input_handler.total_mouse_pos.y += app->input_handler.mouse_pos.y
		- app->input_handler.old_mouse_pos.y;
	app->input_handler.old_mouse_pos = app->input_handler.mouse_pos;
	draw_screens(app);
	push_frame_buffer_to_screen(app);
	app->time.last = app->time.now;
}
