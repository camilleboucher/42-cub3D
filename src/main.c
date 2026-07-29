/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboucher <private_mail>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 15:22:43 by cboucher          #+#    #+#             */
/*   Updated: 2026/07/25 16:52:47 by aiga             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	start(char *map_path);
static void	check_file_extension(char *path, char *ext, int ext_size);
static int	open_map(char *path);
static void	init_map(t_map *map);

int	main(int argc, char *argv[])
{
	if (argc != 2)
		error_exit(ERR_NO_ARG);
	start(argv[1]);
	return (EXIT_SUCCESS);
}

static void	start(char *map_path)
{
	t_map	map;
	int		fd;

	check_file_extension(map_path, ".cub", 4);
	fd = open_map(map_path);
	init_map(&map);
	parsing(&map, fd);
}

static void	check_file_extension(char *path, char *ext, int ext_size)
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

static int	open_map(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1 || read(fd, NULL, 0) == -1)
		error_exit(ERR_SYS);
	return (fd);
}

static void	init_map(t_map *map)
{
	ft_memset(map->path_textures, 0, sizeof(map->path_textures));
	ft_memset(map->floor_rgb, 0, sizeof(map->floor_rgb));
	ft_memset(map->ceiling_rgb, 0, sizeof(map->ceiling_rgb));
}
