#include "cube3D2.h"
#include "vector.h"
#include "raycaster.h"
#include "map_tools.h"

void draw_vertical_line(t_app *app, unsigned int x, int start, int end) {
    unsigned int y;

    y = start;
    if (end > app->frame_buffer.height)
        end = app->frame_buffer.height;
    while (y < end)
    {
        set_pixel(app->frame_buffer.buffer, x, y, (mlx_color){ .rgba = 0x00FF00FF});
        y++;
    }
}

double dabs(double a) {
    unsigned long int*b=(unsigned long int *)&a;
    *b&=(0ul << 63u);
    return *(double *)b;
}

void draw_raycast(t_app *app, t_raycaster *raycaster) {
    int x;
    t_vec2f dir = {-1., 0.};
    t_vec2f plane = {0, 0.66};

    x = 0;
    while (x < app->frame_buffer.width) {
        double camera_x = 2 * x / (double)app->frame_buffer.width - 1;
        t_vec2f ray_dir = {dir.x + plane.x * camera_x, dir.y + plane.y * camera_x};
        t_vec2i map_pos = {(int)raycaster->camera_pos.x , (int)raycaster->camera_pos.y};
        t_vec2f side_dist;
        t_vec2f delta_dist;

        if (ray_dir.x == 0.)
            delta_dist.x = 1e30;
        else
            delta_dist.x = fabs(1 / ray_dir.x);
        if (ray_dir.y == 0.)
            delta_dist.y = 1e30;
        else
            delta_dist.y = fabs(1 / ray_dir.y);
        double perp_wall_dist;
        t_vec2f step;
        int hit = 0;
        int side;
        if (ray_dir.x < 0)
        {
            step.x = -1.;
            side_dist.x = (raycaster->camera_pos.x - map_pos.x) * delta_dist.x;
        }
        else
        {
            step.x = 1.;
            side_dist.x = (map_pos.x + 1. - raycaster->camera_pos.x) * delta_dist.x;
        }
        if (ray_dir.y < 0)
        {
            step.y = -1.;
            side_dist.y = (raycaster->camera_pos.y - map_pos.y) * delta_dist.y;
        }
        else
        {
            step.y = 1.;
            side_dist.y = (map_pos.y + 1. - raycaster->camera_pos.y) * delta_dist.y;
        }
        while (!hit)
        {
            if (side_dist.x < side_dist.y)
            {
                side_dist.x += delta_dist.x;
                map_pos.x += step.x;
                side = 0;
            }
            else
            {
                side_dist.y += delta_dist.y;
                map_pos.y += step.y;
                side = 1;
            }
            if (map_get(&app->map, map_pos.x, map_pos.y) != '0')
                hit = 1;
        }
        if(side == 0)
            perp_wall_dist = side_dist.x - delta_dist.x;
        else
            perp_wall_dist = side_dist.y - delta_dist.y;

        int line_height = (int)((double)app->frame_buffer.height / perp_wall_dist);
        int draw_start = ((int)app->frame_buffer.height - (int)line_height) / 2;
        if (draw_start < 0)
            draw_start = 0;
        int draw_end = ((int)app->frame_buffer.height + (int)line_height) / 2;
        if (draw_end < 0)
            draw_end = (int)app->frame_buffer.height - 1;
        draw_vertical_line(app, x, draw_start, draw_end);
        x++;
    }
}
