/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboucher <private_mail>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 14:21:55 by cboucher          #+#    #+#             */
/*   Updated: 2026/07/25 19:23:36 by aiga             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//TODO: faire un fichier pour gerer les fonctions infos
static bool			get_info(t_map *map, char *s, t_error *error);
static t_direction	get_info_direction(char *s, int size);
static char			*skip_spaces(char *s);
static bool			set_info_direction(t_map *map, t_direction direction,
						char *s, t_error *error);
static t_error		set_info_color(uint8_t *color, t_direction direction,
						char *s, t_error eflag);
static bool			is_rgb8(char *s);
static bool			check_complete_infos(char **path_textures, t_error *error);

void	parsing(t_map *map, int fd)
{
	char	*s;
	t_error	error;
	bool	step_infos;

	error = ERR_NO_RGB_FLOOR | ERR_NO_RGB_CEILING;
	step_infos = true;
	while (1)
	{
		s = get_next_line(fd, false);//WARN: ya un monde ou mon gnl leak + TESTER avec CTRL+D injection fin de fichier
		if (!s)
			break;
		if (step_infos)
		{
			if (s[0] != '\n')
				step_infos = get_info(map, s, &error);
		}
		//else
		//TODO: get_map line and verifications
		free(s);
	}
	close(fd);
	if (error)
		error_exit(error);//TODO: implementer clean_exit et clean_error_exit pour free les textures path par exemple
}

static bool	get_info(t_map *map, char *s, t_error *error)
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

static char	*skip_spaces(char *s)
{
	while (ft_isspace((int)*s))
		s++;
	return (s);
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

static bool	is_rgb8(char *s)
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

static bool	check_complete_infos(char **path_textures, t_error *error)
{
	return ((*error & MASK_ERR_NO_RGBS) == 0
		 && path_textures[NORTH] && path_textures[SOUTH]
		 && path_textures[WEST] && path_textures[EAST]);
}
