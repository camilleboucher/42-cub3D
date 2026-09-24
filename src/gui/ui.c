#include "cube3D2.h"

void draw_rect(t_app *app, t_vec2i pos, t_vec2i size, mlx_color color)
{
    int x;
    int y;

    x = pos.x;
    while (x < size.x + pos.x)
    {
        y = pos.y;
        while (y < size.y + pos.y)
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

bool box_to_box_collision(t_vec2i pos1, t_vec2i size1, t_vec2i pos2, t_vec2i size2) {
    return (pos1.x + size1.x >= pos2.x && pos1.x <= pos2.x + size2.x && pos1.y + size1.y >= pos2.y && pos1.y <= pos2.y + size2.y);
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
        && get_pixel(button.default_image, (app->input_handler.mouse_pos.x - button.pos.x) * button.default_image->width / button.size.x,
            (app->input_handler.mouse_pos.y - button.pos.y) * button.default_image->height / button.size.y).a != 0;
    tex_button_draw(app, button);
    clicked = button.is_hover && app->input_handler.registered_click && !app->input_handler.mouse_is_busy;
    if (clicked)
        app->input_handler.registered_click = false;
    return (clicked);
}

// Supports up to 4 slots. I don't care, it'll be used only one time.
void grab_card_update(t_app *app, t_grab_card *card, t_card_slot slots[4], double delta_time)
{
    bool clicked;
    t_vec2i pos;

    pos = (t_vec2i){card->pos.x, card->pos.y};
    card->is_hover = point_to_box_collision(pos, card->size, app->input_handler.mouse_pos)
        && get_pixel(card->default_image, (app->input_handler.mouse_pos.x - card->pos.x) * card->default_image->width / card->size.x,
            (app->input_handler.mouse_pos.y - card->pos.y) * card->default_image->height / card->size.y).a != 0;
    draw_image_strech(app, pos, card->size, card->default_image);
    if (!app->input_handler.mouse_is_busy && !card->is_grab && card->is_hover && app->input_handler.mouse_down)
    {
        app->input_handler.mouse_is_busy = true;
        card->is_grab = true;
        card->mouse_rel_pos.x = app->input_handler.mouse_pos.x - card->pos.x;
        card->mouse_rel_pos.y = app->input_handler.mouse_pos.y - card->pos.y;
        app->input_handler.registered_click = false;
    }
    if (!app->input_handler.mouse_down)
    {
        app->input_handler.mouse_is_busy = false;
        card->is_grab = false;
    }
    if (card->is_grab) {
        card->pos.x = app->input_handler.mouse_pos.x - card->mouse_rel_pos.x;
        card->pos.y = app->input_handler.mouse_pos.y - card->mouse_rel_pos.y;
    } else {
        t_vec2f home_vector;
        home_vector = vec2f_mul(vec2f_normalize(vec2f_sub(card->target, card->pos)), 1500 * delta_time);
        if (vec2f_lenght(home_vector) > vec2f_dist(card->target, card->pos))
            home_vector = vec2f_sub(card->target, card->pos);
        card->pos = vec2f_add(card->pos, home_vector);
    }

    unsigned int i = 0;
    bool in_slot;
    in_slot = false;
    while (i++ < 4)
    {
        if (box_to_box_collision(slots[i - 1].pos, slots[i - 1].size, (t_vec2i){card->pos.x, card->pos.y}, card->size))
        {
            card->target = (t_vec2f){slots[i - 1].pos.x, slots[i - 1].pos.y};
            in_slot = true;
        }
    }
    if (!in_slot)
        card->target = card->origin;
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

t_grab_card grab_card_create(t_vec2f pos, t_vec2i size, t_region *default_image)
{
    t_grab_card card;

    card = (t_grab_card){0};
    card.is_grab = false;
    card.pos = pos;
    card.origin = pos;
    card.target = pos;
    card.size = size;
    card.default_image = default_image;
    return (card);
}

t_card_slot card_slot_create(t_app *app, t_vec2i pos, t_vec2i size, unsigned int id) {
    t_card_slot slot;

    slot.pos = pos;
    slot.size = size;
    slot.id = id;
    return (slot);
}
