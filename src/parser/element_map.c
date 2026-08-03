/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiga </var/spool/mail/aiga>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 18:08:50 by aiga              #+#    #+#             */
/*   Updated: 2026/07/29 19:33:43 by aiga             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static t_error	save_first_line(char *s, char *cell, TYPE_MAP_SIZE *width);

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
	if (map->height == 0)
		error = save_first_line(s, map->cell, &map->width);
	else
		error = save_line();//TODO: save_line and parametres 
	map->height++;
	return (error);
}

static t_error	save_first_line(char *s, char *cell, TYPE_MAP_SIZE *width)
{
	t_error error;
	int	i;

	error = ERR_NONE;
	i = 0;
	while (s[i] || s[i] != '\n') //WARN: s[i] utile ? pour protection si fin de fichier ?
	{
		if (s[i] == C_FLOOR)
			error = ERR_OPEN_MAP;
		else if (!(s[i] == C_VOID || s[i] == C_WALL))
			return (ERR_INVALID_C);
		cell[i] = s[i];
		i++;
	}
	i--;
	*width = i;
	return (error);
}
