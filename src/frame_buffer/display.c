/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 16:38:48 by yben-dje          #+#    #+#             */
/*   Updated: 2026/11/23 16:38:48 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	push_buffer_to_screen_image(t_app *app, unsigned int sub_screen_index)
{
	t_vec2i	offset;

	offset = (t_vec2i){0, 0};
	if (app->input_handler.player_count > 1)
		offset = (t_vec2i){(sub_screen_index % 2) * app->frame_buffer.width,
			(sub_screen_index / 2) * app->frame_buffer.height};
	mlx_set_image_region(app->ctx, app->frame_buffer.screen_image, offset.y,
		offset.x, app->frame_buffer.buffer->height,
		app->frame_buffer.buffer->width, app->frame_buffer.buffer->buffer);
}

void	push_frame_buffer_to_screen(t_app *app)
{
	mlx_clear_window(app->ctx, app->window, (mlx_color){.rgba = 0x000000FF});
	if (app->input_handler.player_count > 1)
		mlx_set_image_rectangle(app->ctx, app->frame_buffer.screen_image, 0,
			app->frame_buffer.width - 2, app->frame_buffer.screen_height, 4,
			(mlx_color){.rgba = 0x000000ff});
	if (app->input_handler.player_count > 2)
		mlx_set_image_rectangle(app->ctx, app->frame_buffer.screen_image,
			app->frame_buffer.height - 2, 0, 4, app->frame_buffer.screen_width,
			(mlx_color){.rgba = 0x000000ff});
	mlx_put_transformed_image_to_window(app->ctx, app->window,
		app->frame_buffer.screen_image, ((float)app->frame_buffer.screen_width
			+ (float)app->frame_buffer.screen_height) / 2.f,
		((float)app->frame_buffer.screen_height
			- (float)app->frame_buffer.screen_width) / 2.f, -1, 1, 90);
}
