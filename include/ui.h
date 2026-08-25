#ifndef UI_H
#define UI_H

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


bool tex_button_update(t_app *app, t_tex_button button);
t_tex_button tex_button_create(t_vec2i pos, t_vec2i size, t_region *default_image, t_region *hover_image);

#endif