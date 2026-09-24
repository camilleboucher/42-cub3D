/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboucher <private_mail>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 17:32:10 by cboucher          #+#    #+#             */
/*   Updated: 2026/09/24 17:34:28 by cboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "cube3D2.h"

static t_error	backup_map_line(t_map *map, t_list *map_lines,
					char *s, t_step *step);
static t_error	skip_new_lines(t_step *step, char **s);
static int		strlen_map_line(char *s);

void	parsing(int fd, t_app *app, t_step step)
{
	char	*s;
	t_error	error;
	t_list	*map_lines;

	error = ERR_NO_RGB_FLOOR | ERR_NO_RGB_CEILING;
	map_lines = ft_lstnew(NULL);
	while (1)
	{
		s = get_next_line(fd, false);
		if (!s)
			break ;
		if (step == GET_INFOS)
		{
			if (s[0] != '\n')
				step = !get_info(&app->map, s, &error);
			free(s);
		}
		else if (error & MASK_ERRS_CRITICALS)
			free(s);
		else
			error |= backup_map_line(&app->map, map_lines, s, &step);
	}
	close(fd);
	parsing_map(app, &app->map, map_lines, error);
}

static t_error	backup_map_line(t_map *map, t_list *map_lines,
	char *s, t_step *step)
{
	t_list	*node;
	int		size;
	t_error	error;

	error = skip_new_lines(step, &s);
	if (!s || error)
		return (error);
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

static t_error	skip_new_lines(t_step *step, char **s)
{
	if (*step == SKIP_NEW_LINES)
	{
		if (**s == '\n')
		{
			free(*s);
			*s = NULL;
			return (ERR_NONE);
		}
		*step = GET_MAP;
	}
	else if (**s == '\n')
	{
		free(*s);
		return (ERR_EMPTY_LINE);
	}
	return (ERR_NONE);
}

static int	strlen_map_line(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	return (i);
}
