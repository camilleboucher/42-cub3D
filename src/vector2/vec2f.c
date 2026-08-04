#include "../../include/vector.h"
#include <math.h>

t_vec2f vec2f_add(t_vec2f a, t_vec2f b) {
    t_vec2f new;
    new.x = a.x + b.x;
    new.y = a.y + b.y;
    return (new);
}

t_vec2f vec2f_comp_mul(t_vec2f a, t_vec2f b) {
    t_vec2f new;
    new.x = a.x * b.x;
    new.y = a.y * b.y;
    return (new);
}

t_vec2f vec2f_mul(t_vec2f a, float b) {
    t_vec2f new;
    new.x = a.x * b;
    new.y = a.y * b;
    return (new);
}

t_vec2f vec2f_div(t_vec2f a, float b) {
    t_vec2f new;
    new.x = a.x / b;
    new.y = a.y / b;
    return (new);
}

float vec2f_lenght(t_vec2f a) {
    float lenght;

    lenght = sqrtf(a.x * a.x + a.y * a.y);
    return (lenght);
}

float vec2f_dist(t_vec2f a, t_vec2f b) {
    float dist;
    float x_dist;
    float y_dist;

    x_dist = b.x - a.x;
    y_dist = b.y - a.y;
    dist = sqrtf(x_dist * x_dist + y_dist * y_dist);
    return (dist);
}
