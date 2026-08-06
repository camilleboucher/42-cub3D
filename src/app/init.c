#include "mlx.h"
#include "mlx_extended.h"
#include "input_handler.h"
#include "app.h"
#include <stdlib.h>

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

bool reallocate_frame_buffer(struct s_app *app)
{
    mlx_color *buffer;
    mlx_image frame_buffer_image;

    buffer = malloc(sizeof(mlx_color) * (app->frame_buffer.width * app->frame_buffer.height));
    if (!buffer)
        return (false);
    frame_buffer_image = mlx_new_image(app->ctx, app->frame_buffer.width, app->frame_buffer.height);
    if (frame_buffer_image == MLX_NULL_HANDLE)
    {
        free(buffer);
        return (false);
    }
    free(app->frame_buffer.buffer);
    app->frame_buffer.buffer = buffer;
    if (app->frame_buffer.frame_buffer_image != NULL)
        mlx_destroy_image(app->ctx, app->frame_buffer.frame_buffer_image);
    app->frame_buffer.frame_buffer_image = frame_buffer_image;
    return (true);
}

bool resize_frame_buffer(struct s_app *app, unsigned int width, unsigned height) 
{
    app->frame_buffer.width = width;
    app->frame_buffer.height = height;
    if (!reallocate_frame_buffer(app))
        return (false);
    clear_frame_buffer(app, (mlx_color){ .rgba = 0x000000FF });
    return (true);
}

void clear_frame_buffer(struct s_app *app, mlx_color color)
{
    unsigned int i;

    i = 0;
    while (i < app->frame_buffer.width * app->frame_buffer.height)
    {
        if (((i / app->frame_buffer.width) / 32 + (i % app->frame_buffer.width) / 32) % 2 == 0)
            app->frame_buffer.buffer[i] = color;
        else
            app->frame_buffer.buffer[i] = (mlx_color){ .rgba = 0xFFFFFFFF };
        i++;
    }
}

void push_frame_buffer_to_screen(struct s_app *app)
{
    mlx_clear_window(app->ctx, app->window, (mlx_color){ .rgba = 0x000000FF });
    mlx_set_image_region(app->ctx, app->frame_buffer.frame_buffer_image, 0, 0, app->frame_buffer.width, app->frame_buffer.height, app->frame_buffer.buffer);
    mlx_put_image_to_window(app->ctx, app->window, app->frame_buffer.frame_buffer_image, 0, 0);
}
