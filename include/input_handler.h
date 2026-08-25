#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <stdbool.h>
#include "vector.h"

typedef struct s_input_handler {
    t_vec2i mouse_pos;
    bool    registered_click;
} t_input_handler;

#endif