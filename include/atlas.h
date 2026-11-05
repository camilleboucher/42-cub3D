#ifndef ATLAS_H
#define ATLAS_H

#include "animated_sprite.h"
#include "frame_buffer.h"

typedef struct s_image_atlas {
    t_region *images[50];
    t_animated_sprite animated_sprite[10];
    unsigned image_amount;
} t_image_atlas;

bool atlas_load_buttons(t_app *app);
void free_all_images(t_app *app);

#endif
