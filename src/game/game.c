#include "cube3D2.h"
#include "map_tools.h"
#include "mlx_keycodes.h"

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

void mouse_jail(t_app *app) {
    t_vec2i mouse_box;
    mouse_box.x = app->frame_buffer.width / 4;
    mouse_box.y = app->frame_buffer.height / 4;
    if (app->input_handler.mouse_pos.x > app->frame_buffer.width / 2 + mouse_box.x)
    {
        mlx_mouse_move(app->ctx, app->window, app->frame_buffer.width / 2 - mouse_box.x, app->input_handler.mouse_pos.y);
        app->input_handler.mouse_pos = (t_vec2i){app->frame_buffer.width / 2 - mouse_box.x, app->input_handler.mouse_pos.y};
        app->input_handler.old_mouse_pos = app->input_handler.mouse_pos;
    }
    if (app->input_handler.mouse_pos.x < app->frame_buffer.width / 2 - mouse_box.x)
    {
        mlx_mouse_move(app->ctx, app->window, app->frame_buffer.width / 2 + mouse_box.x, app->input_handler.mouse_pos.y);
        app->input_handler.mouse_pos = (t_vec2i){app->frame_buffer.width / 2 + mouse_box.x, app->input_handler.mouse_pos.y};
        app->input_handler.old_mouse_pos = app->input_handler.mouse_pos;
    }
    if (app->input_handler.mouse_pos.y < app->frame_buffer.height / 2 - mouse_box.y)
    {
        mlx_mouse_move(app->ctx, app->window, app->input_handler.mouse_pos.x, app->frame_buffer.height / 2 + mouse_box.y);
        app->input_handler.mouse_pos = (t_vec2i){app->input_handler.mouse_pos.x, app->frame_buffer.height / 2 + mouse_box.y};
        app->input_handler.old_mouse_pos = app->input_handler.mouse_pos;
    }
    if (app->input_handler.mouse_pos.y > app->frame_buffer.height / 2 + mouse_box.y)
    {
        mlx_mouse_move(app->ctx, app->window, app->input_handler.mouse_pos.x, app->frame_buffer.height / 2 - mouse_box.y);
        app->input_handler.mouse_pos = (t_vec2i){app->input_handler.mouse_pos.x, app->frame_buffer.height / 2 - mouse_box.y};
        app->input_handler.old_mouse_pos = app->input_handler.mouse_pos;
    }
}

void ingame_update(t_app *app) {
    t_raycaster raycaster;

    static double a = 1.0;
    static double last_time = 0.;
    static double old_average = 0.0;
    static unsigned int frame_count = 0;

    //printf("%f - %f\n", app->player.pos, app->player.pos.y);

    double time = get_time();
    double average = (1. / (time - last_time) + old_average * (double)frame_count) / ((double)frame_count + 1.);
    old_average = average;
    frame_count++;
    printf("frame time : %f - FPS: %f - Average: %f\n", time - last_time, 1. / (time - last_time), average);
    if (is_key_down(&app->input_handler, MLX_KEY_SPACE) && last_time != 0.)
    {
        //app->player.pos.x += (time - last_time) * 0.2;
        app->player.pos.y -= (time - last_time) * 0.4;
    }
    if (is_key_down(&app->input_handler, MLX_KEY_C)) {
        average = 0.0;
        frame_count = 0;
    }

    raycaster = (t_raycaster){0};

    raycaster.camera_pos = app->player.pos;
    raycaster.camera_dir.x = cos(app->player.angle);
    raycaster.camera_dir.y = sin(app->player.angle);
    //clear_frame_buffer(app, (mlx_color){.rgba = 0xFF0000FF});

    mouse_jail(app);
    player_input(&app->player, &app->input_handler, time - last_time);
    
    app->input_handler.total_mouse_pos.x += app->input_handler.mouse_pos.x - app->input_handler.old_mouse_pos.x;
    app->input_handler.total_mouse_pos.y += app->input_handler.mouse_pos.y - app->input_handler.old_mouse_pos.y;
    app->input_handler.old_mouse_pos = app->input_handler.mouse_pos;
    draw_raycast(app, &raycaster);
    //apply_blur(app, 32, 2);
    push_frame_buffer_to_screen(app);
    last_time = time;
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
    else if (event == MLX_WINDOW_SIZE_CHANGED)
    {
        printf("bla\n");
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

void handle_key_down(int key, void *param) {
    t_app *app;

    app = param;
    input_handler_set_down(&app->input_handler, key);
}

void handle_key_up(int key, void *param) {
    t_app *app;

    app = param;
    input_handler_set_up(&app->input_handler, key);
}

void main_loop(t_app *app)
{
    app->game_state = main_menu;

    init_main_menu(app);
    mlx_add_loop_hook(app->ctx, &game_update, app);
    mlx_on_event(app->ctx, app->window, MLX_WINDOW_EVENT, &window_event_handle, app);
    mlx_on_event(app->ctx, app->window, MLX_MOUSEUP, &handle_mouse_up, app);
    mlx_on_event(app->ctx, app->window, MLX_KEYDOWN, &handle_key_down, app);
    mlx_on_event(app->ctx, app->window, MLX_KEYUP, &handle_key_up, app);
    mlx_loop(app->ctx);
}
