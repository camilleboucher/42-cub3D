#include "cube3D2.h"

#define PI 3.14159265359

bool app_init(struct s_app *app)
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
    mlx_set_fps_goal(app->ctx, 30);
    if (!resize_frame_buffer(app, app->info.width, app->info.height))
        return (false);
    return (true);
}

void app_destroy(struct s_app *app)
{
    mlx_destroy_image(app->ctx, app->frame_buffer.frame_buffer_image);
    mlx_destroy_window(app->ctx, app->window);
    mlx_destroy_context(app->ctx);
}
