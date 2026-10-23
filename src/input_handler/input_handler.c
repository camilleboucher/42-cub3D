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


t_vec2f get_controler_left_vector(t_input_handler *handler, unsigned int controller_index)
{
    return (dead_zone(handler->devices[controller_index].left_vector));
}

t_vec2f get_controler_right_vector(t_input_handler *handler, unsigned int controller_index)
{
    return (dead_zone(handler->devices[controller_index].right_vector));
}

void input_handler_update(t_input_handler *handler, mlx_context ctx)
{
    unsigned int controller_index;

    controller_index = 0;
    while (controller_index < handler->player_count)
    {
        if (handler->devices[controller_index].active && handler->devices[controller_index].type == device_controller)
        {
            handler->devices[controller_index].left_vector.x = mlx_controller_get_axis(ctx, controller_index, MLX_CONTROLLER_AXIS_LEFTX);
            handler->devices[controller_index].left_vector.y = mlx_controller_get_axis(ctx, controller_index, MLX_CONTROLLER_AXIS_LEFTY);
            handler->devices[controller_index].right_vector.x = mlx_controller_get_axis(ctx, controller_index, MLX_CONTROLLER_AXIS_RIGHTX);
            handler->devices[controller_index].right_vector.y = mlx_controller_get_axis(ctx, controller_index, MLX_CONTROLLER_AXIS_RIGHTY);
        }
        controller_index++;
    }
}
