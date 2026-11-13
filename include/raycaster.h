/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboucher <private_mail>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 14:11:08 by cboucher          #+#    #+#             */
/*   Updated: 2026/10/07 14:11:12 by cboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_H
# define RAYCASTER_H

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

void				draw_raycast(t_app *app, t_raycaster *raycaster);

#endif
