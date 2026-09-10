#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include "mlx.h"
#include "vector.h"
#include <stdbool.h>

typedef struct s_input_handler {
  t_vec2i mouse_pos;
  t_vec2f total_mouse_pos;
  bool registered_click;
  int keys[255];
  t_vec2i old_mouse_pos;
  unsigned int controler_count;
  t_vec2f controler_vectors_left[4];
  t_vec2f controler_vectors_right[4];
} t_input_handler;

void input_handler_set_down(t_input_handler *handler, int key);

void input_handler_set_up(t_input_handler *handler, int key);

bool is_key_down(t_input_handler *handler, int key);

t_vec2f get_controler_left_vector(t_input_handler *handler, unsigned int controler_index);

t_vec2f get_controler_right_vector(t_input_handler *handler, unsigned int controler_index);

void input_handler_update(t_input_handler *handler, mlx_context ctx);

#endif