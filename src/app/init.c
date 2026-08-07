#include "mlx.h"
#include "mlx_extended.h"
#include "input_handler.h"
#include "app.h"
#include <stdlib.h>
#include "vector.h"

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


static bool allocate_buffers(struct s_app *app, t_region **buffer, t_region **shader_buffer, mlx_image *frame_buffer_image)
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

bool reallocate_frame_buffer(struct s_app *app)
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

bool resize_frame_buffer(struct s_app *app, unsigned int width, unsigned height) 
{
    app->frame_buffer.width = width;
    app->frame_buffer.height = height;
    if (!reallocate_frame_buffer(app))
        return (false);
    clear_frame_buffer(app, (mlx_color){ .rgba = 0x000000FF });
    return (true);
}

void set_pixel(t_region *frame_buffer, unsigned int x, unsigned int y, mlx_color color) {
    frame_buffer->buffer[y + x * frame_buffer->height] = color;
}

mlx_color get_pixel(t_region *frame_buffer, unsigned int x, unsigned int y) {
    return (frame_buffer->buffer[y + x * frame_buffer->height]);
}

void clear_frame_buffer(struct s_app *app, mlx_color color)
{
    unsigned int i;

    i = 0;
    while (i < app->frame_buffer.width * app->frame_buffer.height)
    {
        if (((i / app->frame_buffer.height) / 64 + (i % app->frame_buffer.height) / 64) % 2 == 0)
            app->frame_buffer.buffer->buffer[i] = color;
        else
            app->frame_buffer.buffer->buffer[i] = (mlx_color){ .rgba = 0xFFFFFFFF };
        i++;
    }
}

void blur_pixel(struct s_app *app, t_vec2i coords, int distance, int steps)
{
    t_vec2i neighbor_coords;
    unsigned int color[3];
    mlx_color other_color;
    unsigned int total_color;

    color[0] = 0;
    color[1] = 0;
    color[2] = 0;
    total_color = 0;
    neighbor_coords.x = coords.x;
    if (neighbor_coords.x < 0)
        neighbor_coords.x = 0;
    while (neighbor_coords.x < coords.x + distance)
    {
        if (neighbor_coords.x >= (int)app->frame_buffer.width)
            break;
        neighbor_coords.y = coords.y;
        if (neighbor_coords.y < 0)
            neighbor_coords.y = 0;
        while (neighbor_coords.y < coords.y + distance)
        {
            if (neighbor_coords.y >= (int)app->frame_buffer.height)
                break;
            other_color = get_pixel(app->frame_buffer.buffer, neighbor_coords.x, neighbor_coords.y);
            color[0] += other_color.r;
            color[1] += other_color.g;
            color[2] += other_color.b;
            total_color++;
            neighbor_coords.y += steps;
        }
        neighbor_coords.x += steps;
    }
    set_pixel(app->frame_buffer.shader_buffer, coords.x, coords.y, (mlx_color){.r = color[0] / total_color, .g = color[1] / total_color, .b = color[2] / total_color, .a = 0xFF});
}

void apply_blur(struct s_app *app, int distance, int quality)
{
    t_vec2i coords;
    t_region *temp_swap;
    int steps;

    steps = distance / quality;
    if (steps < 1)
        steps = 1;
    coords.x = 0;
    while (coords.x < (int)app->frame_buffer.width)
    {
        coords.y = 0;
        while (coords.y < (int)app->frame_buffer.height)
        {
            blur_pixel(app, coords, distance, steps);
            coords.y++;
        }
        coords.x++;
    }
    temp_swap = app->frame_buffer.shader_buffer;
    app->frame_buffer.shader_buffer = app->frame_buffer.buffer;
    app->frame_buffer.buffer = temp_swap;
}

void push_frame_buffer_to_screen(struct s_app *app)
{
    static int a = 0;

    a ++;
    mlx_clear_window(app->ctx, app->window, (mlx_color){ .rgba = 0x000000FF });
    mlx_set_image_region(app->ctx, app->frame_buffer.frame_buffer_image, 0, 0, app->frame_buffer.buffer->height, app->frame_buffer.buffer->width, app->frame_buffer.buffer->buffer);
    mlx_put_transformed_image_to_window(app->ctx, app->window, app->frame_buffer.frame_buffer_image, ((int)app->frame_buffer.width - (int)app->frame_buffer.height) / 2, ((int)app->frame_buffer.height - (int)app->frame_buffer.width) / 2, 1, 1, -90);
    //mlx_put_image_to_window(app->ctx, app->window, app->frame_buffer.frame_buffer_image, 0, 0);
}
