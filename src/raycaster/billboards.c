/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   billboards.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 23:49:06 by yannis            #+#    #+#             */
/*   Updated: 2026/11/18 23:49:35 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "frame_buffer.h"
#include "mlx.h"
#include "raycaster.h"
#include "structs.h"
#include "vector.h"
#include <stdio.h>
#include <stdlib.h>

void display_sprite(t_frame_buffer *buffer, t_sprite_render_info *info)
{
	int		x;
	x = info->draw_start.x;
	while (x < info->draw_end.x) {
		int tex_x = (int)(256 * (x - (info->sprite_screen_x - info->sprite_size.x / 2)) *
											info->texture->width / info->sprite_size.x) / 256;
		if (info->transformed.y > 0 && info->transformed.y < buffer->z_buffer[x] && x > 0 &&
				x < buffer->width) {
			int y;
			y = info->draw_start.y + 1;
			while (y <= info->draw_end.y) {
				int d =
						(y - info->v_offset) * 256 - buffer->height * 128 + info->sprite_size.y * 128;
				int tex_y = (d * info->texture->height / info->sprite_size.y) / 256;
				mlx_color color = get_pixel(info->texture, tex_x, tex_y);
				if (color.a > 100)
					set_pixel(buffer->buffer, x, y, color);
				y++;
			}
		}
		x++;
	}
}

void display_single_player(t_frame_buffer *buffer, t_sprite_render_info *info)
{
	

	info->v_offset = (.20 * info->texture->height) / info->transformed.y;
	info->draw_start.y = ((int)buffer->height - info->sprite_size.y) / 2 + info->v_offset;
	info->draw_end.y = info->draw_start.y + info->sprite_size.y;
	if (info->draw_start.y < 0)
		info->draw_start.y = 0;
	if (info->draw_end.y >= (int)buffer->height)
		info->draw_end.y = (int)buffer->height - 1;
	info->draw_start.x = info->sprite_screen_x - info->sprite_size.x / 2;
	info->draw_end.x = info->draw_start.x + info->sprite_size.x;
	if (info->draw_start.x < 0)
		info->draw_start.x = 0;
	if (info->draw_end.x >= (int)buffer->width)
		info->draw_end.x = (int)buffer->width - 1;
	display_sprite(buffer, info);
}

void draw_single_player(t_app *app, int player_i, t_vec2f plane, t_raycaster *raycaster) {
	t_sprite_render_info	info;
	t_vec2f sprite_pos =
			vec2f_sub(app->players[player_i].pos, raycaster->camera_pos);
	t_vec2f transformed;
	const double inv_det = 1. / (plane.x * raycaster->camera_dir.y -
															 raycaster->camera_dir.x * plane.y);
	transformed.x = raycaster->camera_dir.y * sprite_pos.x -
									raycaster->camera_dir.x * sprite_pos.y;
	transformed.y = -plane.y * sprite_pos.x + plane.x * sprite_pos.y;
	transformed = vec2f_mul(transformed, inv_det);
	info.sprite_screen_x = (int)(((double)app->frame_buffer.width / 2.) * (1. + transformed.x / transformed.y));
	info.sprite_size.x = abs((double)app->frame_buffer.height / transformed.y) * .8;
	info.sprite_size.y = abs((double)app->frame_buffer.height / transformed.y) * .8;
	info.transformed = transformed;
	info.texture = app->image_atlas.images[37 + player_i];
	display_single_player(&app->frame_buffer, &info);
}

static void swap_players(int *pl_a, int *pl_b, double *dist_a, double *dist_b) {
	int pl_temp;
	double dist_temp;

	if (*dist_a < *dist_b) {
		pl_temp = *pl_b;
		*pl_b = *pl_a;
		*pl_a = pl_temp;
		dist_temp = *dist_b;
		*dist_b = *dist_a;
		*dist_a = dist_temp;
	}
}

void quick_players_sort(double dists[4], int players[4]) {
	int i;
	int j;

	i = 4;
	j = 0;
	while (i) {
		i--;
		j = 0;
		while (j < i) {
			swap_players(&players[j], &players[j + 1], &dists[j], &dists[j + 1]);
			j++;
		}
	}
}

void draw_players(t_app *app, t_vec2f plane, t_raycaster *raycaster) {
	double dists[4];
	int players_index[4];

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
	quick_players_sort(dists, players_index);
	if (app->input_handler.player_count > 1)
		draw_single_player(app, players_index[0], plane, raycaster);
	if (app->input_handler.player_count > 2)
		draw_single_player(app, players_index[1], plane, raycaster);
	if (app->input_handler.player_count > 3)
		draw_single_player(app, players_index[2], plane, raycaster);
}
