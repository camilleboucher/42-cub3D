#include "app.h"
#include "menus.h"

#include "cub3D.h"

static void load_map(t_app *app, char *map_path);
static void check_file_extension(char *path, char *ext, int ext_size);
static int open_map(char *path);
static void init_game(t_player *player, t_map *map);

int main(int argc, char *argv[])
{
	struct s_app app;

	if (argc != 2)
		error_exit(ERR_NO_ARG);

	app = (struct s_app){0};

	app_init(&app);
	load_map(&app, argv[1]);
	if (!atlas_load_buttons(&app))
	{
		app_destroy(&app);
		return (1);
	}
	main_loop(&app);
	free_all_images(&app);
	app_destroy(&app);
}

void print_map_player(t_map *map, t_player *player)
{
	int x;
	int y;

	x = 0;
	y = 0;
	printf("MAP:\n====\n");
	printf("NO:	%s\n", map->path_textures[0]);
	printf("SO:	%s\n", map->path_textures[1]);
	printf("WE:	%s\n", map->path_textures[2]);
	printf("EA:	%s\n\n", map->path_textures[3]);
	while (y != map->height)
	{
		write(1, map->cell + x + y * MAP_SIZE_MAX_VALS, 1);
		x++;
		if (x > map->width)
		{
			x = 0;
			y++;
			write(1, "\n", 1);
		}
	}
	printf("\n\nPLAYER:\n=======\n");
	printf("X: %d\n", player->pos.x);
	printf("Y: %d\n", player->pos.y);
	printf("Angle: %f\n", player->angle);
}

static void load_map(t_app *app, char *map_path)
{
	int fd;

	check_file_extension(map_path, ".cub", 4);
	fd = open_map(map_path);
	init_game(&app->player, &app->map);
	parsing(fd, app);
	print_map_player(&app->map, &app->player); // WARN: TMP
	// TODO: FAIRE UN MOD CLEANER
	free(app->map.path_textures[0]);
	free(app->map.path_textures[1]);
	free(app->map.path_textures[2]);
	free(app->map.path_textures[3]);
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

static void init_game(t_player *player, t_map *map)
{
	player->pos = (t_position){0};
	ft_memset(map->cell, C_VOID, sizeof(map->cell));
	map->height = 0;
	ft_memset(map->path_textures, 0, sizeof(map->path_textures));
	ft_memset(map->floor_rgb, 0, sizeof(map->floor_rgb));
	ft_memset(map->ceiling_rgb, 0, sizeof(map->ceiling_rgb));
}
