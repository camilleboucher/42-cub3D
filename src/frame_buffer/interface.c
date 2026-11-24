/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboucher <private_mail>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 14:15:22 by cboucher          #+#    #+#             */
/*   Updated: 2026/10/07 14:29:19 by cboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	set_pixel(t_region *frame_buffer, unsigned int x, unsigned int y,
		mlx_color color)
{
	frame_buffer->buffer[y + x * frame_buffer->height] = color;
}

mlx_color	get_pixel(t_region *frame_buffer, unsigned int x, unsigned int y)
{
	return (frame_buffer->buffer[y + x * frame_buffer->height]);
}

void	set_pixel_opt(t_region *frame_buffer, unsigned int i, mlx_color color)
{
	frame_buffer->buffer[i] = color;
}

mlx_color	get_pixel_opt(t_region *frame_buffer, unsigned int i)
{
	return (frame_buffer->buffer[i]);
}
