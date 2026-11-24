/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   device_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 16:35:04 by yben-dje          #+#    #+#             */
/*   Updated: 2026/11/20 16:35:04 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

bool	is_key_down(t_input_handler *handler, int key)
{
	return (handler->keys[key]);
}

t_vec2f	dead_zone(t_vec2f a)
{
	if (a.x > 0. && a.x < 0.05)
		a.x = 0.;
	if (a.y > 0. && a.y < 0.05)
		a.y = 0.;
	if (a.x < 0. && a.x > -0.05)
		a.x = 0.;
	if (a.y < 0. && a.y > -0.05)
		a.y = 0.;
	return (a);
}

double	dead_one_axis(double a)
{
	if (a > 0. && a < 0.05)
		a = 0.;
	if (a < 0. && a > -0.05)
		a = 0.;
	return (a);
}

t_vec2f	get_controler_left_vector(t_input_handler *handler,
		unsigned int controller_index)
{
	return (dead_zone(handler->devices[controller_index].move_vector));
}

double	get_controler_angle(t_input_handler *handler,
		unsigned int controller_index)
{
	return (handler->devices[controller_index].angle);
}
