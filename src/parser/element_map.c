/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboucher <private_mail>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 18:08:50 by cboucher          #+#    #+#             */
/*   Updated: 2026/08/03 14:14:15 by cboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static t_error	save_first_line(char *s, char *cell, TYPE_MAP_SIZE *width);
static t_error	save_line(char *s, char *cell, t_map *map);
static bool		valid_floor_place(char *s, int x, int y);

t_error	get_map_line(t_map *map, char *s, t_step *step)
{
	t_error	error;

	if (*step == SKIP_NEW_LINES)
	{
		if (*s == '\n')
			return (ERR_NONE);
		*step = GET_MAP;
	}
	else if (*s == '\n')
		return (ERR_EMPTY_LINE);
	if (map->height == MAP_SIZE_MAX_VALS)
		return (ERR_MAP_OVERFLOW);
	else if (map->height == 0)
		error = save_first_line(s, map->cell, &map->width);
	else
		error = save_line(s, map->cell, map);
	map->height++;
	return (error);
}

static t_error	save_first_line(char *s, char *cell, TYPE_MAP_SIZE *width)
{
	t_error	error;
	int		i;

	error = ERR_NONE;
	i = 0;
	while (s[i] || s[i] != '\n') //WARN: s[i] utile ? pour protection si fin de fichier ?
	{
		if (i == MAP_SIZE_MAX_VALS)
			return (error |= ERR_MAP_OVERFLOW);
		else if (s[i] == C_FLOOR)
			error |= ERR_OPEN_MAP;
		else if (!(s[i] == C_VOID || s[i] == C_WALL))
			error |= ERR_INVALID_C;
		cell[i] = s[i];
		i++;
	}
	i--;
	*width = i;
	return (error);
}

static t_error	save_line(char *s, char *cell, t_map *map)
{
	t_error	error;
	int		i;
	int		y;

	error = ERR_NONE;
	i = 0;
	y = map->height * MAP_SIZE_MAX_VALS;
	while (s[i] || s[i] != '\n')
	{
		if (i > MAP_SIZE_MAX_VALS)
			return (error |= ERR_MAP_OVERFLOW);
		else if (s[i] == C_FLOOR)
		{
			if (!valid_floor_place(s, i, y))
				error |= ERR_OPEN_MAP;
		}
		else if (!(s[i] == C_VOID || s[i] == C_WALL))
			error |= ERR_INVALID_C;
		cell[i + y] = s[i];
		i++;
	}
	i--;
	if (i > map->width)
		map->width = i;
	return (error);
}

static bool	valid_floor_place(char *s, int x, int y)
{
	if (x == 0)
		return (false);
	else if (!s[x + 1] && s[x + 1] == '\n')
		return (false);
	else if (s[x - 1] == C_VOID || s[x + 1] == C_VOID
		|| s[x - 1 - y] == C_VOID
		|| s[x - y] == C_VOID
		|| s[x + 1 - y] == C_VOID)
		return (false);
	return (true);
}
