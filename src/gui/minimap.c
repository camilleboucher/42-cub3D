#include "cub3D.h"
#include "frame_buffer.h"
#include "map_tools.h"
#include "mlx.h"
#include "vector.h"
#include <math.h>
#include <stdio.h>

void mask_out_vert_line(t_app *app, unsigned int x, unsigned int start, unsigned int stop)
{
    int y;
    int row;

    y = 0;
    row = x * app->frame_buffer.minimap_frame_buffer->height;
    while (y <= start)
        set_pixel_opt(app->frame_buffer.minimap_frame_buffer, row + y++, (mlx_color){ .rgba=0x00000000 });
    y = stop;
    while (y < app->minimap.size.y)
        set_pixel_opt(app->frame_buffer.minimap_frame_buffer, row + y++, (mlx_color){ .rgba=0x00000000 });
}

void mid_point_disc(t_app *app, double r, t_vec2i center)
{
    double t1 = r / 16;
    int x = r;
    int y = 0;
    while (x >= y) {
        mask_out_vert_line(app, center.x - x, center.y - y, center.y + y);
        mask_out_vert_line(app, center.x + x, center.y - y, center.y + y);
        mask_out_vert_line(app, center.x + y, center.y - x, center.y + x);
        mask_out_vert_line(app, center.x - y, center.y - x, center.y + x);
        y++;
        t1 += y;
        double t2 = t1 - x;
        if (t2 >= 0)
        {
            t1 = t2;
            x--;
        }
    }
}

void draw_square(t_region *buffer, t_vec2i pos, double size, double angle) {
    t_vec2f pos1;
    t_vec2f pos2;
    t_vec2f pos3;
    t_vec2f pos4;

    pos1 = (t_vec2f){ cos(angle) * size * 0.5 + pos.x, sin(angle) * size * 0.5 + pos.y };
    pos2 = (t_vec2f){ cos(angle - M_PI / 2) * size * 0.5 + pos.x, sin(angle - M_PI / 2) * size * 0.5 + pos.y };
    pos3 = (t_vec2f){ cos(angle - M_PI) * size * 0.5 + pos.x, sin(angle - M_PI) * size * 0.5 + pos.y };
    pos4 = (t_vec2f){ cos(angle + M_PI / 2) * size * 0.5 + pos.x, sin(angle + M_PI / 2) * size * 0.5 + pos.y };

    set_pixel(buffer, pos1.x, pos1.y, (mlx_color){ .rgba=0xFF0000FF });
    set_pixel(buffer, pos2.x, pos2.y, (mlx_color){ .rgba=0x00FF00FF });
    set_pixel(buffer, pos3.x, pos3.y, (mlx_color){ .rgba=0x00FF00FF });
    set_pixel(buffer, pos4.x, pos4.y, (mlx_color){ .rgba=0x00FFFFFF });
    double step_left = (pos1.x - pos2.x) / (pos2.y - pos1.y);
    double step_right = (pos4.x - pos1.x) / (pos4.y - pos1.y);
    printf("%f %f\n", step_left, step_right);
    if (step_right <= 0.01 || step_left <= 0.01)
        return;
    double start = pos1.x;
    double end = pos1.x;
    for (unsigned int y = 0; y < pos2.y - pos1.y; y++)
    {
        for (int x = start; x < end; x++)
            set_pixel(buffer, x, pos1.y + y, (mlx_color){ .rgba=0xFF0000FF });
        start -= step_left;
        end += step_right;
    }
}

void draw_rect(t_region *buffer, t_vec2i pos, t_vec2i size, mlx_color color)
{
    int x;
    int y;
    t_vec2i stop;
    int y_start;

    stop = (t_vec2i){pos.x + size.x, pos.y + size.y};
    x = pos.x;
    if (pos.x < 0)
        x = 0;
    y_start = pos.y;
    if (y_start < 0)
        y_start = 0;
    if (stop.x > (int)buffer->width)
        stop.x = buffer->width;
    if (stop.y > (int)buffer->height)
        stop.y = buffer->height;
    while (x < stop.x)
    {
        y = y_start;
        while (y < stop.y)
            set_pixel(buffer, x, y++, color);
        x++;
    }
}

double decimal(double a)
{
    if (a < 0)
        return (a - ceil(a));
    return (a - floor(a));
}

