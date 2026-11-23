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
#include "mlx.h"
#include "mlx_profile.h"
#include "structs.h"
#include <stdlib.h>

static bool	allocate_buffers(t_app *app)
{
	app->frame_buffer.buffer = malloc(sizeof(t_region) + sizeof(mlx_color)
			* (app->frame_buffer.width * app->frame_buffer.height));
	app->frame_buffer.shader_buffer = malloc(sizeof(t_region)
			+ sizeof(mlx_color) * (app->frame_buffer.width
				* app->frame_buffer.height));
	app->frame_buffer.z_buffer = malloc(app->frame_buffer.width
			* sizeof(double));
	if (!app->frame_buffer.buffer || !app->frame_buffer.shader_buffer
		|| !app->frame_buffer.z_buffer)
		return (false);
	app->frame_buffer.screen_image = mlx_new_image(app->ctx,
			app->frame_buffer.screen_height, app->frame_buffer.screen_width);
	if (app->frame_buffer.screen_image == MLX_NULL_HANDLE)
		return (false);
	return (true);
}

static bool	allocate_minimap_buffers(t_app *app)
{
	app->frame_buffer.minimap_fb = malloc(sizeof(t_region) + sizeof(mlx_color)
			* (app->minimap.size.x * app->minimap.size.y));
	if (!app->frame_buffer.minimap_fb)
		return (false);
	app->frame_buffer.minimap_overlay_fb = malloc(sizeof(t_region)
			+ sizeof(mlx_color) * (app->minimap.size.x * app->minimap.size.y));
	if (!app->frame_buffer.minimap_overlay_fb)
		return (false);
	app->frame_buffer.minimap_fb_image = mlx_new_image(app->ctx,
			app->minimap.size.y, app->minimap.size.x);
	if (app->frame_buffer.minimap_fb_image == MLX_NULL_HANDLE)
		return (false);
	app->frame_buffer.minimap_overlay_fb_img = mlx_new_image(app->ctx,
			app->minimap.size.y, app->minimap.size.x);
	if (app->frame_buffer.minimap_overlay_fb_img == MLX_NULL_HANDLE)
		return (false);
	return (true);
}

static void	clean_all_buffers(t_app *app)
{
	free(app->frame_buffer.shader_buffer);
	free(app->frame_buffer.buffer);
	free(app->frame_buffer.minimap_fb);
	free(app->frame_buffer.minimap_overlay_fb);
	free(app->frame_buffer.z_buffer);
	if (app->frame_buffer.screen_image != MLX_NULL_HANDLE)
		mlx_destroy_image(app->ctx, app->frame_buffer.screen_image);
	if (app->frame_buffer.minimap_fb_image != MLX_NULL_HANDLE)
		mlx_destroy_image(app->ctx, app->frame_buffer.minimap_fb_image);
	if (app->frame_buffer.minimap_overlay_fb_img != MLX_NULL_HANDLE)
		mlx_destroy_image(app->ctx, app->frame_buffer.minimap_overlay_fb_img);
	app->frame_buffer.shader_buffer = NULL;
	app->frame_buffer.buffer = NULL;
	app->frame_buffer.minimap_fb = NULL;
	app->frame_buffer.minimap_overlay_fb = NULL;
	app->frame_buffer.z_buffer = NULL;
	app->frame_buffer.screen_image = MLX_NULL_HANDLE;
	app->frame_buffer.minimap_fb_image = MLX_NULL_HANDLE;
	app->frame_buffer.minimap_overlay_fb_img = MLX_NULL_HANDLE;
}

bool	reallocate_frame_buffer(t_app *app)
{
	clean_all_buffers(app);
	if (!allocate_buffers(app))
		return (false);
	if (!allocate_minimap_buffers(app))
		return (false);
	app->frame_buffer.buffer->width = app->frame_buffer.width;
	app->frame_buffer.buffer->height = app->frame_buffer.height;
	app->frame_buffer.shader_buffer->width = app->frame_buffer.width;
	app->frame_buffer.shader_buffer->height = app->frame_buffer.height;
	app->frame_buffer.minimap_fb->width = app->minimap.size.x;
	app->frame_buffer.minimap_fb->height = app->minimap.size.y;
	app->frame_buffer.minimap_overlay_fb->width = app->minimap.size.x;
	app->frame_buffer.minimap_overlay_fb->height = app->minimap.size.y;
	return (true);
}

bool	resize_frame_buffer(t_app *app, unsigned int width, unsigned int height)
{
	app->frame_buffer.screen_width = width;
	app->frame_buffer.screen_height = height;
	app->minimap.size = (t_vec2i){height / 4, height / 4};
	app->minimap.pos = (t_vec2i){height / 4, height / 4};
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
	clear_region(app->frame_buffer.minimap_fb, (mlx_color){.rgba = 0});
	return (true);
}
