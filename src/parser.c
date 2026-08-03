/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboucher <private_mail>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 14:21:55 by cboucher          #+#    #+#             */
/*   Updated: 2026/07/29 19:22:15 by aiga             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	parsing(t_map *map, int fd)
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
				step = !get_info(map, s, &error);
		}
		else if (!(error & ERR_INVALID_C))
			error |= get_map_line(map, s, &step);
		free(s);
	}
	close(fd);
	if (error) //TODO: remplacer par bool last verif (surtout pour derniere ligne) truc dans le genre  AND enregistrer map height grace a line_n - 1 ?
		error_exit(error);//TODO: implementer clean_exit et clean_error_exit pour free les textures path par exemple
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
