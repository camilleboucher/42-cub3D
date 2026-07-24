/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboucher <private_mail>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 15:51:04 by cboucher          #+#    #+#             */
/*   Updated: 2026/07/24 14:25:34 by cboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_map
{
	char	cell[65536];
	uint8_t	width;
	uint8_t	height;
}	t_map;

typedef struct s_game
{
	t_map	*map;
}	t_game;

#endif
