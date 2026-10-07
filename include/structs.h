/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboucher <private_mail>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 17:12:31 by cboucher          #+#    #+#             */
/*   Updated: 2026/09/24 18:11:24 by cboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

#include "vector.h"
#include "mlx.h"

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
	char		*cell;
	uint16_t	width;
	uint16_t	height;
	char		*path_textures[4];
	uint8_t		floor_rgb[3];
	uint8_t		ceiling_rgb[3];
	mlx_color	floor_color;
	mlx_color	ceil_color;
}	t_map;

#endif
