/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 18:43:03 by cboucher          #+#    #+#             */
/*   Updated: 2026/11/19 00:21:49 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "raycaster.h"
#include <math.h>

void	set_hit_info_side(int side, t_vec2f ray_dir, t_hit_info *hit)
{
	if (side)
	{
		if (ray_dir.y > 0)
			hit->side = 0;
		else
			hit->side = 1;
	}
	else
	{
		if (ray_dir.x > 0)
			hit->side = 2;
		else
			hit->side = 3;
	}
}

void	set_side_dist_and_step_values(t_hit_info *hit, t_raycaster *raycaster)
{
	if (hit->ray_dir.x < 0)
	{
		hit->ray_step.x = -1.;
		hit->side_dist.x = (raycaster->camera_pos.x - hit->map_pos.x)
			* hit->delta_dist.x;
	}
	else
	{
		hit->ray_step.x = 1.;
		hit->side_dist.x = (hit->map_pos.x + 1. - raycaster->camera_pos.x)
			* hit->delta_dist.x;
	}
	if (hit->ray_dir.y < 0)
	{
		hit->ray_step.y = -1.;
		hit->side_dist.y = (raycaster->camera_pos.y - hit->map_pos.y)
			* hit->delta_dist.y;
	}
	else
	{
		hit->ray_step.y = 1.;
		hit->side_dist.y = (hit->map_pos.y + 1. - raycaster->camera_pos.y)
			* hit->delta_dist.y;
	}
}

void	walk_raycaster(t_app *app, t_hit_info *hit)
{
	while (1)
	{
		if (hit->side_dist.x < hit->side_dist.y)
		{
			hit->side_dist.x += hit->delta_dist.x;
			hit->map_pos.x += hit->ray_step.x;
			hit->side = 0;
		}
		else
		{
			hit->side_dist.y += hit->delta_dist.y;
			hit->map_pos.y += hit->ray_step.y;
			hit->side = 1;
		}
		hit->cell_id = map_get(&app->map, hit->map_pos.x, hit->map_pos.y);
		if (hit->cell_id != 2)
			break ;
	}
}

void	set_delta_dist(t_app *app, t_hit_info *hit)
{
	if (hit->ray_dir.x == 0.)
		hit->delta_dist.x = 1e30;
	else
		hit->delta_dist.x = fabs(1. / hit->ray_dir.x);
	if (hit->ray_dir.y == 0.)
		hit->delta_dist.y = 1e30;
	else
		hit->delta_dist.y = fabs(1. / hit->ray_dir.y);
}

t_vec2f	compute_plane(t_app *app, t_raycaster *raycaster)
{
	t_vec2f	plane;

	plane.x = -raycaster->camera_dir.y;
	plane.y = raycaster->camera_dir.x;
	plane = vec2f_normalize(plane);
	plane = vec2f_mul(plane, (double)app->frame_buffer.width
			/ (double)app->frame_buffer.height * 0.5);
	return (plane);
}

void	compute_perp_wall_dist(t_app *app, t_hit_info *hit)
{
	if (hit->side == 0)
		hit->perp_wall_dist = hit->side_dist.x - hit->delta_dist.x;
	else
		hit->perp_wall_dist = hit->side_dist.y - hit->delta_dist.y;
	app->frame_buffer.z_buffer[hit->screen_x] = hit->perp_wall_dist;
}

void	compute_wall_x(t_hit_info *hit, t_raycaster *raycaster)
{
	if (hit->side == 0)
		hit->wall_x = raycaster->camera_pos.y + hit->perp_wall_dist
			* hit->ray_dir.y;
	else
		hit->wall_x = raycaster->camera_pos.x + hit->perp_wall_dist
			* hit->ray_dir.x;
	hit->wall_x -= floor(hit->wall_x);
}

void	update_hit_with_screen_x(t_app *app, t_hit_info *hit,
		t_raycaster *raycaster, t_vec2f plane)
{
	double	camera_x;

	camera_x = 2 * hit->screen_x / (double)app->frame_buffer.width - 1;
	hit->ray_dir = (t_vec2f){raycaster->camera_dir.x + plane.x * camera_x,
		raycaster->camera_dir.y + plane.y * camera_x};
	hit->map_pos = (t_vec2i){(int)raycaster->camera_pos.x,
		(int)raycaster->camera_pos.y};
}

void	draw_door_transparency(t_app *app, t_raycaster *raycaster,
		t_hit_info *hit)
{
	unsigned int	i;

	i = hit->screen_x * app->frame_buffer.height;
	while (i < (hit->screen_x + 1) * app->frame_buffer.height)
		set_pixel_opt(app->frame_buffer.buffer, i++, (mlx_color){.rgba = 0x0});
	while (true)
	{
		if (hit->cell_id >= ID_DOOR_CLOSED)
			hit->image = app->image_atlas.images[20 + hit->cell_id];
		else
			hit->image = app->image_atlas.images[3 + hit->side];
		draw_vertical_line(app, hit, true);
		if (hit->cell_id < ID_DOOR_CLOSED)
			break ;
		walk_raycaster(app, hit);
		compute_perp_wall_dist(app, hit);
		if (hit->perp_wall_dist < 0)
			return ;
		compute_wall_x(hit, raycaster);
		hit->line_height = (int)app->frame_buffer.height / hit->perp_wall_dist;
		set_hit_info_side(hit->side, hit->ray_dir, hit);
	}
}

void	draw_raycast(t_app *app, t_raycaster *raycaster)
{
	t_vec2f		plane;
	t_hit_info	hit;

	plane = compute_plane(app, raycaster);
	hit.screen_x = 0;
	while (hit.screen_x < app->frame_buffer.width)
	{
		update_hit_with_screen_x(app, &hit, raycaster, plane);
		set_delta_dist(app, &hit);
		set_side_dist_and_step_values(&hit, raycaster);
		walk_raycaster(app, &hit);
		compute_perp_wall_dist(app, &hit);
		if (hit.perp_wall_dist < 0.)
			return ;
		compute_wall_x(&hit, raycaster);
		hit.line_height = (int)app->frame_buffer.height / hit.perp_wall_dist;
		set_hit_info_side(hit.side, hit.ray_dir, &hit);
		if (hit.cell_id >= ID_DOOR_CLOSED)
			draw_door_transparency(app, raycaster, &hit);
		else
		{
			hit.image = app->image_atlas.images[3 + hit.side];
			draw_vertical_line(app, &hit, false);
		}
		hit.screen_x++;
	}
	draw_players(app, plane, raycaster);
}
