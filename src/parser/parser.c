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

static int	strlen_map_line(char *s);

void	parsing(int fd, t_game *game)
{
	char	*s;
	t_error	error;
	t_step	step;
	t_list	*map_lines;

	error = ERR_NO_RGB_FLOOR | ERR_NO_RGB_CEILING;
	step = GET_INFOS;
	map_lines = ft_lstnew(NULL);
	while (1)
	{
		s = get_next_line(fd, false);//WARN: ya un monde où mon gnl leak + TESTER avec CTRL+D injection fin de fichier
		if (!s)
			break;
		if (step == GET_INFOS)
		{
			if (s[0] != '\n')
				step = !get_info(&game->map, s, &error);
			free(s);
		}
		else if (!(error & MASK_ERR_CRITICAL_BUGS)) //TODO: Avoir un gnl protege si errsys pour free la stash
			error |= backup_map_line(&game->map, map_lines, s);
	}
	close(fd);
	parsing_map(game, map_lines, error, step);
}

t_error	backup_map_line(t_map *map, t_list *map_lines, char *s)
{
	t_list	*node;
	int		size;

	if (!map_lines)
		return (ERR_SYS);
	size = strlen_map_line(s);
	if (map->width < size)
		map->width = size;
	map->height++;
	if (!map_lines->content)
		map_lines->content = s;
	else
	{
		node = ft_lstnew(s);
		if (!node)
			return (ERR_SYS);
		ft_lstadd_back(&map_lines, node);
	}
	return (ERR_NONE);
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

static int	strlen_map_line(char *s)
{
	int	i;

	i = 0;
	while (s[i] || s[i] == '\n')
		i++;
	return (i);
}
