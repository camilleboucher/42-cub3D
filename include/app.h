#ifndef APP_H
#define APP_H

#include "input_handler.h"
#include "frame_buffer.h"
#include "atlas.h"
#include "mlx.h"
#include <stdbool.h>
#include "cub3D.h"

typedef struct s_app
{
    mlx_context ctx;
    mlx_window window;
    mlx_window_create_info info;
    t_input_handler input_handler;
    t_frame_buffer frame_buffer;
    bool request_immediate_abort;
    t_image_atlas image_atlas;
    t_map map;
    t_player player;
} t_app;

bool app_init(t_app *app);

void app_destroy(t_app *app);

void apply_blur(t_app *app, int distance, int quality);

#endif