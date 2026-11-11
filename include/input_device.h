#ifndef INPUT_DEVICE_H
# define INPUT_DEVICE_H

# include "cub3D.h"

void				device_notify(t_app *app, int device_id);
void                update_mouse_and_keyboard(t_input_handler *handler, t_input_device *device);
void                update_keyboard(t_input_handler *handler, t_input_device *device, double delta_time);

#endif
