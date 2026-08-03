/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboucher <private_mail>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 15:22:43 by cboucher          #+#    #+#             */
/*   Updated: 2026/08/03 14:27:28 by cboucher         ###   ########.fr       */
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

void	print_map(t_map *map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	printf("MAP:\n====\n\nNO:	%s\n", map->path_textures[0]);
	printf("SO:	%s\n", map->path_textures[1]);
	printf("WE:	%s\n", map->path_textures[2]);
	printf("EA:	%s\n\n", map->path_textures[3]);
	while (y != map->height)
	{
		write(1, map->cell + x + y * MAP_SIZE_MAX_VALS, 1);
		x++;
		if (x == map->width)
		{
			x = 0;
			y++;
			write(1, "\n", 1);
		}
	}
}

static void	start(char *map_path)
{
	t_map	map;
	int		fd;

	check_file_extension(map_path, ".cub", 4);
	fd = open_map(map_path);
	init_map(&map);
	parsing(&map, fd);
	print_map(&map);//WARN: TMP
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
	ft_memset(map->cell, C_VOID, sizeof(map->cell));
	map->height = 0;
	ft_memset(map->path_textures, 0, sizeof(map->path_textures));
	ft_memset(map->floor_rgb, 0, sizeof(map->floor_rgb));
	ft_memset(map->ceiling_rgb, 0, sizeof(map->ceiling_rgb));
}
