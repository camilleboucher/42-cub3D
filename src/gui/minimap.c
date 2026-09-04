#include "cub3D.h"
#include "map_tools.h"

void fill_vert_line(t_app *app, unsigned int x, unsigned int start, unsigned int stop)
{
    unsigned int y;
    unsigned int row;
    mlx_color color;

    y = start;
    row = x * app->frame_buffer.height;
    while (y <= stop)
    {
        color = get_pixel(app->frame_buffer.shader_buffer, x, y);
        set_pixel_opt(app->frame_buffer.buffer, row + y, color);
        y++;
    }
}

void mid_point_disc(t_app *app, double r, t_vec2i center)
{
    double t1 = r / 16;
    int x = r;
    int y = 0;
    while (x >= y) {
        fill_vert_line(app, center.x - x, center.y - y, center.y + y);
        fill_vert_line(app, center.x + x, center.y - y, center.y + y);
        fill_vert_line(app, center.x + y, center.y - x, center.y + x);
        fill_vert_line(app, center.x - y, center.y - x, center.y + x);
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

void draw_rect(t_region *buffer, t_vec2i pos, t_vec2i size, mlx_color color)
{
    int x;
    int y;

    x = pos.x;
    while (x < size.x + pos.x)
    {
        y = pos.y;
        while (y < size.y + pos.y)
        {
            set_pixel(buffer, x, y, color);
            y++;
        }
        x++;
    }
}

double decimal(double a)
{
    return (a - floor(a));
}

void render_map_to_buffer(t_app *app, int dist, int canvas_size, t_vec2i render_pos) {
    int map_x;
    int map_y;
    int scare_size;
    t_vec2i screen_pos;

    scare_size = canvas_size / (dist * 2);
    map_x = app->player.pos.x - (double)dist - 1;
    screen_pos = (t_vec2i){(int)((1. - decimal(app->player.pos.x) - 1.) * (double)scare_size) + render_pos.x - scare_size, 0};
    while (map_x <= app->player.pos.x + (double)dist + 1)
    {
        map_y = app->player.pos.y - (double)dist - 1;
        screen_pos.y = (int)((1. - decimal(app->player.pos.y) - 1.) * (double)scare_size) + render_pos.y - scare_size;
        while (map_y <= app->player.pos.y + (double)dist + 1)
        {
            if (map_x > 0 && map_x < app->map.width && map_y > 0 && map_y < app->map.height && map_get(&app->map, map_x, map_y) == '1')
                draw_rect(app->frame_buffer.shader_buffer, screen_pos, (t_vec2i){scare_size, scare_size}, (mlx_color){ .rgba=0x999999FF });
            else
                draw_rect(app->frame_buffer.shader_buffer, screen_pos, (t_vec2i){scare_size, scare_size}, (mlx_color){ .rgba=0xFFFFFFFF });
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

    size = (t_vec2i){app->frame_buffer.height / 5, app->frame_buffer.height / 5};
    center = (t_vec2i){50 + size.x / 2, 50 + size.y / 2};
    indicator_size = (t_vec2i){size.x / 4, size.y / 4};
    mid_point_disc(app, size.x / 2 - size.x / 50, center);
    draw_image_strech(app, (t_vec2i){50, 50}, size, app->image_atlas.images[11]);
    draw_image_strech(app, (t_vec2i){center.x + (cos(app->player.angle - M_PI / 2.) * size.x - indicator_size.x) / 2, center.y + (sin(app->player.angle - M_PI / 2.) * size.y - indicator_size.y) / 2}, indicator_size, app->image_atlas.images[7]);
    draw_image_strech(app, (t_vec2i){center.x + (cos(app->player.angle + M_PI / 2.) * size.x - indicator_size.x) / 2, center.y + (sin(app->player.angle + M_PI / 2.) * size.y - indicator_size.y) / 2}, indicator_size, app->image_atlas.images[8]);
    draw_image_strech(app, (t_vec2i){center.x + (cos(app->player.angle) * size.x - indicator_size.x) / 2, center.y + (sin(app->player.angle) * size.y - indicator_size.y) / 2}, indicator_size, app->image_atlas.images[9]);
    draw_image_strech(app, (t_vec2i){center.x + (cos(app->player.angle - M_PI) * size.x - indicator_size.x) / 2, center.y + (sin(app->player.angle - M_PI) * size.y - indicator_size.y) / 2}, indicator_size, app->image_atlas.images[10]);

    render_map_to_buffer(app, 5, size.x, (t_vec2i){50, 50});
}
