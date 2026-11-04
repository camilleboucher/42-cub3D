#include "input_handler.h"
#include "input_device.h"
#include "mlx_extended.h"
#include "vector.h"

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

double dead_one_axis(double a)
{
    if (a > 0. && a < 0.05)
        a = 0.;
    if (a < 0. && a > -0.05)
        a = 0.;
    return (a);
}

t_vec2f get_controler_left_vector(t_input_handler *handler, unsigned int controller_index)
{
    return (dead_zone(handler->devices[controller_index].move_vector));
}

int get_controler_total_rotation(t_input_handler *handler, unsigned int controller_index)
{
    return (handler->devices[controller_index].total_rotation);
}

void input_handler_update(t_input_handler *handler, mlx_context ctx, double delta_time)
{
    unsigned int controller_index;

    controller_index = 0;
    while (controller_index < handler->controller_count)
    {
        if (handler->devices[controller_index + 2].active && handler->devices[controller_index + 2].type == device_controller)
        {
            handler->devices[controller_index + 2].move_vector.x = mlx_controller_get_axis(ctx, controller_index, MLX_CONTROLLER_AXIS_LEFTX);
            handler->devices[controller_index + 2].move_vector.y = mlx_controller_get_axis(ctx, controller_index, MLX_CONTROLLER_AXIS_LEFTY);
            handler->devices[controller_index + 2].total_rotation += dead_one_axis(mlx_controller_get_axis(ctx, controller_index, MLX_CONTROLLER_AXIS_RIGHTX)) * 600. * delta_time;
        }
        controller_index++;
    }
}

void init_devices(t_input_handler *handler) {
    handler->devices[0].active = true;
    handler->devices[0].controller_slot = -1;
    handler->devices[0].type = device_keyboard;
    handler->devices[0].move_vector = (t_vec2f){0, 0};
    handler->devices[0].total_rotation = 0;
    handler->devices[1].active = true;
    handler->devices[1].controller_slot = -2;
    handler->devices[1].type = device_keyboard_and_mouse;
    handler->devices[1].move_vector = (t_vec2f){0., 0.};
    handler->devices[1].total_rotation = 0;
    unsigned int i = 0;
    while (i < handler->controller_count) {
        handler->devices[2 + i].active = true;
        handler->devices[2 + i].controller_slot = i;
        handler->devices[2 + i].type = device_controller;
        handler->devices[2 + i].move_vector = (t_vec2f){0., 0.};
        handler->devices[2 + i].total_rotation = 0;
        i++;
    }
}
