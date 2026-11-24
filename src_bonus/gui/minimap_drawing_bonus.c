/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_drawing_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 18:12:45 by yben-dje          #+#    #+#             */
/*   Updated: 2026/11/20 18:12:45 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	mask_out_vert_line(t_app *app, unsigned int x, unsigned int start,
		unsigned int stop)
{
	int	y;
	int	row;

	y = 0;
	row = x * app->frame_buffer.minimap_fb->height;
	while (y <= (int)start)
		set_pixel_opt(app->frame_buffer.minimap_fb, row + y++,
			(mlx_color){.rgba = 0x00000000});
	y = stop;
	while (y < app->minimap.size.y)
		set_pixel_opt(app->frame_buffer.minimap_fb, row + y++,
			(mlx_color){.rgba = 0x00000000});
}

void	mid_point_disc(t_app *app, double r, t_vec2i center)
{
	double	t1;
	int		x;
	int		y;
	double	t2;

	t1 = r / 16;
	x = r;
	y = 0;
	while (x >= y)
	{
		mask_out_vert_line(app, center.x - x, center.y - y, center.y + y);
		mask_out_vert_line(app, center.x + x, center.y - y, center.y + y);
		mask_out_vert_line(app, center.x + y, center.y - x, center.y + x);
		mask_out_vert_line(app, center.x - y, center.y - x, center.y + x);
		y++;
		t1 += y;
		t2 = t1 - x;
		if (t2 >= 0)
		{
			t1 = t2;
			x--;
		}
	}
}

void	draw_rect_checked(t_region *buffer, t_vec2i pos, t_vec2i size,
		mlx_color color)
{
	int		x;
	int		y;
	t_vec2i	stop;
	int		y_start;

	pos.x += ((int)buffer->width - (int)size.x) / 2;
	pos.y += ((int)buffer->height - (int)size.y) / 2;
	stop = (t_vec2i){pos.x + size.x, pos.y + size.y};
	x = pos.x;
	if (pos.x < 0)
		x = 0;
	y_start = pos.y;
	if (y_start < 0)
		y_start = 0;
	if (stop.x > (int)buffer->width)
		stop.x = buffer->width;
	if (stop.y > (int)buffer->height)
		stop.y = buffer->height;
	while (x < stop.x)
	{
		y = y_start;
		while (y < stop.y)
			set_pixel(buffer, x, y++, color);
		x++;
	}
}

void	draw_rect_raw(t_region *buffer, t_vec2i pos, t_vec2i size,
		mlx_color color)
{
	int		x;
	int		y;
	t_vec2i	stop;
	int		y_start;

	stop = (t_vec2i){pos.x + size.x, pos.y + size.y};
	x = pos.x;
	if (pos.x < 0)
		x = 0;
	y_start = pos.y;
	if (y_start < 0)
		y_start = 0;
	if (stop.x > (int)buffer->width)
		stop.x = buffer->width;
	if (stop.y > (int)buffer->height)
		stop.y = buffer->height;
	while (x < stop.x)
	{
		y = y_start;
		while (y < stop.y)
			set_pixel(buffer, x, y++, color);
		x++;
	}
}
