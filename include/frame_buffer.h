#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H

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
} t_frame_buffer;

bool reallocate_frame_buffer(struct s_app *app);
void clear_frame_buffer(struct s_app *app, mlx_color color);

void push_frame_buffer_to_screen(struct s_app *app);

bool resize_frame_buffer(struct s_app *app, unsigned int width, unsigned height);

void set_pixel(t_region *frame_buffer, unsigned int x, unsigned int y, mlx_color color);
mlx_color get_pixel(t_region *frame_buffer, unsigned int x, unsigned int y);

#endif