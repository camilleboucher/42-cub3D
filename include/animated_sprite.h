/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animated_sprite.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboucher <private_mail>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 13:56:54 by cboucher          #+#    #+#             */
/*   Updated: 2026/10/07 14:05:55 by cboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMATED_SPRITE_H
# define ANIMATED_SPRITE_H

# include "cub3D.h"

t_animated_sprite animated_sprite_from_region(t_region *frames, unsigned int frame_count, double frame_time, bool playing);

mlx_color *animated_sprite_get_buffer_start(t_animated_sprite *sprite, unsigned int *frame_width);

void animated_sprite_draw(t_frame_buffer *buffer, t_animated_sprite *sprite, t_vec2i out_pos);

void animated_sprite_update(t_animated_sprite *sprite, double delta_time);

#endif
