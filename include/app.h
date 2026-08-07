#ifndef APP_H
#define APP_H

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

void apply_blur(struct s_app *app, int distance, int quality);

#endif