void render_map_to_buffer(t_app *app, int dist, int canvas_size, int offset) {
    int map_x;
    int map_y;
    int scare_size;
    t_vec2i screen_pos;

    scare_size = canvas_size / (dist * 2);
    map_x = app->player.pos.x - (double)dist - 1;
    screen_pos = (t_vec2i){(int)((1. - decimal(app->player.pos.x) - 1.) * (double)scare_size) - scare_size + offset, 0};
    while (map_x <= app->player.pos.x + (double)dist + 1)
    {
        map_y = app->player.pos.y - (double)dist - 1;
        screen_pos.y = (int)((1. - decimal(app->player.pos.y) - 1.) * (double)scare_size) - scare_size + offset;
        while (map_y <= app->player.pos.y + (double)dist + 1)
        {
            //printf("OwO %d %d\n", screen_pos.x, screen_pos.y);
            if (map_x > 0 && map_x < app->map.width && map_y > 0 && map_y < app->map.height && map_get(&app->map, map_x, map_y) == '1')
                draw_rect(app->frame_buffer.minimap_frame_buffer, screen_pos, (t_vec2i){scare_size, scare_size}, (mlx_color){ .rgba=0x999999FF });
            else
                draw_rect(app->frame_buffer.minimap_frame_buffer, screen_pos, (t_vec2i){scare_size, scare_size}, (mlx_color){ .rgba=0xFFFFFFFF });
            map_y++;
            screen_pos.y += scare_size;
        }
        map_x++;
        screen_pos.x += scare_size;
    }
}


void render_minimap(t_app *app) {
    t_vec2i center;
    t_vec2i size;
    t_vec2i indicator_size;

    //printf("%f %f\n", app->player.pos.x, app->player.pos.y);

    size = (t_vec2i){app->minimap.size.x / 4 * 3, app->minimap.size.y / 4 * 3};
    center = (t_vec2i){app->minimap.size.x / 2, app->minimap.size.y / 2};
    indicator_size = (t_vec2i){app->minimap.size.x / 4, app->minimap.size.y / 4};
    //mid_point_disc(app, size.x / 2 - size.x / 50, center);
    clear_region(app->frame_buffer.minimap_overlay_frame_buffer, (mlx_color){ .rgba=0x00000000 });
    draw_image_strech(app->frame_buffer.minimap_overlay_frame_buffer, (t_vec2i){(app->minimap.size.x - size.x) / 2, (app->minimap.size.y - size.y) / 2}, size, app->image_atlas.images[11]);
    draw_image_strech(app->frame_buffer.minimap_overlay_frame_buffer, (t_vec2i){center.x + (cos(-app->player.angle - M_PI / 2.) * size.x - indicator_size.x) / 2, center.y + (sin(-app->player.angle - M_PI / 2.) * size.y - indicator_size.y) / 2}, indicator_size, app->image_atlas.images[7]);
    draw_image_strech(app->frame_buffer.minimap_overlay_frame_buffer, (t_vec2i){center.x + (cos(-app->player.angle + M_PI / 2.) * size.x - indicator_size.x) / 2, center.y + (sin(-app->player.angle + M_PI / 2.) * size.y - indicator_size.y) / 2}, indicator_size, app->image_atlas.images[8]);
    draw_image_strech(app->frame_buffer.minimap_overlay_frame_buffer, (t_vec2i){center.x + (cos(-app->player.angle) * size.x - indicator_size.x) / 2, center.y + (sin(-app->player.angle) * size.y - indicator_size.y) / 2}, indicator_size, app->image_atlas.images[9]);
    draw_image_strech(app->frame_buffer.minimap_overlay_frame_buffer, (t_vec2i){center.x + (cos(-app->player.angle - M_PI) * size.x - indicator_size.x) / 2, center.y + (sin(-app->player.angle - M_PI) * size.y - indicator_size.y) / 2}, indicator_size, app->image_atlas.images[10]);
    
    render_map_to_buffer(app, 5, app->minimap.size.x, (app->minimap.size.x - size.x));
    mid_point_disc(app, (double)size.x / 2.1, (t_vec2i){app->minimap.pos.x / 2, app->minimap.pos.y / 2});
    draw_rect(app->frame_buffer.minimap_frame_buffer, (t_vec2i){0, 0}, (t_vec2i){(app->minimap.size.x - size.x / 2.1) / 4, app->minimap.size.y}, (mlx_color){ .rgba=0x00000000 });
    draw_rect(app->frame_buffer.minimap_frame_buffer, (t_vec2i){app->minimap.size.x- (app->minimap.size.x - size.x / 2.1) / 4 + 1, 0}, (t_vec2i){(app->minimap.size.x - size.x / 2.1) / 4, app->minimap.size.y}, (mlx_color){ .rgba=0x00000000 });
    static double a = 0.;
    a += 0.001;
    //draw_square(app->frame_buffer.buffer, (t_vec2i){200, 200}, 100., - M_PI / 2 + 0.5);
}
