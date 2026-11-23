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

void	init_draw(t_draw *d, t_vec2i *out_pos,
	t_frame_buffer *buffer, t_animated_sprite *sprite)
{
	d->pos = (t_vec2i){0, 0};
	if (out_pos->x < 0)
		out_pos->x = 0;
	if (out_pos->y < 0)
		out_pos->y = 0;
	d->stop = (t_vec2i){sprite->frame_width, sprite->frames->height};
	if (d->pos.x + out_pos->x > (int)buffer->width
		|| d->pos.y + out_pos->y > (int)buffer->height)
		return ;
	if (out_pos->x + d->stop.x > (int)buffer->width)
		d->stop.x = buffer->width;
	if (out_pos->y + d->stop.y > (int)buffer->height)
		d->stop.y = buffer->height;
	d->screen_i = buffer->height * out_pos->x;
	d->frame_i = sprite->frame_index * sprite->frame_width
		* sprite->frames->height;
}

void	animated_sprite_draw(t_frame_buffer *buffer, t_animated_sprite *sprite,
		t_vec2i out_pos)
{
	t_draw	d;

	init_draw(&d, &out_pos, buffer, sprite);
	while (d.pos.x < d.stop.x)
	{
		d.pos.y = 0;
		while (d.pos.y < d.stop.y)
		{
			d.color = get_pixel_opt(sprite->frames, d.frame_i + d.pos.y);
			set_pixel_opt(buffer->buffer,
				out_pos.y + d.pos.y + d.screen_i, d.color);
			d.pos.y++;
		}
		d.pos.x++;
		d.frame_i += sprite->frames->height;
		d.screen_i += buffer->buffer->height;
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
