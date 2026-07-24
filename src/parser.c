/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboucher <private_mail>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 14:21:55 by cboucher          #+#    #+#             */
/*   Updated: 2026/07/24 16:04:30 by cboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	parsing(t_map *map, char *path)
{
	int	fd;

	check_extension(path, ".cub", 4);
	fd = open_map(path);
	(void)map;//INFO: c'est read qui fail si cest un dossier
}

void	check_extension(char *path, char *ext, int ext_size)
{
	int	i;

	i = 0;
	while (path[i])
		i++;
	if (i <= ext_size)
		error_exit(ERR_WRONG_PATH);
	while (ext_size >= 0)
	{
		if (path[i] == ext[ext_size])
		{
			i--;
			ext_size--;
		}
		else
			error_exit(ERR_WRONG_PATH);
	}
}

int	open_map(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		error_exit(ERR_SYS);
	return (fd);
}
