/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboucher <private_mail>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 15:51:04 by cboucher          #+#    #+#             */
/*   Updated: 2026/07/25 18:54:05 by aiga             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

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
	char			cell[MAP_SIZE_MAX_VALUES * MAP_SIZE_MAX_VALUES];
	TYPE_MAP_SIZE	width;
	TYPE_MAP_SIZE	height;
	char			*path_textures[4];
	uint8_t			floor_rgb[3];
	uint8_t			ceiling_rgb[3];
}	t_map;

typedef struct s_game
{
	t_map	*map;
}	t_game;

#endif
