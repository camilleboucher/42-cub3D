#include "cube3D2.h"
#include "mlx.h"

#define BLUR_RADIUS 64

void clear_buffer(mlx_color *buffer, long sum[3], mlx_color color, unsigned int size) {
    unsigned int i;

    sum[0] = size * (long)color.r;
    sum[1] = size * (long)color.g;
    sum[2] = size * (long)color.b;
    i = 0;
    while (i < size)
        buffer[i++] = color;
}

void apply_blur(t_app *app)
{
    mlx_color buffer[BLUR_RADIUS];

    unsigned int row = 0;
    while (row < app->frame_buffer.width * app->frame_buffer.height)
    {
        long sum[3] = {0};
        clear_buffer(buffer, sum, get_pixel_opt(app->frame_buffer.buffer, row), BLUR_RADIUS);
        int y = 0;
        while (y < app->frame_buffer.height)
        {
            sum[0] -= buffer[y % BLUR_RADIUS].r;
            sum[1] -= buffer[y % BLUR_RADIUS].g;
            sum[2] -= buffer[y % BLUR_RADIUS].b;
            mlx_color color = get_pixel_opt(app->frame_buffer.buffer, row + y);
            sum[0] += color.r;
            sum[1] += color.g;
            sum[2] += color.b;
            buffer[y % BLUR_RADIUS] = color;
            set_pixel_opt(app->frame_buffer.shader_buffer, row + y, (mlx_color){.r = sum[0] / BLUR_RADIUS, .g = sum[1] / BLUR_RADIUS, .b = sum[2] / BLUR_RADIUS, .a = 255});
            y++;
        }
        row += app->frame_buffer.height;
    }

    unsigned int y = 0;
    while (y < app->frame_buffer.height)
    {
        long sum[3] = {0};
        clear_buffer(buffer, sum, get_pixel_opt(app->frame_buffer.shader_buffer, y), BLUR_RADIUS);
        int x = 0;
        int row = 0;
        while (x < app->frame_buffer.width)
        {
            sum[0] -= buffer[x % BLUR_RADIUS].r;
            sum[1] -= buffer[x % BLUR_RADIUS].g;
            sum[2] -= buffer[x % BLUR_RADIUS].b;
            mlx_color color = get_pixel_opt(app->frame_buffer.shader_buffer, row + y);
            sum[0] += color.r;
            sum[1] += color.g;
            sum[2] += color.b;
            buffer[x % BLUR_RADIUS] = color;
            set_pixel_opt(app->frame_buffer.buffer, row + y, (mlx_color){.r = sum[0] / BLUR_RADIUS, .g = sum[1] / BLUR_RADIUS, .b = sum[2] / BLUR_RADIUS, .a = 255});
            x++;
            row += app->frame_buffer.height;
        }
        y++;
    }
}
