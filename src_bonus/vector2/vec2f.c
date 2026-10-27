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

t_vec2f vec2f_add(t_vec2f a, t_vec2f b) {
    t_vec2f new;
    new.x = a.x + b.x;
    new.y = a.y + b.y;
    return (new);
}

t_vec2f vec2f_sub(t_vec2f a, t_vec2f b) {
    t_vec2f new;
    new.x = a.x - b.x;
    new.y = a.y - b.y;
    return (new);
}

t_vec2f vec2f_comp_mul(t_vec2f a, t_vec2f b) {
    t_vec2f new;
    new.x = a.x * b.x;
    new.y = a.y * b.y;
    return (new);
}

t_vec2f vec2f_mul(t_vec2f a, double b) {
    t_vec2f new;
    new.x = a.x * b;
    new.y = a.y * b;
    return (new);
}

t_vec2f vec2f_div(t_vec2f a, double b) {
    t_vec2f new;
    new.x = a.x / b;
    new.y = a.y / b;
    return (new);
}

t_vec2f vec2f_normalize(t_vec2f a) {
    t_vec2f new;
    double lenght;

    lenght = vec2f_lenght(a);
    if (lenght == 0.)
        return (a);
    new.x = a.x / lenght;
    new.y = a.y / lenght;
    return (new);
}

double vec2f_lenght(t_vec2f a) {
    double lenght;

    lenght = sqrtf(a.x * a.x + a.y * a.y);
    return (lenght);
}

double vec2f_dist(t_vec2f a, t_vec2f b) {
    double dist;
    double x_dist;
    double y_dist;

    x_dist = b.x - a.x;
    y_dist = b.y - a.y;
    dist = sqrtf(x_dist * x_dist + y_dist * y_dist);
    return (dist);
}
