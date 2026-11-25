/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboucher <private_mail>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 14:15:16 by cboucher          #+#    #+#             */
/*   Updated: 2026/10/07 14:29:15 by cboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool	allocate_buffers(t_app *app)
{
	app->frame_buffer.buffer = malloc(sizeof(t_region) + sizeof(mlx_color)
			* (app->frame_buffer.width * app->frame_buffer.height));
	if (!app->frame_buffer.buffer)
		return (false);
	app->frame_buffer.screen_image = mlx_new_image(app->ctx,
			app->frame_buffer.screen_height, app->frame_buffer.screen_width);
	if (app->frame_buffer.screen_image == MLX_NULL_HANDLE)
		return (false);
	return (true);
}

static void	clean_all_buffers(t_app *app)
{
	free(app->frame_buffer.buffer);
	if (app->frame_buffer.screen_image != MLX_NULL_HANDLE)
		mlx_destroy_image(app->ctx, app->frame_buffer.screen_image);
	app->frame_buffer.buffer = NULL;
	app->frame_buffer.screen_image = MLX_NULL_HANDLE;
}

bool	reallocate_frame_buffer(t_app *app)
{
	clean_all_buffers(app);
	if (!allocate_buffers(app))
		return (false);
	app->frame_buffer.buffer->width = app->frame_buffer.width;
	app->frame_buffer.buffer->height = app->frame_buffer.height;
	return (true);
}

bool	resize_frame_buffer(t_app *app, unsigned int width, unsigned int height)
{
	app->frame_buffer.screen_width = width;
	app->frame_buffer.screen_height = height;
	if (app->game_state != ingame || app->input_handler.player_count == 1)
	{
		app->frame_buffer.width = width;
		app->frame_buffer.height = height;
	}
	else if (app->input_handler.player_count == 2)
	{
		app->frame_buffer.width = width / 2;
		app->frame_buffer.height = height;
	}
	else if (app->input_handler.player_count == 3
		|| app->input_handler.player_count == 4)
	{
		app->frame_buffer.width = width / 2;
		app->frame_buffer.height = height / 2;
	}
	if (!reallocate_frame_buffer(app))
		return (false);
	clear_frame_buffer(app, (mlx_color){.rgba = 0});
	return (true);
}
