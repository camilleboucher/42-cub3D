#include "app.h"
#include "input_device.h"
#include "input_handler.h"
#include "mlx_extended.h"
#include "mlx_keycodes.h"
#include "vector.h"

void	device_notify(t_app *app, int device_id)
{
	t_input_device	*device;

	if (device_id >= 2 && device_id < app->input_handler.controller_count + 2)
		device = &app->input_handler.devices[device_id];
	else
        return ;
	if (device->controller_slot >= 0 && device->active)
	{
		printf("Notifying controller %d.\n", device->controller_slot);
		mlx_controller_rumble(app->ctx, device->controller_slot, 0.5, 0.5, 1.0);
	}
}

static void    handle_keyboard_move_vector(t_input_handler *handler, t_input_device *device) {
    device->move_vector.x = 0.;
    device->move_vector.y = 0.;
    if (is_key_down(handler, MLX_KEY_D))
        device->move_vector.x = 1.0;
    if (is_key_down(handler, MLX_KEY_A))
        device->move_vector.x = -1.0;
    if (is_key_down(handler, MLX_KEY_S))
        device->move_vector.y = 1.0;
    if (is_key_down(handler, MLX_KEY_W))
        device->move_vector.y = -1.0;
    if (vec2f_lenght(device->move_vector) > 1.)
        device->move_vector = vec2f_normalize(device->move_vector);
}

void    update_keyboard(t_input_handler *handler, t_input_device *device, double delta_time) {
    handle_keyboard_move_vector(handler, device);
    if (is_key_down(handler, MLX_KEY_RIGHT))
        device->total_rotation += 600. * delta_time;
    if (is_key_down(handler, MLX_KEY_LEFT))
        device->total_rotation -= 600. * delta_time;
}

void    update_mouse_and_keyboard(t_input_handler *handler, t_input_device *device) {
    handle_keyboard_move_vector(handler, device);
    handler->devices[1].total_rotation = handler->total_mouse_pos.x;
}
