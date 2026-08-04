#include "mlx.h"
#include "mlx_extended.h"
#include "input_handler.h"
#include "app.h"

bool app_init(struct s_app *app) {
    (*app).ctx = mlx_init();
    if ((*app).ctx == MLX_NULL_HANDLE)
        return (false);
    (*app).info = (mlx_window_create_info){ 0 };
    (*app).info.title = "Cube 3D";
    (*app).info.width = 800;
    (*app).info.height = 600;
    (*app).window = mlx_new_window((*app).ctx, &(*app).info);
}

void app_destroy(struct s_app *app) {
    mlx_destroy_window(app->ctx, app->window);
    mlx_destroy_context(app->ctx);
}
