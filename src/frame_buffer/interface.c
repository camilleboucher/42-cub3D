/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboucher <private_mail>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 14:15:22 by cboucher          #+#    #+#             */
/*   Updated: 2026/10/07 14:29:19 by cboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	set_pixel(t_region *frame_buffer, unsigned int x, unsigned int y,
		mlx_color color)
{
	frame_buffer->buffer[y + x * frame_buffer->height] = color;
}

void set_pxl(t_region *frame_buf, unsigned int i, mlx_color color, bool is_door)
{
	if (!is_door || get_pixel_opt(frame_buf, i).a < 255)
		set_pixel_opt(frame_buf, i, color);
}

mlx_color	get_pixel(t_region *frame_buffer, unsigned int x, unsigned int y)
{
	return (frame_buffer->buffer[y + x * frame_buffer->height]);
}

void	clear_frame_buffer(t_app *app, mlx_color color)
{
	unsigned int	i;

	i = 0;
	while (i < app->frame_buffer.width * app->frame_buffer.height)
		app->frame_buffer.buffer->buffer[i++] = color;
}

void	set_pixel_opt(t_region *frame_buffer, unsigned int i, mlx_color color)
{
	frame_buffer->buffer[i] = color;
}

mlx_color	get_pixel_opt(t_region *frame_buffer, unsigned int i)
{
	return (frame_buffer->buffer[i]);
}
