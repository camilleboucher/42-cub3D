#include "cube3D2.h"
#include "mlx.h"

// Adapted from https://zingl.github.io/blurring.html

void apply_blur(t_app *app, int distance, int quality)
{
    mlx_color buffer [5] = { 0 };

    unsigned int x = 0;
    while (x < (int)app->frame_buffer.width - 5)
    {
        long dif[3] = {0};
        long sum[3] = {0};
        int y = 0;
        while (y < (int)app->frame_buffer.height - 5)
        {
            sum[0] += (long)dif[0];
            sum[1] += (long)dif[1];
            sum[2] += (long)dif[2];
            mlx_color color = get_pixel(app->frame_buffer.buffer, x, y + 5);
            dif[0] += (long)color.r;
            dif[1] += (long)color.g;
            dif[2] += (long)color.b;
            if (y >= 0)
            {
                dif[0] += (long)buffer[y % 5].r;
                dif[1] += (long)buffer[y % 5].g;
                dif[2] += (long)buffer[y % 5].b;
                set_pixel(app->frame_buffer.buffer, x, y, (mlx_color){ .r = sum[0] / (5 * 5), .g = sum[1] / (5 * 5), .b = sum[2] / (5 * 5), .a=255});
            }
            if (y + 5 >= 0) {
                mlx_color p = get_pixel(app->frame_buffer.buffer, x, y);
                buffer[y % 5] = p;
                dif[0] -= 2 * (long)p.r;
                dif[1] -= 2 * (long)p.g;
                dif[2] -= 2 * (long)p.b;
            }
            y++;
        }
        x++;
    }



    unsigned int y = 0;
    while (y < (int)app->frame_buffer.height - 5)
    {
        long dif[3] = {0};
        long sum[3] = {0};
        int x = 0;
        while (x < (int)app->frame_buffer.width - 5)
        {
            sum[0] += (long)dif[0];
            sum[1] += (long)dif[1];
            sum[2] += (long)dif[2];
            mlx_color color = get_pixel(app->frame_buffer.buffer, x + 5, y);
            dif[0] += (long)color.r;
            dif[1] += (long)color.g;
            dif[2] += (long)color.b;
            if (x >= 0)
            {
                dif[0] += (long)buffer[x % 5].r;
                dif[1] += (long)buffer[x % 5].g;
                dif[2] += (long)buffer[x % 5].b;
                set_pixel(app->frame_buffer.buffer, x, y, (mlx_color){ .r = sum[0] / (5 * 5), .g = sum[1] / (5 * 5), .b = sum[2] / (5 * 5), .a=255});
            }
            if (x + 5 >= 0) {
                mlx_color p = get_pixel(app->frame_buffer.buffer, x, y);
                buffer[x % 5] = p;
                dif[0] -= 2 * (long)p.r;
                dif[1] -= 2 * (long)p.g;
                dif[2] -= 2 * (long)p.b;
            }
            x++;
        }
        y++;
    }
    
}
