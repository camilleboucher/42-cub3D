#ifndef UI_H
#define UI_H

#include "vector.h"
typedef struct s_tex_button
{
    t_vec2i pos;
    t_vec2i size;
    bool is_hover;
    bool is_down;
    t_region *default_image;
    t_region *hover_image;
} t_tex_button;

typedef struct s_label
{
    t_vec2i pos;
    bool is_hover;
    bool is_down;
    mlx_color color;
} t_label;

typedef struct s_main_menu
{
    t_tex_button play_button;
} t_main_menu;

typedef struct s_minimap {
    t_vec2i size;
    t_vec2i pos;
    bool showed;
} t_minimap;

bool tex_button_update(t_app *app, t_tex_button button);
t_tex_button tex_button_create(t_vec2i pos, t_vec2i size, t_region *default_image, t_region *hover_image);
void draw_image_strech(t_region *buffer, t_vec2i pos, t_vec2i size, t_region *image);
void render_minimap(t_app *app);

#endif