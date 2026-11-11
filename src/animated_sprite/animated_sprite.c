/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animated_sprite.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboucher <private_mail>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 17:59:01 by cboucher          #+#    #+#             */
/*   Updated: 2026/11/11 17:59:02 by cboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_animated_sprite	animated_sprite_from_region(t_region *frames,
		unsigned int frame_count, double frame_time, bool playing)
{
	t_animated_sprite	sprite;

	sprite.frames = frames;
	sprite.frame_count = frame_count;
	sprite.frame_time = frame_time;
	sprite.frame_index = 0;
	sprite.playing = playing;
	sprite.timer = 0.;
	sprite.frame_width = frames->width / frame_count;
	return (sprite);
}

mlx_color	*animated_sprite_get_buffer_start(t_animated_sprite *sprite,
		unsigned int *frame_width)
{
	*frame_width = sprite->frames->width / sprite->frame_count;
	return (sprite->frames->buffer + ((*frame_width * sprite->frames->height)
			* sprite->frame_index));
}

void	animated_sprite_draw(t_frame_buffer *buffer, t_animated_sprite *sprite,
		t_vec2i out_pos)
{
	t_vec2i			pos;
	t_vec2i			stop;
	unsigned int	screen_i;
	unsigned int	frame_i;
	mlx_color		color;

	pos = (t_vec2i){0, 0};
	if (out_pos.x < 0)
		out_pos.x = 0;
	if (out_pos.y < 0)
		out_pos.y = 0;
	stop = (t_vec2i){sprite->frame_width, sprite->frames->height};
	if (pos.x + out_pos.x > buffer->width || pos.y + out_pos.y > buffer->height)
		return ;
	if (out_pos.x + stop.x > buffer->width)
		stop.x = buffer->width;
	if (out_pos.y + stop.y > buffer->height)
		stop.y = buffer->height;
	screen_i = buffer->height * out_pos.x;
	frame_i = sprite->frame_index * sprite->frame_width
		* sprite->frames->height;
	while (pos.x < stop.x)
	{
		pos.y = 0;
		while (pos.y < stop.y)
		{
			color = get_pixel_opt(sprite->frames, frame_i + pos.y);
			set_pixel_opt(buffer->buffer, out_pos.y + pos.y + screen_i, color);
			pos.y++;
		}
		pos.x++;
		frame_i += sprite->frames->height;
		screen_i += buffer->buffer->height;
	}
}

void	animated_sprite_update(t_animated_sprite *sprite, double delta_time)
{
	sprite->timer += delta_time;
	if (sprite->timer >= sprite->frame_time)
	{
		sprite->timer = 0.;
		sprite->frame_index++;
		if (sprite->frame_index >= sprite->frame_count)
			sprite->frame_index = 0;
	}
}
