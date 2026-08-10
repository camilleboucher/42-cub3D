#include "cube3D2.h"

static bool allocate_buffers(t_app *app, t_region **buffer, t_region **shader_buffer, mlx_image *frame_buffer_image)
{
    *buffer = malloc(sizeof(t_region) + sizeof(mlx_color) * (app->frame_buffer.width * app->frame_buffer.height));
    if (!buffer)
        return (false);
    *shader_buffer = malloc(sizeof(t_region) + sizeof(mlx_color) * (app->frame_buffer.width * app->frame_buffer.height));
    if (!*shader_buffer)
    {
        free(*buffer);
        return (false);
    }
    *frame_buffer_image = mlx_new_image(app->ctx, app->frame_buffer.height, app->frame_buffer.width);
    if (*frame_buffer_image == MLX_NULL_HANDLE)
    {
        free(*buffer);
        free(*shader_buffer);
        return (false);
    }
    return (true);
}

bool reallocate_frame_buffer(t_app *app)
{
    t_region *buffer;
    t_region *shader_buffer;
    mlx_image frame_buffer_image;

    if (!allocate_buffers(app, &buffer, &shader_buffer, &frame_buffer_image))
        return (false);
    free(app->frame_buffer.buffer);
    app->frame_buffer.buffer = buffer;
    buffer->width = app->frame_buffer.width;
    buffer->height = app->frame_buffer.height;
    free(app->frame_buffer.shader_buffer);
    app->frame_buffer.shader_buffer = shader_buffer;
    shader_buffer->width = app->frame_buffer.width;
    shader_buffer->height = app->frame_buffer.height;
    if (app->frame_buffer.frame_buffer_image != NULL)
        mlx_destroy_image(app->ctx, app->frame_buffer.frame_buffer_image);
    app->frame_buffer.frame_buffer_image = frame_buffer_image;
    return (true);
}

bool resize_frame_buffer(t_app *app, unsigned int width, unsigned height) 
{
    app->frame_buffer.width = width;
    app->frame_buffer.height = height;
    if (!reallocate_frame_buffer(app))
        return (false);
    clear_frame_buffer(app, (mlx_color){ .rgba = 0x000000FF });
    return (true);
}

void push_frame_buffer_to_screen(t_app *app)
{
    static int a = 0;

    a ++;
    mlx_clear_window(app->ctx, app->window, (mlx_color){ .rgba = 0x000000FF });
    mlx_set_image_region(app->ctx, app->frame_buffer.frame_buffer_image, 0, 0, app->frame_buffer.buffer->height, app->frame_buffer.buffer->width, app->frame_buffer.buffer->buffer);
    mlx_put_transformed_image_to_window(app->ctx, app->window, app->frame_buffer.frame_buffer_image, ((int)app->frame_buffer.width - (int)app->frame_buffer.height) / 2, ((int)app->frame_buffer.height - (int)app->frame_buffer.width) / 2, 1, 1, -90);
}
