#ifndef APP_H
#define APP_H

#include "../MacroLibX/includes/mlx.h"
#include "input_handler.h"

struct s_app
{
    mlx_context ctx;
    mlx_window  window;
    mlx_window_create_info info;
    struct s_input_handler input_handler;
};

bool app_init(struct s_app *app);

void app_destroy(struct s_app *app);

#endif