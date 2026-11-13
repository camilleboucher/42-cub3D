#include "cub3D.h"
#include "frame_buffer.h"
#include "mlx.h"
#include "ui.h"
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

void draw_rect_checked(t_region *buffer, t_vec2i pos, t_vec2i size, mlx_color color)
{
    int x;
    int y;
    t_vec2i stop;
    int y_start;

    pos.x += ((int)buffer->width - (int)size.x) / 2;
	pos.y += ((int)buffer->height - (int)size.y) / 2;
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

void draw_rect_raw(t_region *buffer, t_vec2i pos, t_vec2i size, mlx_color color)
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
    if (a < 0.)
        return (a - ceil(a));
    return (a - floor(a));
}

void minimap_put_tile(t_app *app, t_vec2i map_pos, int scare_size, t_vec2i screen_pos) {
	char cell_type;

	cell_type = map_get(&app->map, map_pos.x, map_pos.y);
	if (map_pos.x > 0 && map_pos.x < app->map.width && map_pos.y > 0 && map_pos.y < app->map.height)
	{
		if (cell_type == 1)
        	draw_image_strech(app->frame_buffer.minimap_frame_buffer, screen_pos, (t_vec2i){scare_size, scare_size}, app->image_atlas.images[32]);
		else if (cell_type >= 3 && cell_type <= 6)
        	draw_image_strech(app->frame_buffer.minimap_frame_buffer, screen_pos, (t_vec2i){scare_size, scare_size}, app->image_atlas.images[30 + cell_type]);
		else
			draw_rect_checked(app->frame_buffer.minimap_frame_buffer, screen_pos, (t_vec2i){scare_size, scare_size}, (mlx_color){ .rgba=0xFFFFFFFF });
	}
	else
    	draw_rect_checked(app->frame_buffer.minimap_frame_buffer, screen_pos, (t_vec2i){scare_size, scare_size}, (mlx_color){ .rgba=0xFFFFFFFF });
}

void render_map_to_buffer(t_app *app, int dist, int canvas_size, int offset) {
    t_vec2i map_pos;
    int scare_size;
    t_vec2i screen_pos;

    scare_size = canvas_size / (dist * 2);
    map_pos.x = ceil(app->players[0].pos.x - dist);
    screen_pos = (t_vec2i){(int)((1. - decimal(app->players[0].pos.x) - 1.) * (double)scare_size) - scare_size + offset, 0};
    while (map_pos.x <= app->players[0].pos.x + (double)dist + 1)
    {
        map_pos.y = ceil(app->players[0].pos.y - dist);
        screen_pos.y = (int)((1. - decimal(app->players[0].pos.y) - 1.) * (double)scare_size) - scare_size + offset;
        while (map_pos.y <= app->players[0].pos.y + (double)dist + 1)
        {
            minimap_put_tile(app, map_pos, scare_size, screen_pos);
            map_pos.y++;
            screen_pos.y += scare_size;
        }
        map_pos.x++;
        screen_pos.x += scare_size;
    }
}

void render_minimap(t_app *app) {
    t_vec2i center;
    t_vec2i size;
    t_vec2i indicator_size;

    //printf("%f %f\n", app->players[0].pos.x, app->players[0].pos.y);

    size = (t_vec2i){app->minimap.size.x / 4 * 3, app->minimap.size.y / 4 * 3};
    center = (t_vec2i){app->minimap.size.x / 2, app->minimap.size.y / 2};
    indicator_size = (t_vec2i){app->minimap.size.x / 4, app->minimap.size.y / 4};
    //mid_point_disc(app, size.x / 2 - size.x / 50, center);
    clear_region(app->frame_buffer.minimap_overlay_frame_buffer, (mlx_color){ .rgba=0x00000000 });
    draw_image_strech(app->frame_buffer.minimap_overlay_frame_buffer, (t_vec2i){0, 0}, size, app->image_atlas.images[31]);
    draw_image_strech(app->frame_buffer.minimap_overlay_frame_buffer, (t_vec2i){(cos(-app->players[0].angle - M_PI / 2.) * size.x) / 2, (sin(-app->players[0].angle - M_PI / 2.) * size.y) / 2}, indicator_size, app->image_atlas.images[27]);
    draw_image_strech(app->frame_buffer.minimap_overlay_frame_buffer, (t_vec2i){(cos(-app->players[0].angle + M_PI / 2.) * size.x) / 2, (sin(-app->players[0].angle + M_PI / 2.) * size.y) / 2}, indicator_size, app->image_atlas.images[28]);
    draw_image_strech(app->frame_buffer.minimap_overlay_frame_buffer, (t_vec2i){(cos(-app->players[0].angle) * size.x) / 2, (sin(-app->players[0].angle) * size.y) / 2}, indicator_size, app->image_atlas.images[29]);
    draw_image_strech(app->frame_buffer.minimap_overlay_frame_buffer, (t_vec2i){(cos(-app->players[0].angle - M_PI) * size.x) / 2, (sin(-app->players[0].angle - M_PI) * size.y) / 2}, indicator_size, app->image_atlas.images[30]);

    //printf("%f %f\n", app->players[0].pos.x, app->players[0].pos.y);
    render_map_to_buffer(app, 5, app->minimap.size.x, -app->minimap.size.x / 4);
    mid_point_disc(app, (double)size.x / 2.08, (t_vec2i){app->minimap.pos.x / 2, app->minimap.pos.y / 2});
    draw_rect_raw(app->frame_buffer.minimap_frame_buffer, (t_vec2i){0, 0}, (t_vec2i){(app->minimap.size.x - size.x / 2.1) / 4, app->minimap.size.y}, (mlx_color){ .rgba=0x00000000 });
    draw_rect_raw(app->frame_buffer.minimap_frame_buffer, (t_vec2i){app->minimap.size.x- (app->minimap.size.x - size.x / 2.1) / 4 + 1, 0}, (t_vec2i){(app->minimap.size.x - size.x / 2.1) / 4, app->minimap.size.y}, (mlx_color){ .rgba=0x00000000 });
    //draw_square(app->frame_buffer.buffer, (t_vec2i){200, 200}, 100., - M_PI / 2 + 0.5);
}
