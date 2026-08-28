/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/27 18:49:14 by yben-dje          #+#    #+#             */
/*   Updated: 2026/08/28 13:47:40 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D2.h"
#include "vector.h"
#include "raycaster.h"
#include "map_tools.h"


void set_pixel_opt(t_region *frame_buffer, unsigned int i, mlx_color color)
{
    frame_buffer->buffer[i] = color;
}

mlx_color get_pixel_opt(t_region *frame_buffer, unsigned int i)
{
    return (frame_buffer->buffer[i]);
}

void draw_vertical_line(t_app *app, unsigned int x, int line_height, int tex_x) {
    unsigned int y;

    int draw_start = ((int)app->frame_buffer.height - line_height) / 2;
    if (draw_start < 0)
        draw_start = 0;
    int draw_end = ((int)app->frame_buffer.height + line_height) / 2;
    if (draw_end > app->frame_buffer.height)
        draw_end = app->frame_buffer.height;
    double step = 64. / (double)line_height;
    double tex_pos = (draw_start - app->frame_buffer.height / 2. + line_height / 2.) * step;
    y = 0;
    unsigned int fb_row = x * app->frame_buffer.buffer->height;
    while (y < draw_start)
        set_pixel_opt(app->frame_buffer.buffer, fb_row + y++, (mlx_color){ .rgba = 0x000000FF});
    unsigned int tex_row = tex_x * app->image_atlas.images[2]->height;
    while (y < draw_end)
    {
        tex_pos += step;
        mlx_color color = get_pixel_opt(app->image_atlas.images[2], tex_row + ((unsigned int)tex_pos & (64 - 1)));
        set_pixel_opt(app->frame_buffer.buffer, fb_row + y++, color);
    }
    while (y < app->frame_buffer.height)
        set_pixel_opt(app->frame_buffer.buffer, fb_row + y++, (mlx_color){ .rgba = 0x000000FF});
}

double dabs(double a) {
    unsigned long int*b=(unsigned long int *)&a;
    *b&=~(1ul << 63u);
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
            delta_dist.x = fabs(1. / ray_dir.x);
        if (ray_dir.y == 0.)
            delta_dist.y = 1e30;
        else
            delta_dist.y = fabs(1. / ray_dir.y);
        double perp_wall_dist;
        t_vec2f step;
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
        while (1)
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
                break;
        }
        if(side == 0)
            perp_wall_dist = side_dist.x - delta_dist.x;
        else
            perp_wall_dist = side_dist.y - delta_dist.y;

        int line_height = app->frame_buffer.height / perp_wall_dist;

        double wall_x;
        if (side == 0)
            wall_x = raycaster->camera_pos.y + perp_wall_dist * ray_dir.y;
        else
            wall_x = raycaster->camera_pos.x + perp_wall_dist * ray_dir.x;
        wall_x -= floorf(wall_x);
        int tex_x = wall_x * 64.;
        if (side == 0 && ray_dir.x > 0) tex_x = 64 - tex_x - 1;
        if (side == 1 && ray_dir.x < 0) tex_x = 64 - tex_x - 1;
        draw_vertical_line(app, x, line_height, tex_x);
        x++;
    }
}
