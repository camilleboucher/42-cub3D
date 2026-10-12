/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboucher <private_mail>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 15:54:39 by cboucher          #+#    #+#             */
/*   Updated: 2026/09/24 17:18:14 by cboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	clean_map(t_map *map)
{
	free(map->cell);
	free(map->path_textures[0]);
	free(map->path_textures[1]);
	free(map->path_textures[2]);
	free(map->path_textures[3]);
}

void app_destroy(t_app *app)
{
	clean_map(&app->map);
    free(app->frame_buffer.buffer);
    free(app->frame_buffer.shader_buffer);
    mlx_destroy_image(app->ctx, app->frame_buffer.frame_buffer_image);
    mlx_destroy_window(app->ctx, app->window);
    mlx_destroy_context(app->ctx);
}
