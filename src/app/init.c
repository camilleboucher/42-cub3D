/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboucher <private_mail>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 13:53:15 by cboucher          #+#    #+#             */
/*   Updated: 2026/10/07 14:28:45 by cboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void init_parser(t_player *player, t_map *map)
{
	player->pos = (t_vec2f){0};
	map->height = 0;
	map->width = 0;
	ft_memset(map->path_textures, 0, sizeof(map->path_textures));
	ft_memset(map->floor_rgb, 0, sizeof(map->floor_rgb));
	ft_memset(map->ceiling_rgb, 0, sizeof(map->ceiling_rgb));
}

bool app_init(t_app *app)
{
	app->time.now = 0.;
	app->time.last = 0.;
    app->ctx = mlx_init();
    if (app->ctx == MLX_NULL_HANDLE)
        return (false);
    app->info = (mlx_window_create_info){0};
    app->info.title = "Cube 3D";
    app->info.width = 800;
    app->info.height = 600;
    app->info.is_resizable = true;
    app->window = mlx_new_window(app->ctx, &app->info);
    mlx_set_window_min_size(app->ctx, app->window, 64, 64);
    if (app->window == MLX_NULL_HANDLE)
        return (false);
    app->request_immediate_abort = false;
    app->game_state = main_menu;
    app->input_handler = (t_input_handler){ 0 };
    app->minimap.showed = false;
    //mlx_set_fps_goal(app->ctx, 30);
    if (!resize_frame_buffer(app, app->info.width, app->info.height))
        return (false);
    return (true);
}
