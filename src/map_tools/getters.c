/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 14:18:36 by cboucher          #+#    #+#             */
/*   Updated: 2026/10/26 19:47:24 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char map_get(t_map *map, int x, int y)
{
    if (x < 0 || y < 0 || x >= map->width || y >= map->height)
        return ('1');
    return (map->cell[x + y * map->width]);
}
