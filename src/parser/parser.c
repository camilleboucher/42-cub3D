/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 14:21:55 by cboucher          #+#    #+#             */
/*   Updated: 2026/08/24 18:29:44 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "cube3D2.h"

static t_error	last_line_verification(char *cell, int map_height);
static void		parser_clean_error_exit(uint64_t eflag, t_map *map);

void	parsing(int fd, t_app *app)
{
	char	*s;
	t_error	error;
	t_step	step;

	error = ERR_NO_RGB_FLOOR | ERR_NO_RGB_CEILING;
	step = GET_INFOS;
	while (1)
	{
		s = get_next_line(fd, false);//WARN: ya un monde où mon gnl leak + TESTER avec CTRL+D injection fin de fichier
		if (!s)
			break;
		if (step == GET_INFOS)
		{
			if (s[0] != '\n')
				step = !get_info(&app->map, s, &error);
		}
		else if (!(error & MASK_ERR_CRITICAL_BUGS)) //TODO: Avoir un gnl protege si errsys pour free la stash
			error |= get_map_line(app, &app->map, s, &step);
		free(s);
	}
	close(fd);
	if (!(error & MASK_ERR_CRITICAL_BUGS))
		error |= last_line_verification(app->map.cell, app->map.height);
	if (error)
		parser_clean_error_exit(error, &app->map);
}

char	*skip_spaces(char *s)
{
	while (ft_isspace((int)*s))
		s++;
	return (s);
}

bool	is_rgb8(char *s)
{
	int	size;

	size = ft_strlen(s);
	if (size > 3)
		return (false);
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (false);
		s++;
	}
	return (true);
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

static void	parser_clean_error_exit(uint64_t eflag, t_map *map)
{
	free(map->path_textures[0]);
	free(map->path_textures[1]);
	free(map->path_textures[2]);
	free(map->path_textures[3]);
	error_exit(eflag);
}
