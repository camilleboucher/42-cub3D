/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 18:58:29 by yben-dje          #+#    #+#             */
/*   Updated: 2026/11/20 18:58:29 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

mlx_color	blend_colors(mlx_color a, mlx_color b)
{
	mlx_color	merged;

	if (b.a == 0xFF)
		return (b);
	if (a.a + b.a > 0xFF)
	{
		b.a = 0xFF - a.a;
	}
	merged.a = a.a + b.a;
	merged.r = (a.r * a.a) / 0xFF + (b.r * b.a) / 0xFF;
	merged.g = (a.g * a.a) / 0xFF + (b.g * b.a) / 0xFF;
	merged.b = (a.b * a.a) / 0xFF + (b.b * b.a) / 0xFF;
	return (merged);
}

bool	point_to_box_collision(t_app *app, t_vec2i box_pos, t_vec2i box_size,
		t_vec2i point_pos)
{
	point_pos.x -= (app->frame_buffer.width - box_size.x) / 2;
	point_pos.y -= (app->frame_buffer.height - box_size.y) / 2;
	return (point_pos.x > box_pos.x && point_pos.x < box_pos.x + box_size.x
		&& point_pos.y > box_pos.y && point_pos.y < box_pos.y + box_size.y);
}

bool	box_to_box_collision(t_vec2i pos1, t_vec2i size1, t_vec2i pos2,
		t_vec2i size2)
{
	return (pos1.x + size1.x >= pos2.x && pos1.x <= pos2.x + size2.x && pos1.y
		+ size1.y >= pos2.y && pos1.y <= pos2.y + size2.y);
}

bool	mouse_perfect_collision(t_app *app, t_vec2i pos, t_vec2i size,
		t_region *image)
{
	mlx_color	pixel;

	if (!point_to_box_collision(app, pos, size, app->input_handler.mouse_pos))
		return (false);
	pixel = get_pixel(image, (app->input_handler.mouse_pos.x - pos.x
				- (int)app->frame_buffer.width / 2) * (int)image->width / size.x
			+ (int)image->width / 2, (app->input_handler.mouse_pos.y - pos.y
				- ((int)app->frame_buffer.height) / 2) * (int)image->height
			/ size.y + (int)image->height / 2);
	if (pixel.a != 0)
		return (true);
	return (false);
}
