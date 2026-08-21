/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboucher <private_mail>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 18:08:50 by cboucher          #+#    #+#             */
/*   Updated: 2026/08/21 19:21:26 by aiga             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static t_error	verifs_openmap(char *cell, int x, int y, int map_width);
static bool		is_char_valid_place(t_map *map, char *s, int x, int y);
static bool		save_player(char *s, int *i, t_game *game, t_error *error);

t_error	save_first_line(char *s, char *cell)
{
	t_error	error;
	int		i;

	error = ERR_NONE;
	i = 0;
	while (s[i] && s[i] != '\n')
	{
		if (i == MAP_SIZE_MAX_VALS)
			return (error | ERR_MAP_OVERFLOW);
		else if (s[i] == C_FLOOR)
			error |= ERR_OPEN_MAP;
		else if (!(s[i] == C_VOID || s[i] == C_WALL))
			error |= ERR_INVALID_C;
		cell[i] = s[i];
		i++;
	}
	return (error);
}

t_error	save_line(char *s, char *cell, t_game *game, t_map *map)
{
	t_error	error;
	int		i;
	int		y;

	error = ERR_NONE;
	i = 0;
	y = map->height * map->width;
	while (s[i] && s[i] != '\n')
	{
		if (i > MAP_SIZE_MAX_VALS)
			return (error | ERR_MAP_OVERFLOW);
		else if (!is_char_valid_place(map, s, i, y))
			error |= ERR_OPEN_MAP;
		else if (save_player(s, &i, game, &error))
			continue ;
		else if (!(s[i] == C_VOID || s[i] == C_FLOOR || s[i] == C_WALL
			|| s[i] == 'N' || s[i] == 'S' || s[i] == 'E' || s[i] == 'W'))
			error |= ERR_INVALID_C;
		cell[i + y] = s[i];
		i++;
	}
	error |= verifs_openmap(map->cell, i, y, map->width);
	return (error);
}

static t_error	verifs_openmap(char *cell, int x, int y, int map_width)
{
	while (x < map_width)
	{
		if (cell[x + y] == C_VOID)
		{
			if (cell[x + y - map_width] == C_FLOOR)
				return (ERR_OPEN_MAP);
		}
		x++;
	}
	return (ERR_NONE);
}

static bool		is_char_valid_place(t_map *map, char *s, int x, int y)
{
	if (s[x] == C_VOID)
	{
		if (map->cell[x + y - map->width] == C_FLOOR)
			return (false);
	}
	else if (s[x] == C_FLOOR)
	{
		if (x == 0)
			return (false);
		else if (!s[x + 1] || s[x + 1] == '\n')
			return (false);
		else if (s[x - 1] == C_VOID
			|| s[x + 1] == C_VOID
			|| map->cell[x + y - map->width] == C_VOID)
			return (false);
	}
	return (true);
}

static bool		save_player(char *s, int *i, t_game *game, t_error *error)
{
	char	dir;

	dir = s[*i];
	if (!(dir == 'N' || dir == 'S' || dir == 'E' || dir == 'W'))
		return (false);
	if (game->player.pos.x || game->player.pos.y)
		*error |= ERR_DUPLICATE_PLAYER;
	else if (dir == 'E')
		game->player.angle = 0;
	else if (dir == 'N')
		game->player.angle = M_PI_2;
	else if (dir == 'W')
		game->player.angle = M_PI;
	else if (dir == 'S')
		game->player.angle = -M_PI_2;
	game->map.cell[*i + game->map.height * game->map.width] = C_FLOOR;
	game->player.pos = (t_vec2i){*i, game->map.height};
	(*i)++;
	return (true);
}
