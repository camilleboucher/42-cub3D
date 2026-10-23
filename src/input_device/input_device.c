#include "input_device.h"
#include "mlx_extended.h"
#include "app.h"

void	device_notify(t_app *app, t_input_device *device)
{
    if (device->controller_slot > 0)
        mlx_controller_rumble(app->ctx, device->controller_slot, 1.0, 1.0, 1.0);
}
