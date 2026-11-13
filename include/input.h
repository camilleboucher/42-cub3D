/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboucher <private_mail>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 17:56:40 by cboucher          #+#    #+#             */
/*   Updated: 2026/11/11 18:32:15 by cboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include "cub3D.h"

// device
void	device_notify(t_app *app, int device_id);
void	update_mouse_and_keyboard(t_input_handler *handler,
			t_input_device *device);
void	update_keyboard(t_input_handler *handler, t_input_device *device,
			double delta_time);

// handler
void	input_handler_set_down(t_input_handler *handler, int key);
void	input_handler_set_up(t_input_handler *handler, int key);
bool	is_key_down(t_input_handler *handler, int key);
t_vec2f	get_controler_left_vector(t_input_handler *handler,
			unsigned int controller_index);
double	get_controler_angle(t_input_handler *handler,
			unsigned int controller_index);
void	input_handler_update(t_input_handler *handler, mlx_context ctx,
			double delta_time);
void	init_devices(t_input_handler *handler);

#endif
