#include "cube3D2.h"

void main_menu_window_update(t_app *app)
{
    clear_frame_buffer(app, (mlx_color){.rgba = 0x305050FF});
    // apply_blur(app, a / 2 % 20 + 1, 5);
    app->main_menu.play_button.pos.x = ((int)app->frame_buffer.width - (int)app->main_menu.play_button.default_image->width) / 2;
    app->main_menu.play_button.pos.y = ((int)app->frame_buffer.height - (int)app->main_menu.play_button.default_image->height) / 2;
    if (tex_button_update(app, app->main_menu.play_button))
    {
        printf("Click!\n");
        app->game_state = ingame;
    }
    push_frame_buffer_to_screen(app);
}

void handle_resize_event(t_app *app)
{
    int width;
    int height;

    mlx_get_window_size(app->ctx, app->window, &width, &height);
    if (!resize_frame_buffer(app, width, height))
        app->request_immediate_abort = true;
}

void handle_mouse_up(int button, void *param)
{
    t_app *app;

    app = param;
    if (button == 1)
        app->input_handler.registered_click = true;
}

void ingame_update(t_app *app) {
    t_raycaster raycaster;

    raycaster = (t_raycaster){0};

    raycaster.camera_pos = (t_vec2f){3, 3};
    clear_frame_buffer(app, (mlx_color){.rgba = 0xFF0000FF});
    draw_raycast(app, &raycaster);
    push_frame_buffer_to_screen(app);
}

void window_event_handle(int event, void *param)
{
    t_app *app;

    app = param;
    if (app->request_immediate_abort)
        return;
    if (event == 0)
    {
        mlx_loop_end(app->ctx);
    }
    else if (event == 8)
    {
        handle_resize_event(app);
        if (app->request_immediate_abort)
            mlx_loop_end(app->ctx);
    }
}

void init_main_menu(t_app *app)
{
    app->main_menu.play_button = tex_button_create((t_vec2i){100, 0}, (t_vec2i){485, 202}, app->image_atlas.images[0], app->image_atlas.images[1]);
}

void game_update(void *param) {
    t_app *app;

    app = param;
    if (app->request_immediate_abort)
        return;
    mlx_mouse_get_pos(app->ctx, &app->input_handler.mouse_pos.x, &app->input_handler.mouse_pos.y);
    if (app->game_state == ingame) {
        ingame_update(app);
    }
    else if (app->game_state == main_menu)
        main_menu_window_update(app);
}

void main_loop(t_app *app)
{
    app->game_state = main_menu;
    init_main_menu(app);
    mlx_add_loop_hook(app->ctx, &game_update, app);
    mlx_on_event(app->ctx, app->window, MLX_WINDOW_EVENT, &window_event_handle, app);
    mlx_on_event(app->ctx, app->window, MLX_MOUSEUP, &handle_mouse_up, app); 
    mlx_loop(app->ctx);
}
