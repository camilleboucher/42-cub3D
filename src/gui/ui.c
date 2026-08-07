#include "cube3D2.h"


typedef struct s_tex_button
{
    t_vec2i pos;
    t_vec2i size;
    char *text;
    bool is_hover;
    bool is_down;
    mlx_image image;
} t_tex_button;

typedef struct s_label
{
    t_vec2i pos;
    bool is_hover;
    bool is_down;
    mlx_color color;
} t_label;


void tex_button_draw(t_tex_button button) {
    
}

bool tex_button_update(t_tex_button button) {
    
}
