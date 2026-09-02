#include "cube3D2.h"

void set_pixel(t_region *frame_buffer, unsigned int x, unsigned int y, mlx_color color)
{
    frame_buffer->buffer[y + x * frame_buffer->height] = color;
}

mlx_color get_pixel(t_region *frame_buffer, unsigned int x, unsigned int y)
{
    return (frame_buffer->buffer[y + x * frame_buffer->height]);
}

void clear_frame_buffer(t_app *app, mlx_color color)
{
    unsigned int i;

    i = 0;
    while (i < app->frame_buffer.width * app->frame_buffer.height)
    {
        if (((i / app->frame_buffer.height) / 64 + (i % app->frame_buffer.height) / 64) % 2 == 0)
            app->frame_buffer.buffer->buffer[i] = color;
        else
            app->frame_buffer.buffer->buffer[i] = (mlx_color){.rgba = 0xFFFFFFFF};
        i++;
    }
}

void set_pixel_opt(t_region *frame_buffer, unsigned int i, mlx_color color)
{
    frame_buffer->buffer[i] = color;
}

mlx_color get_pixel_opt(t_region *frame_buffer, unsigned int i)
{
    return (frame_buffer->buffer[i]);
}
