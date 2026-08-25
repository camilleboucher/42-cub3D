#include "cube3D2.h"

void draw_rect(t_app *app, t_vec2i pos, t_vec2i size, mlx_color color)
{
    int x;
    int y;

    x = 0;
    while (x < size.x)
    {
        y = 0;
        while (y < size.y)
        {
            set_pixel(app->frame_buffer.buffer, x, y, color);
            y++;
        }
        x++;
    }
}

mlx_color blend_colors(mlx_color a, mlx_color b)
{
    mlx_color merged;

    if (a.a + b.a > 0xFF)
    {
        b.a = 0xFF - a.a;
    }
    merged.a = a.a + b.a;
    merged.r = (a.r * a.a) / 0xFF + (b.r * b.a) / 0xFF;
    merged.g = (a.g * a.a) / 0xFF + (b.g * b.a) / 0xFF;
    merged.b = (a.b * a.a) / 0xFF + (b.b * b.a) / 0xFF;
    return (merged);
}

static t_vec2i get_out_size(t_app *app, t_vec2i pos, t_vec2i size)
{
    t_vec2i out_size;

    out_size = size;
    if (pos.x + size.x > (int)app->frame_buffer.width)
        out_size.x = (int)app->frame_buffer.width - pos.x;
    if (pos.y + size.y > (int)app->frame_buffer.height)
        out_size.y = (int)app->frame_buffer.height - pos.y;
    return (out_size);
}

static t_vec2i get_start_pos(t_vec2i pos)
{
    t_vec2i start_pos;

    start_pos = (t_vec2i){0, 0};
    if (pos.x < 0)
        start_pos.x = -pos.x;
    if (pos.y < 0)
        start_pos.y = -pos.y;
    return (start_pos);
}

void draw_image_strech(t_app *app, t_vec2i pos, t_vec2i size, t_region *image)
{
    int x;
    int y;
    mlx_color color;
    t_vec2i out_size;
    t_vec2i start_pos;

    if (pos.x > (int)app->frame_buffer.buffer->width || pos.y > (int)app->frame_buffer.buffer->height || pos.x + size.x < 0 || pos.y + size.y < 0)
        return;
    out_size = get_out_size(app, pos, size);
    start_pos = get_start_pos(pos);
    x = start_pos.x;
    while (x < out_size.x)
    {
        y = start_pos.y;
        while (y < out_size.y)
        {
            color = blend_colors(get_pixel(image, image->width * x / size.x, image->height * y / size.y),
                                 get_pixel(app->frame_buffer.buffer, x + pos.x, y + pos.y));
            set_pixel(app->frame_buffer.buffer, x + pos.x, y + pos.y, color);
            y++;
        }
        x++;
    }
}

bool point_to_box_collision(t_vec2i box_pos, t_vec2i box_size, t_vec2i point_pos)
{
    return (point_pos.x > box_pos.x && point_pos.x < box_pos.x + box_size.x && point_pos.y > box_pos.y && point_pos.y < box_pos.y + box_size.y);
}

void tex_button_draw(t_app *app, t_tex_button button)
{
    if (button.is_hover)
        draw_image_strech(app, button.pos, button.size, button.hover_image);
    else
        draw_image_strech(app, button.pos, button.size, button.default_image);
}

bool tex_button_update(t_app *app, t_tex_button button)
{
    bool clicked;

    button.is_hover = point_to_box_collision(button.pos, button.size, app->input_handler.mouse_pos) 
        && get_pixel(button.default_image, app->input_handler.mouse_pos.x - button.pos.x,
            app->input_handler.mouse_pos.y - button.pos.y).a != 0;
    tex_button_draw(app, button);
    clicked = button.is_hover && app->input_handler.registered_click;
    app->input_handler.registered_click = false;
    return (clicked);
}

t_tex_button tex_button_create(t_vec2i pos, t_vec2i size, t_region *default_image, t_region *hover_image)
{
    t_tex_button button;

    button = (t_tex_button){0};
    button.is_down = false;
    button.pos = pos;
    button.size = size;
    button.default_image = default_image;
    button.hover_image = hover_image;
    return (button);
}
