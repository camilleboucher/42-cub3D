#include "cube3D2.h"
#include "mlx.h"
#include "vector.h"
#include <stdio.h>

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
    *frame_buffer_image = mlx_new_image(app->ctx, app->frame_buffer.screen_height, app->frame_buffer.screen_width);
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
    if (app->frame_buffer.screen_image != NULL)
        mlx_destroy_image(app->ctx, app->frame_buffer.screen_image);
    app->frame_buffer.screen_image = frame_buffer_image;
    return (true);
}

bool resize_frame_buffer(t_app *app, unsigned int width, unsigned height)
{
    app->frame_buffer.screen_width = width;
    app->frame_buffer.screen_height = height;
    if (app->game_state != ingame || app->input_handler.controler_count == 1)
    {
        app->frame_buffer.width = width;
        app->frame_buffer.height = height;
    }
    else if (app->input_handler.controler_count == 2)
    {
        app->frame_buffer.width = width / 2;
        app->frame_buffer.height = height;
    }
    else if (app->input_handler.controler_count == 3 || app->input_handler.controler_count == 4)
    {
        app->frame_buffer.width = width / 2;
        app->frame_buffer.height = height / 2;
    }
    if (!reallocate_frame_buffer(app))
        return (false);
    clear_frame_buffer(app, (mlx_color){.rgba = 0x000000FF});
    return (true);
}

void push_buffer_to_screen_image(t_app *app, unsigned int sub_screen_index)
{
    t_vec2i offset;

    offset = (t_vec2i){0, 0};
    if (app->input_handler.controler_count > 1)
        offset = (t_vec2i){(sub_screen_index % 2) * app->frame_buffer.width, (sub_screen_index / 2) * app->frame_buffer.height};
    printf("%d %d\n", offset.x, offset.y);
    mlx_set_image_region(app->ctx, app->frame_buffer.screen_image, offset.y, offset.x, 
        app->frame_buffer.buffer->height, app->frame_buffer.buffer->width, 
        app->frame_buffer.buffer->buffer);
}

void push_frame_buffer_to_screen(t_app *app)
{
    mlx_clear_window(app->ctx, app->window, (mlx_color){.rgba = 0x000000FF});
    mlx_put_transformed_image_to_window(app->ctx, app->window, 
        app->frame_buffer.screen_image, 
        ((float)app->frame_buffer.screen_width + (float)app->frame_buffer.screen_height) / 2.f, 
        ((float)app->frame_buffer.screen_height - (float)app->frame_buffer.screen_width) / 2.f, -1, 1, 90);
}
