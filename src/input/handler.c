/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboucher <private_mail>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 14:18:13 by cboucher          #+#    #+#             */
/*   Updated: 2026/11/11 18:32:29 by cboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	input_handler_set_down(t_input_handler *handler, int key)
{
	if (key >= 255 || key < 0)
		return ;
	handler->keys[key] = true;
}

void	input_handler_set_up(t_input_handler *handler, int key)
{
	if (key >= 255 || key < 0)
		return ;
	handler->keys[key] = false;
}

void	input_handler_update(t_input_handler *handler,
		double delta_time)
{
	update_keyboard(handler, &handler->devices[0], delta_time);
}

void	init_devices(t_input_handler *handler)
{
	handler->devices[0].active = true;
	handler->devices[0].controller_slot = -1;
	handler->devices[0].type = device_keyboard;
	handler->devices[0].move_vector = (t_vec2f){0, 0};
	handler->devices[0].angle = 0;
}
