#include "app.h"
#include "input_device.h"
#include "mlx_extended.h"

void	device_notify(t_app *app, int device_id)
{
	t_input_device	*device;

	if (device_id >= 0 && device_id < app->input_handler.controller_count)
		device = &app->input_handler.devices[device_id];
	if (device->controller_slot >= 0 && device->active)
	{
		printf("Notifying controller %d.\n", device->controller_slot);
		mlx_controller_rumble(app->ctx, device->controller_slot, 0.5, 0.5, 1.0);
	}
}
