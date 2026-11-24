/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_structures_bonus.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboucher <private_mail>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 14:11:55 by cboucher          #+#    #+#             */
/*   Updated: 2026/10/07 14:11:55 by cboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_STRUCTURES_BONUS_H
# define DATA_STRUCTURES_BONUS_H

typedef struct s_vec2i
{
	int		x;
	int		y;
}			t_vec2i;

typedef struct s_vec2f
{
	double	x;
	double	y;
}			t_vec2f;

// vec2f_math.c
t_vec2f	vec2f_add(t_vec2f a, t_vec2f b);
t_vec2f	vec2f_comp_mul(t_vec2f a, t_vec2f b);
t_vec2f	vec2f_mul(t_vec2f a, double b);
t_vec2f	vec2f_div(t_vec2f a, double b);
// vec2f_utils.c
double	vec2f_length(t_vec2f a);
double	vec2f_dist(t_vec2f a, t_vec2f b);
t_vec2f	vec2f_sub(t_vec2f a, t_vec2f b);
t_vec2f	vec2f_normalize(t_vec2f a);

#endif
