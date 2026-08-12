#include "cube3D2.h"

typedef struct s_main_menu {
    t_app *app;
    t_tex_button play_button;
} t_main_menu;

void main_menu_window_update(void *param) {
    t_main_menu *menu;
    static int a = 0;

    menu = param;
    if (menu->app->request_immediate_abort)
        return ;
    clear_frame_buffer(menu->app, (mlx_color){ .rgba = 0x305050FF } );
    //apply_blur(app, a / 2 % 20 + 1, 5);
    menu->play_button.pos.x = ((int)menu->app->frame_buffer.width - (int)menu->play_button.image->width) / 2;
    menu->play_button.pos.y = ((int)menu->app->frame_buffer.height - (int)menu->play_button.image->height) / 2;
    tex_button_update(menu->app, menu->play_button);
    a++;
    push_frame_buffer_to_screen(menu->app);
}

void handle_resize_event(t_app *app) {
    int width;
    int height;

    mlx_get_window_size(app->ctx, app->window, &width, &height);
    if (!resize_frame_buffer(app, width, height))
        app->request_immediate_abort = true;
}

void main_menu_window_event_handle(int event, void *param) {
    t_app *app;

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

void init_main_menu(t_app *app, t_main_menu *menu) {
    menu->app = app;
    menu->play_button = tex_button_create((t_vec2i){100, 0}, (t_vec2i){485, 202}, menu->app->image_atlas.images[0]);
}

void open_main_menu(t_app *app) {
    t_main_menu menu;

    init_main_menu(app, &menu);
    mlx_add_loop_hook(app->ctx, &main_menu_window_update, &menu);
    mlx_on_event(app->ctx, app->window, MLX_WINDOW_EVENT, &main_menu_window_event_handle, app);
    mlx_loop(app->ctx);
}
