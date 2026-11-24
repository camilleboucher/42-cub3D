/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 16:51:02 by yben-dje          #+#    #+#             */
/*   Updated: 2026/11/23 17:10:28 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	is_solid(char cell)
{
	if (cell == ID_WALL)
		return (true);
	return (false);
}

bool	has_collision(t_map *map, t_vec2f test_pos)
{
	return (is_solid(map_get(map, test_pos.x - PLAYER_BOX, test_pos.y
				+ PLAYER_BOX)) || is_solid(map_get(map, test_pos.x - PLAYER_BOX,
				test_pos.y - PLAYER_BOX)) || is_solid(map_get(map, test_pos.x
				+ PLAYER_BOX, test_pos.y - PLAYER_BOX)) || is_solid(map_get(map,
				test_pos.x + PLAYER_BOX, test_pos.y + PLAYER_BOX)));
}
