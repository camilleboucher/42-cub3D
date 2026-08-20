/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboucher <private_mail>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 14:21:55 by cboucher          #+#    #+#             */
/*   Updated: 2026/08/04 18:56:20 by aiga             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static t_error	get_map_line(t_game *game, t_map *map, char *s, t_step *step);
static t_error	last_line_verification(char *cell, int map_height);
static void		parser_cleaner(uint64_t eflag, t_map *map, t_list *map_lines);


void	parsing_map(t_game *game, t_list *map_head, t_error error, t_step step)
{
	t_list	*map_line;

	map_line = map_head;
	game->map.cell = malloc(sizeof(char) * (game->map.height * game->map.width));
	if (!game->map.cell)
		error |= ERR_SYS;
	else
	{
		ft_memset(game->map.cell, C_VOID, sizeof(game->map.cell));
		game->map.height = 0;
		while (map_line && !(error & MASK_ERR_CRITICAL_BUGS))
		{
			error |= get_map_line(game, &game->map, map_line->content, &step);
			map_line = map_line->next;
		}
		if (!(error & MASK_ERR_CRITICAL_BUGS))
			error |= last_line_verification(game->map.cell, game->map.height);
	}
	parser_cleaner(error, &game->map, map_head);
}

static t_error	get_map_line(t_game *game, t_map *map, char *s, t_step *step)
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
		error = save_first_line(s, map->cell);
	else
		error = save_line(s, map->cell, game, map);
	map->height++;
	return (error);
}

static t_error	last_line_verification(char *cell, int map_height)
{
	int	i;
	int	y;

	i = 0;
	y = map_height * MAP_SIZE_MAX_VALS;
	while (i < MAP_SIZE_MAX_VALS)
	{
		if (cell[i + y] == C_FLOOR)
			return (ERR_OPEN_MAP);
		i++;
	}
	return (ERR_NONE);
}

static void	parser_cleaner(uint64_t eflag, t_map *map, t_list *map_lines)
{
	//TODO:clean map-list
	if (eflag)
	{
		clean_map(map);
		error_exit(eflag);
	}
}
