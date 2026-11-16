/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_buffer.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboucher <private_mail>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 14:09:48 by cboucher          #+#    #+#             */
/*   Updated: 2026/10/07 14:09:50 by cboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRAME_BUFFER_H
# define FRAME_BUFFER_H

# include "cub3D.h"

bool		reallocate_frame_buffer(t_app *app);
void		clear_frame_buffer(t_app *app, mlx_color color);

void		push_frame_buffer_to_screen(t_app *app);
void		push_buffer_to_screen_image(t_app *app,
				unsigned int sub_screen_index);

bool		resize_frame_buffer(t_app *app, unsigned int width,
				unsigned int height);

void		set_pixel(t_region *frame_buffer, unsigned int x, unsigned int y,
				mlx_color color);

void		set_pxl(t_region *frame_buf, unsigned int i,
				mlx_color color, bool is_door);

mlx_color	get_pixel(t_region *frame_buffer, unsigned int x, unsigned int y);

void		set_pixel_opt(t_region *frame_buffer, unsigned int i,
				mlx_color color);
mlx_color	get_pixel_opt(t_region *frame_buffer, unsigned int i);

#endif
