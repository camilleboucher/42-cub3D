#include "input_handler.h"

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
