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

static bool	allocate_buffers(t_app *app)
{
	app->frame_buffer.buffer = malloc(sizeof(t_region) + sizeof(mlx_color)
			* (app->frame_buffer.width * app->frame_buffer.height));
	app->frame_buffer.shader_buffer = malloc(sizeof(t_region) + sizeof(mlx_color)
			* (app->frame_buffer.width * app->frame_buffer.height));
	if (!app->frame_buffer.buffer || !app->frame_buffer.shader_buffer)
		return (false);
	app->frame_buffer.screen_image = mlx_new_image(app->ctx,
			app->frame_buffer.screen_height, app->frame_buffer.screen_width);
	if (app->frame_buffer.screen_image == MLX_NULL_HANDLE)
		return (false);
	return (true);
}

static bool allocate_minimap_buffers(t_app *app) {
	app->frame_buffer.minimap_frame_buffer = malloc(sizeof(t_region) + sizeof(mlx_color) * (app->minimap.size.x * app->minimap.size.y));
    if (!app->frame_buffer.minimap_frame_buffer)
        return (false);
    app->frame_buffer.minimap_overlay_frame_buffer = malloc(sizeof(t_region) + sizeof(mlx_color) * (app->minimap.size.x * app->minimap.size.y));
    if (!app->frame_buffer.minimap_overlay_frame_buffer)
        return (false);
    app->frame_buffer.minimap_frame_buffer_image = mlx_new_image(app->ctx, app->minimap.size.y, app->minimap.size.x);
    if (app->frame_buffer.minimap_frame_buffer_image == MLX_NULL_HANDLE)
        return (false);
    app->frame_buffer.minimap_overlay_frame_buffer_image = mlx_new_image(app->ctx, app->minimap.size.y, app->minimap.size.x);
    if (app->frame_buffer.minimap_overlay_frame_buffer_image == MLX_NULL_HANDLE)
        return (false);
    return (true);
}

bool	reallocate_frame_buffer(t_app *app)
{
	free(app->frame_buffer.shader_buffer);
	free(app->frame_buffer.buffer);
	free(app->frame_buffer.minimap_frame_buffer);
	free(app->frame_buffer.minimap_overlay_frame_buffer);
	if (app->frame_buffer.screen_image != MLX_NULL_HANDLE)
		mlx_destroy_image(app->ctx, app->frame_buffer.screen_image);
	if (app->frame_buffer.minimap_frame_buffer_image != MLX_NULL_HANDLE)
		mlx_destroy_image(app->ctx, app->frame_buffer.minimap_frame_buffer_image);
	if (app->frame_buffer.minimap_overlay_frame_buffer_image != MLX_NULL_HANDLE)
		mlx_destroy_image(app->ctx, app->frame_buffer.minimap_overlay_frame_buffer_image);
	app->frame_buffer.shader_buffer = NULL;
	app->frame_buffer.buffer = NULL;
	app->frame_buffer.minimap_frame_buffer = NULL;
	app->frame_buffer.minimap_overlay_frame_buffer = NULL;
	app->frame_buffer.screen_image = MLX_NULL_HANDLE;
	app->frame_buffer.minimap_frame_buffer_image = MLX_NULL_HANDLE;
	app->frame_buffer.minimap_overlay_frame_buffer_image = MLX_NULL_HANDLE;
	if (!allocate_buffers(app))
		return (false);
	if (!allocate_minimap_buffers(app))
		return (false);
	app->frame_buffer.buffer->width = app->frame_buffer.width;
	app->frame_buffer.buffer->height = app->frame_buffer.height;
	app->frame_buffer.shader_buffer->width = app->frame_buffer.width;
	app->frame_buffer.shader_buffer->height = app->frame_buffer.height;
	app->frame_buffer.minimap_frame_buffer->width = app->minimap.size.x;
	app->frame_buffer.minimap_frame_buffer->height = app->minimap.size.y;
	app->frame_buffer.minimap_overlay_frame_buffer->width = app->minimap.size.x;
	app->frame_buffer.minimap_overlay_frame_buffer->height = app->minimap.size.y;
	return (true);
}


///    ---------------------------------------------------------



bool resize_frame_buffer(t_app *app, unsigned int width, unsigned height)
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
    else if (app->input_handler.player_count == 3 || app->input_handler.player_count == 4)
    {
        app->frame_buffer.width = width / 2;
        app->frame_buffer.height = height / 2;
    }
    if (!reallocate_frame_buffer(app))
        return (false);
    clear_frame_buffer(app, (mlx_color){.rgba = 0x000000FF});
    clear_region(app->frame_buffer.minimap_frame_buffer, (mlx_color){.rgba = 0x00000000});
    return (true);
}

void push_buffer_to_screen_image(t_app *app, unsigned int sub_screen_index)
{
    t_vec2i offset;

    offset = (t_vec2i){0, 0};
    if (app->input_handler.player_count > 1)
        offset = (t_vec2i){(sub_screen_index % 2) * app->frame_buffer.width, (sub_screen_index / 2) * app->frame_buffer.height};
    mlx_set_image_region(app->ctx, app->frame_buffer.screen_image, offset.y, offset.x,
        app->frame_buffer.buffer->height, app->frame_buffer.buffer->width,
        app->frame_buffer.buffer->buffer);
}

void push_frame_buffer_to_screen(t_app *app)
{
    mlx_clear_window(app->ctx, app->window, (mlx_color){.rgba = 0x000000FF});

    if (app->input_handler.player_count > 1)
        mlx_set_image_rectangle(app->ctx, app->frame_buffer.screen_image, 0, app->frame_buffer.width - 2, app->frame_buffer.screen_height, 4, (mlx_color){ .rgba=0x000000ff });
    if (app->input_handler.player_count > 2)
        mlx_set_image_rectangle(app->ctx, app->frame_buffer.screen_image, app->frame_buffer.height - 2, 0, 4, app->frame_buffer.screen_width, (mlx_color){ .rgba=0x000000ff });
    mlx_put_transformed_image_to_window(app->ctx, app->window,
        app->frame_buffer.screen_image,
        ((float)app->frame_buffer.screen_width + (float)app->frame_buffer.screen_height) / 2.f,
        ((float)app->frame_buffer.screen_height - (float)app->frame_buffer.screen_width) / 2.f, -1, 1, 90);
    if (app->minimap.showed)
    {
        mlx_set_image_region(app->ctx, app->frame_buffer.minimap_frame_buffer_image, 0, 0,
            app->frame_buffer.minimap_frame_buffer->height, app->frame_buffer.minimap_frame_buffer->width,
            app->frame_buffer.minimap_frame_buffer->buffer);
        mlx_put_transformed_image_to_window(app->ctx, app->window, app->frame_buffer.minimap_frame_buffer_image, app->minimap.pos.x, app->minimap.pos.y - app->minimap.size.y, -1, 1, app->players[0].angle * 180 / M_PI + 180);

        mlx_set_image_region(app->ctx, app->frame_buffer.minimap_overlay_frame_buffer_image, 0, 0,
            app->frame_buffer.minimap_frame_buffer->height, app->frame_buffer.minimap_frame_buffer->width,
            app->frame_buffer.minimap_overlay_frame_buffer->buffer);
        mlx_put_transformed_image_to_window(app->ctx, app->window, app->frame_buffer.minimap_overlay_frame_buffer_image, app->minimap.pos.x, app->minimap.pos.y - app->minimap.size.y, -1, 1, 90);
    }
}
