#include <stdbool.h>
#include "mlx.h"
#include "mlx_extended.h"
#include "vector.h"

typedef struct s_color_button
{
    t_vec2i pos;
    t_vec2i size;
    char *text;
    bool is_hover;
    bool is_down;
    mlx_color color;
} t_color_button;

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
    char *text;
    bool is_hover;
    bool is_down;
    mlx_color color;
} t_label;

bool color_button_update(t_color_button button) {
    
}