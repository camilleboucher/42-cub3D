#include "cub3D.h"

char map_get(t_map *map, unsigned int x, unsigned int y)
{
    return (map->cell[x + y * MAP_SIZE_MAX_VALS]);
}
