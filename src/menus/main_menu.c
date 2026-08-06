#include "menus.h"

void main_menu_window_update(void *param) {
    struct s_app *app;
    static int a = 0;

    app = param;
    if (app->request_immediate_abort)
        return ;
    clear_frame_buffer(app, (mlx_color){ .rgba = 0x305050FF } );
    apply_blur(app, a / 2 % 20 + 1, 5);
    a++;
    push_frame_buffer_to_screen(app);
}

void handle_resize_event(struct s_app *app) {
    int width;
    int height;

    mlx_get_window_size(app->ctx, app->window, &width, &height);
    if (!resize_frame_buffer(app, width, height))
        app->request_immediate_abort = true;
}

void main_menu_window_event_handle(int event, void *param) {
    struct s_app *app;

    app = param;
    if (app->request_immediate_abort)
        return ;
    if (event == 0) {
        mlx_loop_end(app->ctx);
    }
    else if (event == 8) {
        handle_resize_event(app);
        if (app->request_immediate_abort)
            mlx_loop_end(app->ctx);
    }
}

void open_main_menu(struct s_app *app) {
    mlx_add_loop_hook(app->ctx, &main_menu_window_update, app);
    mlx_on_event(app->ctx, app->window, MLX_WINDOW_EVENT, &main_menu_window_event_handle, app);
    mlx_loop(app->ctx);
}
