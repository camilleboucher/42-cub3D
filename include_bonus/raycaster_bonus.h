/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 14:11:08 by cboucher          #+#    #+#             */
/*   Updated: 2026/11/18 23:46:42 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_BONUS_H
# define RAYCASTER_BONUS_H

typedef struct s_hit_info
{
	char			cell_id;
	/* Raycaster variable */
	t_vec2f			ray_dir;
	t_vec2i			map_pos;
	t_vec2f			side_dist;
	t_vec2f			delta_dist;
	t_vec2f			ray_step;
	unsigned int	screen_x;
	int				line_height;
	int				tex_x;
	int				side;
	double			perp_wall_dist;
	double			wall_x;
	/* Line filling variables */
	t_region		*image;
	int				draw_start;
	int				draw_end;
	double			step;
	unsigned int	y;
	unsigned int	fb_row;
	unsigned int	tex_row;

	int				tex_pos;
	double			scale;
	double			stepstep;

}					t_hit_info;

typedef struct s_raycaster
{
	t_vec2f			camera_pos;
	double			camera_rot;
	t_vec2f			camera_dir;
}					t_raycaster;

typedef struct s_sprite_render_info
{
	t_region		*texture;
	int				sprite_screen_x;
	t_vec2i			sprite_size;
	t_vec2f			transformed;
	t_vec2i			draw_start;
	t_vec2i			draw_end;
	int				v_offset;
}					t_sprite_render_info;

void				draw_raycast(t_app *app, t_raycaster *raycaster);
void				draw_players(t_app *app, t_vec2f plane,
						t_raycaster *raycaster);

void				set_delta_dist(t_hit_info *hit);
t_vec2f				compute_plane(t_app *app, t_raycaster *raycaster);
void				compute_perp_wall_dist(t_app *app, t_hit_info *hit);
void				compute_wall_x(t_hit_info *hit, t_raycaster *raycaster);
void				set_side_dist_and_step_values(t_hit_info *hit,
						t_raycaster *raycaster);

void				draw_vertical_line(t_app *app, t_hit_info *hit);
void				draw_vertical_line_door(t_app *app, t_hit_info *hit);
mlx_color			blend_colors(mlx_color a, mlx_color b);

void				quick_players_sort(double dists[4], int players[4],
						int player_count);

#endif
