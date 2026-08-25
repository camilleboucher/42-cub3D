#include "cube3D2.h"

typedef struct s_main_menu {
    t_app *app;
    t_tex_button play_button;
} t_main_menu;

void main_menu_window_update(void *param) {
    t_main_menu *menu;

    menu = param;
    if (menu->app->request_immediate_abort)
        return ;
    clear_frame_buffer(menu->app, (mlx_color){ .rgba = 0x305050FF } );
    //apply_blur(app, a / 2 % 20 + 1, 5);
    mlx_mouse_get_pos(menu->app->ctx, &menu->app->input_handler.mouse_pos.x, &menu->app->input_handler.mouse_pos.y);
    menu->play_button.pos.x = ((int)menu->app->frame_buffer.width - (int)menu->play_button.default_image->width) / 2;
    menu->play_button.pos.y = ((int)menu->app->frame_buffer.height - (int)menu->play_button.default_image->height) / 2;
    if (tex_button_update(menu->app, menu->play_button))
        printf("Click!\n");
    push_frame_buffer_to_screen(menu->app);
}

void handle_resize_event(t_app *app) {
    int width;
    int height;

    mlx_get_window_size(app->ctx, app->window, &width, &height);
    if (!resize_frame_buffer(app, width, height))
        app->request_immediate_abort = true;
}

void handle_mouse_up(int button, void *param) {
    t_main_menu *menu;

    menu = param;
    if (button == 1)
        menu->app->input_handler.registered_click = true;
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
    menu->play_button = tex_button_create((t_vec2i){100, 0}, (t_vec2i){485, 202}, menu->app->image_atlas.images[0], menu->app->image_atlas.images[1]);
}

void open_main_menu(t_app *app) {
    t_main_menu menu;

    init_main_menu(app, &menu);
    mlx_add_loop_hook(app->ctx, &main_menu_window_update, &menu);
    mlx_on_event(app->ctx, app->window, MLX_WINDOW_EVENT, &main_menu_window_event_handle, app);
    mlx_on_event(app->ctx, app->window, MLX_MOUSEUP, &handle_mouse_up, &menu);
    mlx_loop(app->ctx);
}
