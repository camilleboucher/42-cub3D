#ifndef INPUT_DEVICE_H
#define INPUT_DEVICE_H

#include "vector.h"
#include <stdbool.h>

typedef struct s_app t_app;
typedef struct s_input_handler t_input_handler;

typedef enum e_device_type
{
	device_controller,
	device_keyboard,
	device_keyboard_and_mouse,
}					t_device_type;

typedef struct s_input_device
{
	bool			active;
	t_vec2f			move_vector;
	double          angle;
	t_device_type	type;
    int             controller_slot;
}					t_input_device;

void				device_notify(t_app *app, int device_id);
void                update_mouse_and_keyboard(t_input_handler *handler, t_input_device *device);
void                update_keyboard(t_input_handler *handler, t_input_device *device, double delta_time);

#endif
