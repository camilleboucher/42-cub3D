#include "cube3D2.h"

t_vec2i vec2i_add(t_vec2i a, t_vec2i b) {
    t_vec2i new;
    new.x = a.x + b.x;
    new.y = a.y + b.y;
    return (new);
}

t_vec2i vec2i_comp_mul(t_vec2i a, t_vec2i b) {
    t_vec2i new;
    new.x = a.x * b.x;
    new.y = a.y * b.y;
    return (new);
}

t_vec2i vec2i_mul(t_vec2i a, int b) {
    t_vec2i new;
    new.x = a.x + b;
    new.y = a.y + b;
    return (new);
}

t_vec2i vec2i_div(t_vec2i a, int b) {
    t_vec2i new;
    new.x = a.x / b;
    new.y = a.y / b;
    return (new);
}
