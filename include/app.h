#ifndef APP_H
#define APP_H

#include "../MacroLibX/includes/mlx.h"
#include "input_handler.h"
#include "atlas.h"

typedef struct s_region {
    unsigned int width;
    unsigned int height;
    mlx_color  buffer[];
} t_region;

typedef struct s_frame_buffer
{
    t_region *buffer;
    t_region *shader_buffer;
    unsigned int width;
    unsigned int height;
    mlx_image frame_buffer_image;
} t_frame_buffer;

struct s_app
{
    mlx_context ctx;
    mlx_window window;
    mlx_window_create_info info;
    struct s_input_handler input_handler;
    t_frame_buffer frame_buffer;
    bool request_immediate_abort;
    struct s_image_atlas image_atlas;
};

bool app_init(struct s_app *app);

void app_destroy(struct s_app *app);

bool reallocate_frame_buffer(struct s_app *app);

void clear_frame_buffer(struct s_app *app, mlx_color color);

void push_frame_buffer_to_screen(struct s_app *app);

bool resize_frame_buffer(struct s_app *app, unsigned int width, unsigned height);

void apply_blur(struct s_app *app, int distance, int quality);

#endif