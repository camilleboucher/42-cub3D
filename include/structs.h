/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 13:56:49 by cboucher          #+#    #+#             */
/*   Updated: 2026/08/31 14:32:17 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

#include "constants.h"
#include <stdint.h>

typedef enum e_direction
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
	FLOOR,
	CEILING,
	NO_DIRECTION
}	t_direction;

typedef enum e_rgb
{
	R,
	G,
	B
}	t_rgb;

typedef struct s_map
{
	char			cell[MAP_SIZE_MAX_VALS * MAP_SIZE_MAX_VALS];
	TYPE_MAP_SIZE	width;
	TYPE_MAP_SIZE	height;
	char			*path_textures[4];
	uint8_t			floor_rgb[3];
	uint8_t			ceiling_rgb[3];
}	t_map;

#endif
