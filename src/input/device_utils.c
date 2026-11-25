/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   device_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 16:35:04 by yben-dje          #+#    #+#             */
/*   Updated: 2026/11/20 16:35:04 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	is_key_down(t_input_handler *handler, int key)
{
	return (handler->keys[key]);
}

t_vec2f	get_controller_left_vector(t_input_handler *handler,
		unsigned int controller_index)
{
	return (handler->devices[controller_index].move_vector);
}

double	get_controller_angle(t_input_handler *handler,
		unsigned int controller_index)
{
	return (handler->devices[controller_index].angle);
}
