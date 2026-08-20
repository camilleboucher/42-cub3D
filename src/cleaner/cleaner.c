#include "cub3D.h"

void	clean_game(t_game *game)
{
	clean_map(&game->map);
}

void	clean_map(t_map *map)
{
	free(map->cell);
	free(map->path_textures[0]);
	free(map->path_textures[1]);
	free(map->path_textures[2]);
	free(map->path_textures[3]);
}
