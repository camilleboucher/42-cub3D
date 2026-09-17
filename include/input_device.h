#include "vector.h"
#include <stdbool.h>

struct s_input_device {
    bool active;
    t_vec2f left_vector;
    t_vec2f right_vector;
} t_input_device;