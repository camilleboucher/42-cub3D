#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include "frame_buffer.h"

typedef struct s_animated_sprite {
    t_region *frames;
    unsigned int frame_count;
    float frame_time;
    unsigned int frame_index;
    bool playing;
} t_animated_sprite;

t_animated_sprite animated_sprite_from_region(t_region *frames, unsigned int frame_count, float frame_time, bool playing) {
    t_animated_sprite sprite;

    sprite.frames = frames;
    sprite.frame_count = frame_count;
    sprite.frame_time = frame_time;
    sprite.frame_index = 0;
    sprite.playing = playing;
    return (sprite);
}

mlx_color *animated_sprite_get_buffer_start(t_animated_sprite *sprite, unsigned int *frame_width) {
    *frame_width = sprite->frames->width / sprite->frame_count;
    return (sprite->frames->buffer + ((*frame_width * sprite->frames->height) * sprite->frame_index));
}

#endif