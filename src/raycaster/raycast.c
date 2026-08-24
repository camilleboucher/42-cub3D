#include "cube3D2.h"
#include "vector.h"
#include "raycaster.h"
#include "map_tools.h"

void draw_raycast(t_app *app, t_raycaster *raycaster) {
    unsigned int x;
    t_vec2f dir = {-1., 0.};
    t_vec2f plane = {0, 0.66};

    x = 0;
    while (x < app->frame_buffer.width) {
        double camera_x = 2 * x / (double)app->frame_buffer.width - 1;
        t_vec2f ray_dir = {dir.x + plane.x * raycaster->camera_pos.x, dir.y + plane.y * raycaster->camera_pos.y};
        t_vec2i map_pos = {raycaster->camera_pos.x, raycaster->camera_pos.y};
        t_vec2f side_dist;
        t_vec2f delta_dist;
        if (ray_dir.x)
            delta_dist.x = 1e42;
        else
            delta_dist.x = fabs(1 / ray_dir.x);
        if (ray_dir.y)
            delta_dist.y = 1e42;
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
    }
}
