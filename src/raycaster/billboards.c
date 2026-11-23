/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   billboards.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 23:49:06 by yannis            #+#    #+#             */
/*   Updated: 2026/11/19 15:08:25 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <stdio.h>

static void	v_scan_line(t_frame_buffer *buffer, t_sprite_render_info *info,
		int tex_x, int x)
{
	int			y;
	int			d;
	int			tex_y;
	mlx_color	color;
	int			raw;

	y = info->draw_start.y;
	raw = x * buffer->height;
	while (y <= info->draw_end.y)
	{
		d = (y - info->v_offset) * 256 - buffer->height * 128
			+ info->sprite_size.y * 128;
		tex_y = (d * info->texture->height / info->sprite_size.y) / 256;
		color = get_pixel(info->texture, tex_x, tex_y);
		if (color.a > 100)
			set_pixel_opt(buffer->buffer, raw + y, color);
		y++;
	}
}

void	display_sprite(t_frame_buffer *buffer, t_sprite_render_info *info)
{
	int	x;
	int	tex_x;

	x = info->draw_start.x;
	while (x <= info->draw_end.x)
	{
		tex_x = (int)(256 * (x - (info->sprite_screen_x - info->sprite_size.x
						/ 2)) * info->texture->width / info->sprite_size.x)
			/ 256;
		if (info->transformed.y > 0 && info->transformed.y < buffer->z_buffer[x]
			&& x >= 0 && x < (int)buffer->width)
			v_scan_line(buffer, info, tex_x, x);
		x++;
	}
}

void	display_single_player(t_frame_buffer *buffer,
		t_sprite_render_info *info)
{
	info->v_offset = (.20 * buffer->height) / info->transformed.y;
	info->draw_start.y = ((int)buffer->height - info->sprite_size.y) / 2
		+ info->v_offset + 1;
	info->draw_end.y = info->draw_start.y + info->sprite_size.y - 2;
	if (info->draw_start.y < 0)
		info->draw_start.y = 0;
	if (info->draw_end.y >= (int)buffer->height)
		info->draw_end.y = (int)buffer->height - 1;
	info->draw_start.x = info->sprite_screen_x - info->sprite_size.x / 2;
	info->draw_end.x = info->draw_start.x + info->sprite_size.x - 1;
	if (info->draw_start.x < 0)
		info->draw_start.x = 0;
	if (info->draw_end.x >= (int)buffer->width)
		info->draw_end.x = (int)buffer->width - 1;
	display_sprite(buffer, info);
}

void	draw_single_player(t_app *app, int player_i, t_vec2f plane,
		t_raycaster *raycaster)
{
	t_sprite_render_info	info;
	t_vec2f					sprite_pos;
	t_vec2f					transformed;
	const double			inv_det = 1. / (plane.x * raycaster->camera_dir.y
			- raycaster->camera_dir.x * plane.y);

	sprite_pos = vec2f_sub(app->players[player_i].pos, raycaster->camera_pos);
	transformed.x = raycaster->camera_dir.y * sprite_pos.x
		- raycaster->camera_dir.x * sprite_pos.y;
	transformed.y = -plane.y * sprite_pos.x + plane.x * sprite_pos.y;
	transformed = vec2f_mul(transformed, inv_det);
	info.sprite_screen_x = (int)(((double)app->frame_buffer.width / 2.) * (1.
				+ transformed.x / transformed.y));
	info.sprite_size.x = fabs((double)app->frame_buffer.height / transformed.y)
		* .8;
	info.sprite_size.y = fabs((double)app->frame_buffer.height / transformed.y)
		* .8;
	info.transformed = transformed;
	info.texture = app->image_atlas.images[37 + player_i];
	display_single_player(&app->frame_buffer, &info);
}

void	draw_players(t_app *app, t_vec2f plane, t_raycaster *raycaster)
{
	double	dists[4];
	int		players_index[4];

	dists[0] = vec2f_dist(raycaster->camera_pos, app->players[0].pos);
	if (app->input_handler.player_count > 1)
		dists[1] = vec2f_dist(raycaster->camera_pos, app->players[1].pos);
	if (app->input_handler.player_count > 2)
		dists[2] = vec2f_dist(raycaster->camera_pos, app->players[2].pos);
	if (app->input_handler.player_count > 3)
		dists[3] = vec2f_dist(raycaster->camera_pos, app->players[3].pos);
	players_index[0] = 0;
	players_index[1] = 1;
	players_index[2] = 2;
	players_index[3] = 3;
	quick_players_sort(dists, players_index, app->input_handler.player_count);
	if (app->input_handler.player_count > 1)
		draw_single_player(app, players_index[0], plane, raycaster);
	if (app->input_handler.player_count > 2)
		draw_single_player(app, players_index[1], plane, raycaster);
	if (app->input_handler.player_count > 3)
		draw_single_player(app, players_index[2], plane, raycaster);
}
