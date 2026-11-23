/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 17:10:01 by yben-dje          #+#    #+#             */
/*   Updated: 2026/11/23 17:10:28 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	handle_mouse_up(int button, void *param)
{
	t_app	*app;

	app = param;
	if (button == 1)
	{
		app->input_handler.registered_click = true;
		app->input_handler.mouse_down = false;
	}
}

void	handle_mouse_down(int button, void *param)
{
	t_app	*app;

	app = param;
	if (button == 1)
	{
		app->input_handler.mouse_down = true;
	}
}

static void	mouse_jail_x(t_app *app, t_vec2i mouse_box)
{
	if (app->input_handler.mouse_pos.x > (int)app->frame_buffer.screen_width / 2
		+ mouse_box.x)
	{
		mlx_mouse_move(app->ctx, app->window, app->frame_buffer.screen_width / 2
			- mouse_box.x, app->input_handler.mouse_pos.y);
		app->input_handler.mouse_pos = (t_vec2i){app->frame_buffer.screen_width
			/ 2 - mouse_box.x, app->input_handler.mouse_pos.y};
		app->input_handler.old_mouse_pos = app->input_handler.mouse_pos;
	}
	if (app->input_handler.mouse_pos.x < (int)app->frame_buffer.screen_width / 2
		- mouse_box.x)
	{
		mlx_mouse_move(app->ctx, app->window, app->frame_buffer.screen_width / 2
			+ mouse_box.x, app->input_handler.mouse_pos.y);
		app->input_handler.mouse_pos = (t_vec2i){app->frame_buffer.screen_width
			/ 2 + mouse_box.x, app->input_handler.mouse_pos.y};
		app->input_handler.old_mouse_pos = app->input_handler.mouse_pos;
	}
}

static void	mouse_jail_y(t_app *app, t_vec2i mouse_box)
{
	if (app->input_handler.mouse_pos.y < (int)app->frame_buffer.screen_height / 2
		- mouse_box.y)
	{
		mlx_mouse_move(app->ctx, app->window, app->input_handler.mouse_pos.x,
			app->frame_buffer.screen_height / 2 + mouse_box.y);
		app->input_handler.mouse_pos = (t_vec2i){app->input_handler.mouse_pos.x,
			app->frame_buffer.screen_height / 2 + mouse_box.y};
		app->input_handler.old_mouse_pos = app->input_handler.mouse_pos;
	}
	if (app->input_handler.mouse_pos.y > (int)app->frame_buffer.screen_height / 2
		+ mouse_box.y)
	{
		mlx_mouse_move(app->ctx, app->window, app->input_handler.mouse_pos.x,
			app->frame_buffer.screen_height / 2 - mouse_box.y);
		app->input_handler.mouse_pos = (t_vec2i){app->input_handler.mouse_pos.x,
			app->frame_buffer.screen_height / 2 - mouse_box.y};
		app->input_handler.old_mouse_pos = app->input_handler.mouse_pos;
	}
}

void	mouse_jail(t_app *app)
{
	t_vec2i	mouse_box;

	mouse_box.x = app->frame_buffer.screen_width / 4;
	mouse_box.y = app->frame_buffer.screen_height / 4;
	mouse_jail_x(app, mouse_box);
	mouse_jail_y(app, mouse_box);
}
