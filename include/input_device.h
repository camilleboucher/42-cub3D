#ifndef INPUT_DEVICE_H
#define INPUT_DEVICE_H

#include "vector.h"
#include <stdbool.h>

typedef struct s_app t_app;

typedef enum e_device_type
{
	device_controller,
	device_keyboard,
	device_keyboard_and_mouse,
}					t_device_type;

typedef struct s_input_device
{
	bool			active;
	t_vec2f			left_vector;
	t_vec2f			right_vector;
	t_device_type	type;
    int             controller_slot;
}					t_input_device;

void				device_notify(t_app *app, int device_id);

#endif