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

bool app_init(t_app *app)
{
    app->ctx = mlx_init();
    if (app->ctx == MLX_NULL_HANDLE)
        return (false);
    app->info = (mlx_window_create_info){0};
    app->info.title = "Cube 3D";
    app->info.width = 800;
    app->info.height = 600;
    app->info.is_resizable = true;
    app->window = mlx_new_window(app->ctx, &app->info);
    if (app->window == MLX_NULL_HANDLE)
        return (false);
    app->frame_buffer.buffer = NULL;
    app->frame_buffer.shader_buffer = NULL;
    app->frame_buffer.frame_buffer_image = NULL;
    app->request_immediate_abort = false;
    app->input_handler = (t_input_handler){ 0 };
    //mlx_set_fps_goal(app->ctx, 30);
    if (!resize_frame_buffer(app, app->info.width, app->info.height))
        return (false);
    return (true);
}
