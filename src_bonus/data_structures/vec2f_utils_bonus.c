/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2f_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboucher <private_mail>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 14:43:36 by cboucher          #+#    #+#             */
/*   Updated: 2026/10/07 14:43:39 by cboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

t_vec2f	vec2f_normalize(t_vec2f a)
{
	t_vec2f	new;
	double	lenght;

	lenght = vec2f_length(a);
	if (lenght == 0.)
		return (a);
	new.x = a.x / lenght;
	new.y = a.y / lenght;
	return (new);
}

double	vec2f_length(t_vec2f a)
{
	double	lenght;

	lenght = sqrtf(a.x * a.x + a.y * a.y);
	return (lenght);
}

double	vec2f_dist(t_vec2f a, t_vec2f b)
{
	double	dist;
	double	x_dist;
	double	y_dist;

	x_dist = b.x - a.x;
	y_dist = b.y - a.y;
	dist = sqrtf(x_dist * x_dist + y_dist * y_dist);
	return (dist);
}
