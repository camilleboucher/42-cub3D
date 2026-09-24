#include "input_handler.h"
#include "mlx_extended.h"

void input_handler_set_down(t_input_handler *handler, int key)
{
    if (key >= 255 || key < 0)
        return;
    handler->keys[key] = true;
}

void input_handler_set_up(t_input_handler *handler, int key)
{
    if (key >= 255 || key < 0)
        return;
    handler->keys[key] = false;
}

bool is_key_down(t_input_handler *handler, int key)
{
    return (handler->keys[key]);
}

t_vec2f dead_zone(t_vec2f a)
{
    if (a.x > 0. && a.x < 0.05)
        a.x = 0.;
    if (a.y > 0. && a.y < 0.05)
        a.y = 0.;
    if (a.x < 0. && a.x > -0.05)
        a.x = 0.;
    if (a.y < 0. && a.y > -0.05)
        a.y = 0.;
    return (a);
}


t_vec2f get_controler_left_vector(t_input_handler *handler, unsigned int controler_index)
{
    return (dead_zone(handler->controler_vectors_left[controler_index]));
}

t_vec2f get_controler_right_vector(t_input_handler *handler, unsigned int controler_index)
{
    return (dead_zone(handler->controler_vectors_right[controler_index]));
}

void input_handler_update(t_input_handler *handler, mlx_context ctx)
{
    unsigned int controler_index;

    controler_index = 0;
    while (controler_index < handler->controler_count)
    {
        handler->controler_vectors_left[controler_index].x = mlx_controller_get_axis(ctx, controler_index, MLX_CONTROLLER_AXIS_LEFTX);
        handler->controler_vectors_left[controler_index].y = mlx_controller_get_axis(ctx, controler_index, MLX_CONTROLLER_AXIS_LEFTY);
        handler->controler_vectors_right[controler_index].x = mlx_controller_get_axis(ctx, controler_index, MLX_CONTROLLER_AXIS_RIGHTX);
        handler->controler_vectors_right[controler_index].y = mlx_controller_get_axis(ctx, controler_index, MLX_CONTROLLER_AXIS_RIGHTY);
        controler_index++;
    }
}
