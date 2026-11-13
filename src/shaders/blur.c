/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blur.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboucher <private_mail>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 14:25:03 by cboucher          #+#    #+#             */
/*   Updated: 2026/10/07 14:30:36 by cboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

#define MAX_BLUR_RADIUS 64

void	clear_buffer(mlx_color *buffer, long sum[3], mlx_color color,
		unsigned int size)
{
	unsigned int	i;

	sum[0] = size * (long)color.r;
	sum[1] = size * (long)color.g;
	sum[2] = size * (long)color.b;
	i = 0;
	while (i < size)
		buffer[i++] = color;
}

void	apply_blur(t_app *app, int radius)
{
	mlx_color		buffer[MAX_BLUR_RADIUS];
	unsigned int	row;
	mlx_color		color;
	unsigned int	y;
	long			sum[3] = {0};
	int				x;

	row = 0;
	while (row < app->frame_buffer.width * app->frame_buffer.height)
	{
		clear_buffer(buffer, sum, get_pixel_opt(app->frame_buffer.buffer, row),
			radius);
		y = 0;
		while (y < app->frame_buffer.height)
		{
			sum[0] -= buffer[y % radius].r;
			sum[1] -= buffer[y % radius].g;
			sum[2] -= buffer[y % radius].b;
			color = get_pixel_opt(app->frame_buffer.buffer, row + y);
			sum[0] += color.r;
			sum[1] += color.g;
			sum[2] += color.b;
			buffer[y % radius] = color;
			set_pixel_opt(app->frame_buffer.shader_buffer, row + y,
				(mlx_color){.r = sum[0] / radius, .g = sum[1] / radius,
				.b = sum[2] / radius, .a = 255});
			y++;
		}
		row += app->frame_buffer.height;
	}
	y = 0;
	while (y < app->frame_buffer.height)
	{
		clear_buffer(buffer, sum, get_pixel_opt(app->frame_buffer.shader_buffer,
				y), radius);
		x = 0;
		row = 0;
		while (x < app->frame_buffer.width)
		{
			sum[0] -= buffer[x % radius].r;
			sum[1] -= buffer[x % radius].g;
			sum[2] -= buffer[x % radius].b;
			color = get_pixel_opt(app->frame_buffer.shader_buffer, row + y);
			sum[0] += color.r;
			sum[1] += color.g;
			sum[2] += color.b;
			buffer[x % radius] = color;
			set_pixel_opt(app->frame_buffer.buffer, row + y,
				(mlx_color){.r = sum[0] / radius, .g = sum[1] / radius,
				.b = sum[2] / radius, .a = 255});
			x++;
			row += app->frame_buffer.height;
		}
		y++;
	}
}
