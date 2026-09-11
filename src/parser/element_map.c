/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 18:08:50 by cboucher          #+#    #+#             */
/*   Updated: 2026/08/27 17:59:44 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "cube3D2.h"

static t_error	save_first_line(char *s, char *cell, TYPE_MAP_SIZE *width);
static t_error	save_line(char *s, char *cell, t_app *app, t_map *map);
static bool		is_char_valid_place(char *s, int x, int y, char *cell);
static bool		save_player(char *s, int *i, t_app *app, t_error *error);

t_error	get_map_line(t_app *app, t_map *map, char *s, t_step *step)
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
		error = save_line(s, map->cell, app, map);
	map->height++;
	return (error);
}

static t_error	save_first_line(char *s, char *cell, TYPE_MAP_SIZE *width)
{
	t_error	error;
	int		i;

	error = ERR_NONE;
	i = 0;
	while (s[i] && s[i] != '\n') //WARN: s[i] utile ? pour protection si fin de fichier ?
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
	i--;
	*width = i;
	return (error);
}

static t_error	save_line(char *s, char *cell, t_app *app, t_map *map)
{
	t_error	error;
	int		i;
	int		y;

	error = ERR_NONE;
	i = 0;
	y = map->height * MAP_SIZE_MAX_VALS;
	while (s[i] && s[i] != '\n')
	{
		if (i > MAP_SIZE_MAX_VALS)
			return (error | ERR_MAP_OVERFLOW);
		else if (!is_char_valid_place(s, i, y, cell))
			error |= ERR_OPEN_MAP;
		else if (save_player(s, &i, app, &error))
			continue ;
		else if (!(s[i] == C_VOID || s[i] == C_FLOOR || s[i] == C_WALL
			|| s[i] == 'N' || s[i] == 'S' || s[i] == 'E' || s[i] == 'W'))
			error |= ERR_INVALID_C;
		cell[i + y] = s[i];
		i++;
	}
	i--;
	if (i > map->width)
		map->width = i;
	return (error);
}

static bool		is_char_valid_place(char *s, int x, int y, char *cell)
{
	if (s[x] == C_VOID)
	{
		if (cell[x + y - MAP_SIZE_MAX_VALS] == C_FLOOR)
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
			|| cell[x + y - MAP_SIZE_MAX_VALS] == C_VOID)
			return (false);
	}
	return (true);
}

static bool		save_player(char *s, int *i, t_app *app, t_error *error)
{
	char	dir;

	dir = s[*i];
	if (!(dir == 'N' || dir == 'S' || dir == 'E' || dir == 'W'))
		return (false);
	if (app->players[0].pos.x || app->players[0].pos.y)
		*error |= ERR_DUPLICATE_PLAYER;
	else if (dir == 'E')
		app->players[0].angle = 0;
	else if (dir == 'N')
		app->players[0].angle = M_PI_2;
	else if (dir == 'W')
		app->players[0].angle = M_PI;
	else if (dir == 'S')
		app->players[0].angle = -M_PI_2;
	app->map.cell[*i + app->map.height * MAP_SIZE_MAX_VALS] = C_FLOOR;
	app->players[0].pos = (t_vec2f){*i, app->map.height};
	app->players[1].pos = (t_vec2f){*i, app->map.height};
	app->players[2].pos = (t_vec2f){*i, app->map.height};
	app->players[3].pos = (t_vec2f){*i, app->map.height};
	(*i)++;
	return (true);
}
