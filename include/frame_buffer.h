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
#define FRAME_BUFFER_H

bool reallocate_frame_buffer(t_app *app);
void clear_frame_buffer(t_app *app, mlx_color color);

void push_frame_buffer_to_screen(t_app *app);

bool resize_frame_buffer(t_app *app, unsigned int width, unsigned height);

void set_pixel(t_region *frame_buffer, unsigned int x, unsigned int y, mlx_color color);
mlx_color get_pixel(t_region *frame_buffer, unsigned int x, unsigned int y);

void set_pixel_opt(t_region *frame_buffer, unsigned int i, mlx_color color);
mlx_color get_pixel_opt(t_region *frame_buffer, unsigned int i);

#endif
