/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboucher <private_mail>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 14:18:05 by cboucher          #+#    #+#             */
/*   Updated: 2026/11/20 18:19:11 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static t_vec2i	get_start_pos(t_vec2i pos)
{
	t_vec2i	start_pos;

	start_pos = (t_vec2i){0, 0};
	if (pos.x < 0)
		start_pos.x = -pos.x;
	if (pos.y < 0)
		start_pos.y = -pos.y;
	return (start_pos);
}

static t_vec2i	get_out_size(t_region *buffer, t_vec2i pos, t_vec2i size)
{
	t_vec2i	out_size;

	out_size = size;
	if (pos.x + size.x > (int)buffer->width)
		out_size.x = (int)buffer->width - pos.x;
	if (pos.y + size.y > (int)buffer->height)
		out_size.y = (int)buffer->height - pos.y;
	return (out_size);
}

void	draw_image_strech(t_region *buffer, t_vec2i pos, t_vec2i size,
		t_region *image)
{
	t_vec2i		pix_pos;
	mlx_color	color;
	t_vec2i		out_size;
	t_vec2i		start_pos;

	pos.x += ((int)buffer->width - (int)size.x) / 2;
	pos.y += ((int)buffer->height - (int)size.y) / 2;
	if (pos.x > (int)buffer->width || pos.y > (int)buffer->height || pos.x
		+ size.x < 0 || pos.y + size.y < 0)
		return ;
	out_size = get_out_size(buffer, pos, size);
	start_pos = get_start_pos(pos);
	pix_pos.x = start_pos.x;
	while (pix_pos.x < out_size.x)
	{
		pix_pos.y = start_pos.y;
		while (pix_pos.y < out_size.y)
		{
			color = blend_colors(get_pixel(buffer, pix_pos.x + pos.x, pix_pos.y
						+ pos.y), get_pixel(image, image->width * pix_pos.x
						/ size.x, image->height * pix_pos.y / size.y));
			set_pixel(buffer, pix_pos.x + pos.x, pix_pos.y++ + pos.y, color);
		}
		pix_pos.x++;
	}
}

void	tex_button_draw(t_app *app, t_tex_button button)
{
	if (button.is_hover)
		draw_image_strech(app->frame_buffer.buffer, button.pos, button.size,
			button.hover_image);
	else
		draw_image_strech(app->frame_buffer.buffer, button.pos, button.size,
			button.default_image);
}

bool	tex_button_update(t_app *app, t_tex_button button)
{
	bool	clicked;

	if (button.hide)
		return (false);
	button.is_hover = mouse_perfect_collision(app, button.pos, button.size,
			button.default_image);
	tex_button_draw(app, button);
	clicked = button.is_hover && app->input_handler.registered_click
		&& !app->input_handler.mouse_is_busy;
	if (clicked)
		app->input_handler.registered_click = false;
	return (clicked);
}
