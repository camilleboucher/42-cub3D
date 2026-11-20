/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2f.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboucher <private_mail>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 14:43:36 by cboucher          #+#    #+#             */
/*   Updated: 2026/10/07 14:43:39 by cboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_vec2f	vec2f_add(t_vec2f a, t_vec2f b)
{
	t_vec2f	new;

	new.x = a.x + b.x;
	new.y = a.y + b.y;
	return (new);
}

t_vec2f	vec2f_sub(t_vec2f a, t_vec2f b)
{
	t_vec2f	new;

	new.x = a.x - b.x;
	new.y = a.y - b.y;
	return (new);
}

t_vec2f	vec2f_comp_mul(t_vec2f a, t_vec2f b)
{
	t_vec2f	new;

	new.x = a.x * b.x;
	new.y = a.y * b.y;
	return (new);
}

t_vec2f	vec2f_mul(t_vec2f a, double b)
{
	t_vec2f	new;

	new.x = a.x * b;
	new.y = a.y * b;
	return (new);
}

t_vec2f	vec2f_div(t_vec2f a, double b)
{
	t_vec2f	new;

	new.x = a.x / b;
	new.y = a.y / b;
	return (new);
}
