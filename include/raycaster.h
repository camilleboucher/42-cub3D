#ifndef RAYCASTER_H
#define RAYCASTER_H

#include "vector.h"

typedef struct s_raycaster {
    t_vec2f camera_pos;
    double  camera_rot;
    t_vec2f camera_dir;
} t_raycaster;

void draw_raycast(t_app *app, t_raycaster *raycaster);

#endif