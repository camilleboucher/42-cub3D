#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include "frame_buffer.h"
#include "mlx.h"
#include "vector.h"

typedef struct s_animated_sprite {
    t_region *frames;
    unsigned int frame_count;
    double frame_time;
    double timer;
    unsigned int frame_index;
    bool playing;
    unsigned int frame_width;
} t_animated_sprite;

t_animated_sprite animated_sprite_from_region(t_region *frames, unsigned int frame_count, float frame_time, bool playing);

mlx_color *animated_sprite_get_buffer_start(t_animated_sprite *sprite, unsigned int *frame_width);

void animated_sprite_draw(t_frame_buffer *buffer, t_animated_sprite *sprite, t_vec2i out_pos);

void animated_sprite_update(t_animated_sprite *sprite, double delta_time);

#endif
