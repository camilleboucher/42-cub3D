#include "menus.h"

void main_menu_window_update(void *param) {
    struct s_app *app;

    app = param;
    
}

void main_menu_window_event_handle(int event, void *param) {
    struct s_app *app;

    app = param;
    if (event == 0) {
        mlx_loop_end(app->ctx);
    }
}

void open_main_menu(struct s_app *app) {
    mlx_add_loop_hook(app->ctx, &main_menu_window_update, app);
    mlx_on_event(app->ctx, app->window, MLX_WINDOW_EVENT, &main_menu_window_event_handle, app);
    mlx_loop(app->ctx);
}
