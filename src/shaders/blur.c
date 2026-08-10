#include "cube3D2.h"

void blur_pixel(t_app *app, t_vec2i coords, int distance, int steps)
{
    t_vec2i neighbor_coords;
    unsigned int color[3];
    mlx_color other_color;
    unsigned int total_color;

    color[0] = 0;
    color[1] = 0;
    color[2] = 0;
    total_color = 0;
    neighbor_coords.x = coords.x - distance;
    if (neighbor_coords.x < 0)
        neighbor_coords.x = 0;
    while (neighbor_coords.x < coords.x + distance)
    {
        if (neighbor_coords.x >= (int)app->frame_buffer.width)
            break;
        neighbor_coords.y = coords.y - distance;
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

void apply_blur(t_app *app, int distance, int quality)
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
