/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2i.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboucher <private_mail>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 14:43:27 by cboucher          #+#    #+#             */
/*   Updated: 2026/10/07 14:43:32 by cboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_vec2i vec2i_add(t_vec2i a, t_vec2i b) {
    t_vec2i new;
    new.x = a.x + b.x;
    new.y = a.y + b.y;
    return (new);
}

t_vec2i vec2i_comp_mul(t_vec2i a, t_vec2i b) {
    t_vec2i new;
    new.x = a.x * b.x;
    new.y = a.y * b.y;
    return (new);
}

t_vec2i vec2i_mul(t_vec2i a, int b) {
    t_vec2i new;
    new.x = a.x + b;
    new.y = a.y + b;
    return (new);
}

t_vec2i vec2i_div(t_vec2i a, int b) {
    t_vec2i new;
    new.x = a.x / b;
    new.y = a.y / b;
    return (new);
}
