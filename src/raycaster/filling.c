/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filling.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 16:58:52 by yben-dje          #+#    #+#             */
/*   Updated: 2026/11/20 16:58:52 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "frame_buffer.h"

int	max(int a, int b)
{
	if (a < b)
		return (b);
	return (a);
}

void	screen_to_texture_line(t_app *app, t_hit_info *hit)
{
	double		tex_pos;
	mlx_color	color;

	tex_pos = (hit->draw_start - app->frame_buffer.height / 2.
			+ hit->line_height / 2.) * hit->step;
	while ((int)hit->y < hit->draw_end)
	{
		tex_pos += hit->step;
		if ((unsigned int)tex_pos >= hit->image->height)
			break ;
		color = get_pixel_opt(hit->image, hit->tex_row
				+ ((unsigned int)tex_pos));
		set_pixel_opt(app->frame_buffer.buffer, hit->fb_row + hit->y++, color);
	}
}

void	texture_to_screen_fill(t_app *app, t_hit_info *hit, int stop)
{
	mlx_color	color;

	while (hit->tex_pos < stop)
	{
		hit->stepstep += hit->scale;
		color = get_pixel_opt(hit->image, hit->tex_row
				+ ((unsigned int)hit->tex_pos % (hit->image->height)));
		while (hit->y < hit->stepstep - 1e-6
			&& hit->y < app->frame_buffer.height)
			set_pixel_opt(app->frame_buffer.buffer, hit->fb_row + hit->y++, color);
		hit->tex_pos++;
	}
	if (hit->tex_pos < (int)hit->image->height && hit->stepstep
		+ hit->scale >= app->frame_buffer.height - 1)
	{
		color = get_pixel_opt(hit->image, hit->tex_row
				+ ((unsigned int)hit->tex_pos % (hit->image->height)));
		while (hit->y < app->frame_buffer.height)
			set_pixel_opt(app->frame_buffer.buffer, hit->fb_row + hit->y++, color);
	}
}

void	texture_to_screen_line(t_app *app, t_hit_info *hit)
{
	int	stop;

	hit->tex_pos = 0;
	hit->scale = 1. / hit->step;
	hit->stepstep = (((int)app->frame_buffer.height - hit->line_height) / 2.);
	if (hit->stepstep < -hit->scale)
		hit->stepstep = fmod(hit->stepstep, hit->scale);
	stop = hit->image->height;
	if (hit->line_height > (int)app->frame_buffer.height)
	{
		hit->tex_pos += (int)((hit->line_height - app->frame_buffer.height)
				* hit->step) / 2;
		stop -= (int)((hit->line_height - app->frame_buffer.height) * hit->step)
			/ 2;
		stop -= max((hit->stepstep + hit->scale * (stop - hit->tex_pos))
				- (app->frame_buffer.height - 1), 0) / hit->scale;
	}
	texture_to_screen_fill(app, hit, stop);
}

void	draw_vertical_line(t_app *app, t_hit_info *hit)
{
	hit->tex_x = ((1. - 1e-6) - hit->wall_x) * (double)hit->image->width;
	hit->draw_start = ((int)app->frame_buffer.height - hit->line_height) / 2;
	if (hit->draw_start < 0)
		hit->draw_start = 0;
	hit->draw_end = ((int)app->frame_buffer.height + hit->line_height) / 2;
	if (hit->draw_end > (int)app->frame_buffer.height)
		hit->draw_end = app->frame_buffer.height;
	hit->step = ((double)hit->image->height + 1e-6) / (double)hit->line_height;
	hit->y = 0;
	hit->fb_row = hit->screen_x * app->frame_buffer.buffer->height;
	while ((int)hit->y < hit->draw_start)
		set_pixel_opt(app->frame_buffer.buffer, hit->fb_row + hit->y++,
			app->map.ceil_color);
	hit->tex_row = hit->tex_x * hit->image->height;
	if (hit->step >= 2.)
		screen_to_texture_line(app, hit);
	else if (hit->step > 0.)
		texture_to_screen_line(app, hit);
	while (hit->y < app->frame_buffer.height)
		set_pixel_opt(app->frame_buffer.buffer, hit->fb_row + hit->y++,
			app->map.floor_color);
}
