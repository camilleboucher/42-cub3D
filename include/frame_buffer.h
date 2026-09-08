#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H

#include "mlx.h"

typedef struct s_app t_app;

typedef struct s_region
{
    unsigned int width;
    unsigned int height;
    mlx_color buffer[];
} t_region;

typedef struct s_frame_buffer
{
    t_region *buffer;
    t_region *shader_buffer;
    unsigned int width;
    unsigned int height;
    mlx_image frame_buffer_image;
    t_region *minimap_frame_buffer;
    t_region *minimap_overlay_frame_buffer;
    mlx_image minimap_frame_buffer_image;
    mlx_image minimap_overlay_frame_buffer_image;
} t_frame_buffer;

bool reallocate_frame_buffer(t_app *app);
void clear_frame_buffer(t_app *app, mlx_color color);

void push_frame_buffer_to_screen(t_app *app);

bool resize_frame_buffer(t_app *app, unsigned int width, unsigned height);

void set_pixel(t_region *frame_buffer, unsigned int x, unsigned int y, mlx_color color);
mlx_color get_pixel(t_region *frame_buffer, unsigned int x, unsigned int y);

void set_pixel_opt(t_region *frame_buffer, unsigned int i, mlx_color color);
mlx_color get_pixel_opt(t_region *frame_buffer, unsigned int i);

void clear_region(t_region *region, mlx_color color);

#endif