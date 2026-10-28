/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboucher <private_mail>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 15:25:55 by cboucher          #+#    #+#             */
/*   Updated: 2026/10/28 18:26:41 by cboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	load_map(t_app *app, char *map_path);
static void	check_file_extension(char *path, char *ext, int ext_size);
static int	open_map(char *path);

int main(int argc, char *argv[])
{
	struct s_app app;

	if (argc != 2)
		error_exit(ERR_NO_ARG);
	app = (struct s_app){0};
	load_map(&app, argv[1]);
	window_init(&app);
	if (!atlas_load_buttons(&app)
		|| !create_objects(&app))
	{
		app_destroy(&app);
		return (1);
	}
	main_loop(&app);
	free_all_images(&app);
	app_destroy(&app);
}

static void load_map(t_app *app, char *map_path)
{
	int fd;

	check_file_extension(map_path, ".cub", 4);
	fd = open_map(map_path);
	init_parser(&app->player, &app->map);
	parsing(fd, app, GET_INFOS);
	app->map.ceil_color = (mlx_color){ .r=app->map.ceiling_rgb[0], .g=app->map.ceiling_rgb[1], .b=app->map.ceiling_rgb[2], .a=0xFF };
	app->map.floor_color = (mlx_color){ .r=app->map.floor_rgb[0], .g=app->map.floor_rgb[1], .b=app->map.floor_rgb[2], .a=0xFF };
}

static void check_file_extension(char *path, char *ext, int ext_size)
{
	int i;

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

static int open_map(char *path)
{
	int fd;

	fd = open(path, O_RDONLY);
	if (fd == -1 || read(fd, NULL, 0) == -1)
		error_exit(ERR_SYS);
	return (fd);
}
