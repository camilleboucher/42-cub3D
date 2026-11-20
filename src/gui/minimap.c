/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 18:03:32 by yben-dje          #+#    #+#             */
/*   Updated: 2026/11/20 18:03:32 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double	decimal(double a)
{
	if (a < 0.)
		return (a - ceil(a));
	return (a - floor(a));
}

void	minimap_put_tile(t_app *app, t_vec2i map_pos, int scare_size,
		t_vec2i screen_pos)
{
	char	cell_type;

	cell_type = map_get(&app->map, map_pos.x, map_pos.y);
	if (map_pos.x >= 0 && map_pos.x < app->map.width && map_pos.y >= 0
		&& map_pos.y < app->map.height)
	{
		if (cell_type == 1)
			draw_image_strech(app->frame_buffer.minimap_frame_buffer,
				screen_pos, (t_vec2i){scare_size, scare_size},
				app->image_atlas.images[32]);
		else if (cell_type >= 3 && cell_type <= 6)
			draw_image_strech(app->frame_buffer.minimap_frame_buffer,
				screen_pos, (t_vec2i){scare_size, scare_size},
				app->image_atlas.images[30 + cell_type]);
		else
			draw_rect_checked(app->frame_buffer.minimap_frame_buffer,
				screen_pos, (t_vec2i){scare_size, scare_size},
				(mlx_color){.rgba = 0xFFFFFFFF});
	}
	else
		draw_rect_checked(app->frame_buffer.minimap_frame_buffer, screen_pos,
			(t_vec2i){scare_size, scare_size}, (mlx_color){.rgba = 0xFFFFFFFF});
}

void	render_map_to_buffer(t_app *app, int dist, int canvas_size, int offset)
{
	t_vec2i	map_pos;
	int		scare_size;
	t_vec2i	screen_pos;

	scare_size = canvas_size / (dist * 2);
	map_pos.x = ceil(app->players[0].pos.x - dist);
	screen_pos = (t_vec2i){(int)((1. - decimal(app->players[0].pos.x) - 1.)
			* (double)scare_size) - scare_size + offset, 0};
	while (map_pos.x <= app->players[0].pos.x + (double)dist + 1)
	{
		map_pos.y = ceil(app->players[0].pos.y - dist);
		screen_pos.y = (int)((1. - decimal(app->players[0].pos.y) - 1.)
				* (double)scare_size) - scare_size + offset;
		while (map_pos.y <= app->players[0].pos.y + (double)dist + 1)
		{
			minimap_put_tile(app, map_pos, scare_size, screen_pos);
			map_pos.y++;
			screen_pos.y += scare_size;
		}
		map_pos.x++;
		screen_pos.x += scare_size;
	}
}

void	draw_overlay(t_app *app, t_vec2i size, t_vec2i indicator_size)
{
	clear_region(app->frame_buffer.minimap_overlay_frame_buffer,
		(mlx_color){.rgba = 0x00000000});
	draw_image_strech(app->frame_buffer.minimap_overlay_frame_buffer,
		(t_vec2i){0, 0}, size, app->image_atlas.images[31]);
	draw_image_strech(app->frame_buffer.minimap_overlay_frame_buffer,
		(t_vec2i){(cos(-app->players[0].angle - M_PI / 2.) * size.x) / 2,
		(sin(-app->players[0].angle - M_PI / 2.) * size.y) / 2}, indicator_size,
		app->image_atlas.images[27]);
	draw_image_strech(app->frame_buffer.minimap_overlay_frame_buffer,
		(t_vec2i){(cos(-app->players[0].angle + M_PI / 2.) * size.x) / 2,
		(sin(-app->players[0].angle + M_PI / 2.) * size.y) / 2}, indicator_size,
		app->image_atlas.images[28]);
	draw_image_strech(app->frame_buffer.minimap_overlay_frame_buffer,
		(t_vec2i){(cos(-app->players[0].angle) * size.x) / 2,
		(sin(-app->players[0].angle) * size.y) / 2}, indicator_size,
		app->image_atlas.images[29]);
	draw_image_strech(app->frame_buffer.minimap_overlay_frame_buffer,
		(t_vec2i){(cos(-app->players[0].angle - M_PI) * size.x) / 2,
		(sin(-app->players[0].angle - M_PI) * size.y) / 2}, indicator_size,
		app->image_atlas.images[30]);
}

void	render_minimap(t_app *app)
{
	t_vec2i	size;
	t_vec2i	indicator_size;

	size = (t_vec2i){app->minimap.size.x / 4 * 3, app->minimap.size.y / 4 * 3};
	indicator_size = (t_vec2i){app->minimap.size.x / 4, app->minimap.size.y
		/ 4};
	draw_overlay(app, size, indicator_size);
	render_map_to_buffer(app, 5, app->minimap.size.x, -app->minimap.size.x / 4);
	mid_point_disc(app, (double)size.x / 2.08, (t_vec2i){app->minimap.pos.x / 2,
		app->minimap.pos.y / 2});
	draw_rect_raw(app->frame_buffer.minimap_frame_buffer, (t_vec2i){0, 0},
		(t_vec2i){(app->minimap.size.x - size.x / 2.1) / 4,
		app->minimap.size.y}, (mlx_color){.rgba = 0x00000000});
	draw_rect_raw(app->frame_buffer.minimap_frame_buffer,
		(t_vec2i){app->minimap.size.x - (app->minimap.size.x - size.x / 2.1) / 4
		+ 1, 0}, (t_vec2i){(app->minimap.size.x - size.x / 2.1) / 4,
		app->minimap.size.y}, (mlx_color){.rgba = 0x00000000});
}
