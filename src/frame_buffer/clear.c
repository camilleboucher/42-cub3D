/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 16:45:00 by yben-dje          #+#    #+#             */
/*   Updated: 2026/11/23 16:45:00 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	clear_region(t_region *region, mlx_color color)
{
	unsigned int	i;

	i = 0;
	while (i < region->width * region->height)
		set_pixel_opt(region, i++, color);
}

void	clear_frame_buffer(t_app *app, mlx_color color)
{
	unsigned int	i;

	i = 0;
	while (i < app->frame_buffer.width * app->frame_buffer.height)
		app->frame_buffer.buffer->buffer[i++] = color;
}
