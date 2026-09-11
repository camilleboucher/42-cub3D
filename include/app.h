#ifndef APP_H
#define APP_H

#include "input_handler.h"
#include "frame_buffer.h"
#include "atlas.h"
#include "mlx.h"
#include <stdbool.h>
#include "cub3D.h"
#include "cube3D2.h"
#include "menus.h"

typedef enum e_game_state {
    ingame,
    main_menu,
} t_game_state;

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
    t_player players[4];
    t_game_state game_state;
    t_main_menu main_menu;
} t_app;

bool app_init(t_app *app);

void app_destroy(t_app *app);

#endif