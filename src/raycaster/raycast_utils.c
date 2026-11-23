/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 17:25:50 by yben-dje          #+#    #+#             */
/*   Updated: 2026/11/20 17:27:43 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	set_delta_dist(t_hit_info *hit)
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
