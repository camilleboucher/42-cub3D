#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <stdbool.h>
#include "vector.h"

typedef struct s_input_handler {
    t_vec2i mouse_pos;
    t_vec2i total_mouse_pos;
    bool    registered_click;
    int     keys[255];
    t_vec2i old_mouse_pos;
} t_input_handler;

void input_handler_set_down(t_input_handler *handler, int key);

void input_handler_set_up(t_input_handler *handler, int key);

bool is_key_down(t_input_handler *handler, int key);

#endif