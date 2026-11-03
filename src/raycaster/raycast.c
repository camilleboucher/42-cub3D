/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.642.fr>          +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/27 18:649:164 by yben-dje          #+#    #+#             */
/*   Updated: 2026/10/07 14:30:33 by cboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	max(int a, int b)
{
	if (a < b)
		return (b);
	return (a);
}

typedef struct s_hit_info
{
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

void	screen_to_texture_line(t_app *app, t_hit_info *hit)
{
	double		tex_pos;
	mlx_color	color;

	tex_pos = (hit->draw_start - app->frame_buffer.height / 2.
			+ hit->line_height / 2.) * hit->step;
	while (hit->y < hit->draw_end)
	{
		tex_pos += hit->step;
		color = get_pixel_opt(hit->image, hit->tex_row
				+ ((unsigned int)tex_pos & (64 - 1)));
		set_pixel_opt(app->frame_buffer.buffer, hit->fb_row + hit->y++, color);
	}
}

void	texture_to_screen_fill(t_app *app, t_hit_info *hit, int stop) {
	mlx_color	color;
	while (hit->tex_pos < stop)
	{
		hit->stepstep += hit->scale;
		color = get_pixel_opt(hit->image, hit->tex_row
				+ ((unsigned int)hit->tex_pos & (64 - 1)));
		while (hit->y < hit->stepstep - 1e-6)
			set_pixel_opt(app->frame_buffer.buffer, hit->fb_row + hit->y++,
				color);
		hit->tex_pos++;
	}
	if (hit->tex_pos < 64 && hit->stepstep + hit->scale >= app->frame_buffer.height - 1)
	{
		color = get_pixel_opt(hit->image, hit->tex_row
				+ ((unsigned int)hit->tex_pos & (64 - 1)));
		while (hit->y < app->frame_buffer.height)
			set_pixel_opt(app->frame_buffer.buffer, hit->fb_row + hit->y++,
				color);
	}
}

void	texture_to_screen_line(t_app *app, t_hit_info *hit)
{
	int			stop;
	mlx_color	color;

	hit->tex_pos = 0;
	hit->scale = 1. / hit->step;
	hit->stepstep = (((int)app->frame_buffer.height - hit->line_height) / 2.);
	if (hit->stepstep < -hit->scale)
		hit->stepstep = fmod(hit->stepstep, hit->scale);
	stop = 64;
	if (hit->line_height > app->frame_buffer.height)
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
	hit->draw_start = ((int)app->frame_buffer.height - hit->line_height) / 2;
	if (hit->draw_start < 0)
		hit->draw_start = 0;
	hit->draw_end = ((int)app->frame_buffer.height + hit->line_height) / 2;
	if (hit->draw_end > app->frame_buffer.height)
		hit->draw_end = app->frame_buffer.height;
	hit->step = 64. / (double)hit->line_height;
	hit->y = 0;
	hit->fb_row = hit->screen_x * app->frame_buffer.buffer->height;
	while (hit->y < hit->draw_start)
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

void	set_hit_info_side(int side, t_vec2f ray_dir, t_hit_info *hit)
{
	if (side == 0 && ray_dir.x > 0)
		hit->tex_x = 64 - hit->tex_x - 1;
	if (side == 1 && ray_dir.y < 0)
		hit->tex_x = 64 - hit->tex_x - 1;
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
		if (map_get(&app->map, hit->map_pos.x, hit->map_pos.y) != 2)
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

void	compute_perp_wall_dist(t_hit_info *hit)
{
	if (hit->side == 0)
		hit->perp_wall_dist = hit->side_dist.x - hit->delta_dist.x;
	else
		hit->perp_wall_dist = hit->side_dist.y - hit->delta_dist.y;
}

double	compute_wall_x(t_hit_info *hit, t_raycaster *raycaster)
{
	double	wall_x;

	if (hit->side == 0)
		wall_x = raycaster->camera_pos.y + hit->perp_wall_dist * hit->ray_dir.y;
	else
		wall_x = raycaster->camera_pos.x + hit->perp_wall_dist * hit->ray_dir.x;
	wall_x -= floorf(wall_x);
	hit->tex_x = ((1. - 1e-6) - wall_x) * 64.;
	return (wall_x);
}

void update_hit_with_screen_x(t_app *app, t_hit_info *hit, t_raycaster *raycaster, t_vec2f plane)
{
    double camera_x;

    camera_x = 2 * hit->screen_x / (double)app->frame_buffer.width - 1;
    hit->ray_dir = (t_vec2f){raycaster->camera_dir.x + plane.x * camera_x,
        raycaster->camera_dir.y + plane.y * camera_x};
    hit->map_pos = (t_vec2i){(int)raycaster->camera_pos.x,
        (int)raycaster->camera_pos.y};
}

void	draw_raycast(t_app *app, t_raycaster *raycaster)
{
	t_vec2f		plane;
	t_hit_info	hit;
	double wall_x;

	plane = compute_plane(app, raycaster);
	hit.screen_x = 0;
	while (hit.screen_x < app->frame_buffer.width)
	{
		update_hit_with_screen_x(app, &hit, raycaster, plane);
		set_delta_dist(app, &hit);
		set_side_dist_and_step_values(&hit, raycaster);
		walk_raycaster(app, &hit);
		compute_perp_wall_dist(&hit);
		if (hit.perp_wall_dist < 0)
			return ;
		wall_x = compute_wall_x(&hit, raycaster);
		hit.line_height = (int)app->frame_buffer.height / hit.perp_wall_dist;
		set_hit_info_side(hit.side, hit.ray_dir, &hit);
		hit.image = app->image_atlas.images[3 + hit.side];
		draw_vertical_line(app, &hit);
		hit.screen_x++;
	}
}
