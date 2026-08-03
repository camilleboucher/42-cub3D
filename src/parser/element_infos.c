/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_infos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiga </var/spool/mail/aiga>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 17:54:47 by aiga              #+#    #+#             */
/*   Updated: 2026/07/29 19:06:53 by aiga             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static t_direction	get_info_direction(char *s, int size);
static bool			set_info_direction(t_map *map, t_direction direction,
						char *s, t_error *error);
static t_error		set_info_color(uint8_t *color, t_direction direction,
						char *s, t_error eflag);
static bool			check_complete_infos(char **path_textures, t_error *error);

bool	get_info(t_map *map, char *s, t_error *error)
{
	t_direction	direction;

	direction = get_info_direction(s, ft_strlen(s));
	if (direction == NO_DIRECTION)
		return (*error |= ERR_WRONG_INFO_START);
	else if (direction > EAST)
		s++;
	else
		s += 2;
	if (!ft_isspace((int)*s))
		return (*error |= ERR_MISSING_SPACE);
	s = skip_spaces(s + 1);
	if (!set_info_direction(map, direction, s, error))
		return (false);
	return (true);
}

static t_direction	get_info_direction(char *s, int size)
{
	if (size >= 2)
	{
		if (ft_strncmp(s, "NO", 2) == 0)
			return (NORTH);
		else if (ft_strncmp(s, "SO", 2) == 0)
			return (SOUTH);
		else if (ft_strncmp(s, "WE", 2) == 0)
			return (WEST);
		else if (ft_strncmp(s, "EA", 2) == 0)
			return (EAST);
	}
	if (size >= 1)
	{
		if (ft_strncmp(s, "F", 1) == 0)
			return (FLOOR);
		else if (ft_strncmp(s, "C", 1) == 0)
			return (CEILING);
	}
	return (NO_DIRECTION);
}

static bool	set_info_direction(t_map *map, t_direction direction,
					char *s, t_error *error)
{
	char	*path_texture_dir;

	if (direction <= EAST)
	{
		path_texture_dir = map->path_textures[direction];
		if (path_texture_dir)
			return (*error |= ERR_DUPLICATE_INFO);
		path_texture_dir = ft_strdup(s);
		if (!path_texture_dir)
			return (*error |= ERR_SYS);
		path_texture_dir[ft_strlen(path_texture_dir) - 1] = '\0';
	}
	else if (direction == FLOOR)
		*error |= set_info_color(map->floor_rgb, direction, s, *error)
			& ~ERR_NO_RGB_FLOOR;
	else
		*error |= set_info_color(map->ceiling_rgb, direction, s, *error)
			& ~ERR_NO_RGB_CEILING;
	if (check_complete_infos(map->path_textures, error))
		return (false);
	return (*error);
}

static t_error		set_info_color(uint8_t *color, t_direction direction,
						char *s, t_error eflag)
{
	t_error	error;
	char	**rgb;
	int		i;

	if ((direction == FLOOR && (eflag & ERR_NO_RGB_FLOOR) == 0)
		| (direction == CEILING && (eflag & ERR_NO_RGB_CEILING) == 0))
		return (ERR_DUPLICATE_INFO);
	s[ft_strlen(s) - 1] = '\0';
	rgb = ft_split(s, ',');
	if (!rgb)
		return (ERR_SYS);
	i = 0;
	error = ERR_NONE;
	while (i <= B)
	{
		if (!is_rgb8(rgb[i]))
		{
			error = ERR_NOT_RGB8;
			break ;
		}
		color[i] = (uint8_t)ft_atoi(rgb[i]);
		i++;
	}
	ft_free_strs(rgb);
	return (error);
}

static bool	check_complete_infos(char **path_textures, t_error *error)
{
	return ((*error & MASK_ERR_NO_RGBS) == 0
		 && path_textures[NORTH] && path_textures[SOUTH]
		 && path_textures[WEST] && path_textures[EAST]);
}
