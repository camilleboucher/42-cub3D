#include "cube3D2.h"

void	draw_rect(t_app *app, t_vec2i pos, t_vec2i size, mlx_color color)
{
	int	x;
	int	y;

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

mlx_color	blend_colors(mlx_color a, mlx_color b)
{
	mlx_color	merged;

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

static t_vec2i	get_out_size(t_app *app, t_vec2i pos, t_vec2i size)
{
	t_vec2i	out_size;

	out_size = size;
	if (pos.x + size.x > (int)app->frame_buffer.width)
		out_size.x = (int)app->frame_buffer.width - pos.x;
	if (pos.y + size.y > (int)app->frame_buffer.height)
		out_size.y = (int)app->frame_buffer.height - pos.y;
	return (out_size);
}

static t_vec2i	get_start_pos(t_vec2i pos)
{
	t_vec2i	start_pos;

	start_pos = (t_vec2i){0, 0};
	if (pos.x < 0)
		start_pos.x = -pos.x;
	if (pos.y < 0)
		start_pos.y = -pos.y;
	return (start_pos);
}

void	draw_image_strech(t_app *app, t_vec2i pos, t_vec2i size,
		t_region *image)
{
	int			x;
	int			y;
	mlx_color	color;
	t_vec2i		out_size;
	t_vec2i		start_pos;

	pos.x += ((int)app->frame_buffer.width - (int)size.x) / 2;
	pos.y += ((int)app->frame_buffer.height - (int)size.y) / 2;
	if (pos.x > (int)app->frame_buffer.buffer->width
		|| pos.y > (int)app->frame_buffer.buffer->height || pos.x + size.x < 0
		|| pos.y + size.y < 0)
		return ;
	out_size = get_out_size(app, pos, size);
	start_pos = get_start_pos(pos);
	x = start_pos.x;
	while (x < out_size.x)
	{
		y = start_pos.y;
		while (y < out_size.y)
		{
			color = blend_colors(get_pixel(image, image->width * x / size.x,
						image->height * y / size.y),
					get_pixel(app->frame_buffer.buffer, x + pos.x, y + pos.y));
			set_pixel(app->frame_buffer.buffer, x + pos.x, y + pos.y, color);
			y++;
		}
		x++;
	}
}

bool	point_to_box_collision(t_app *app, t_vec2i box_pos, t_vec2i box_size,
		t_vec2i point_pos)
{
	point_pos.x -= (app->frame_buffer.width - box_size.x) / 2;
	point_pos.y -= (app->frame_buffer.height - box_size.y) / 2;
	return (point_pos.x > box_pos.x && point_pos.x < box_pos.x + box_size.x
		&& point_pos.y > box_pos.y && point_pos.y < box_pos.y + box_size.y);
}

bool	box_to_box_collision(t_vec2i pos1, t_vec2i size1, t_vec2i pos2,
		t_vec2i size2)
{
	return (pos1.x + size1.x >= pos2.x && pos1.x <= pos2.x + size2.x && pos1.y
		+ size1.y >= pos2.y && pos1.y <= pos2.y + size2.y);
}

void	tex_button_draw(t_app *app, t_tex_button button)
{
	if (button.is_hover)
		draw_image_strech(app, button.pos, button.size, button.hover_image);
	else
		draw_image_strech(app, button.pos, button.size, button.default_image);
}

bool	mouse_perfect_collision(t_app *app, t_vec2i pos, t_vec2i size,
		t_region *image)
{
	mlx_color	pixel;

	if (!point_to_box_collision(app, pos, size, app->input_handler.mouse_pos))
		return (false);
	pixel = get_pixel(image, (app->input_handler.mouse_pos.x - pos.x
				- (int)app->frame_buffer.width / 2) * (int)image->width / size.x
			+ (int)image->width / 2, (app->input_handler.mouse_pos.y - pos.y
				- ((int)app->frame_buffer.height) / 2) * (int)image->height
			/ size.y + (int)image->height / 2);
	if (pixel.a != 0)
		return (true);
	return (false);
}

bool	tex_button_update(t_app *app, t_tex_button button)
{
	bool	clicked;

	button.is_hover = mouse_perfect_collision(app, button.pos, button.size,
			button.default_image);
	tex_button_draw(app, button);
	clicked = button.is_hover && app->input_handler.registered_click
		&& !app->input_handler.mouse_is_busy;
	if (clicked)
		app->input_handler.registered_click = false;
	return (clicked);
}

// Supports up to 4 slots. I don't care, it'll be used only one time.
void	grab_card_update(t_app *app, t_grab_card *card, t_card_slot slots[4],
		double delta_time)
{
	bool			clicked;
	t_vec2i			pos;
		t_vec2f home_vector;
	unsigned int	i;
	bool			in_slot;

	pos = (t_vec2i){card->pos.x, card->pos.y};
	card->is_hover = mouse_perfect_collision(app, pos, card->size,
			card->default_image);
	draw_image_strech(app, pos, card->size, card->default_image);
	if (!app->input_handler.mouse_is_busy && !card->is_grab && card->is_hover
		&& app->input_handler.mouse_down)
	{
		app->input_handler.mouse_is_busy = true;
		card->is_grab = true;
		card->mouse_rel_pos.x = app->input_handler.mouse_pos.x - card->pos.x;
		card->mouse_rel_pos.y = app->input_handler.mouse_pos.y - card->pos.y;
		app->input_handler.registered_click = false;
		device_notify(app, card->device_id);
	}
	if (!app->input_handler.mouse_down)
	{
		app->input_handler.mouse_is_busy = false;
		card->is_grab = false;
	}
	if (card->is_grab)
	{
		card->pos.x = app->input_handler.mouse_pos.x - card->mouse_rel_pos.x;
		card->pos.y = app->input_handler.mouse_pos.y - card->mouse_rel_pos.y;
	}
	else
	{
		home_vector = vec2f_mul(vec2f_normalize(vec2f_sub(card->target,
						card->pos)), 1500 * delta_time);
		if (vec2f_lenght(home_vector) > vec2f_dist(card->target, card->pos))
			home_vector = vec2f_sub(card->target, card->pos);
		card->pos = vec2f_add(card->pos, home_vector);
	}
	i = 0;
	in_slot = false;
	while (i++ < 4)
	{
		if (!slots[i - 1].hide && box_to_box_collision(slots[i - 1].pos, slots[i
				- 1].size, (t_vec2i){card->pos.x, card->pos.y}, card->size))
		{
			card->target = (t_vec2f){slots[i - 1].pos.x, slots[i - 1].pos.y};
			in_slot = true;
		}
	}
	if (!in_slot)
		card->target = card->origin;
}

t_tex_button	tex_button_create(t_vec2i pos, t_vec2i size,
		t_region *default_image, t_region *hover_image)
{
	t_tex_button	button;

	button = (t_tex_button){0};
	button.is_down = false;
	button.pos = pos;
	button.size = size;
	button.default_image = default_image;
	button.hover_image = hover_image;
	return (button);
}

t_grab_card	grab_card_create(t_vec2f pos, t_vec2i size, int device_id)
{
	t_grab_card	card;

	card = (t_grab_card){0};
	card.is_grab = false;
	card.pos = pos;
	card.origin = pos;
	card.target = pos;
	card.size = size;
	card.device_id = device_id;
	return (card);
}

t_card_slot	card_slot_create(t_app *app, t_vec2i pos, t_vec2i size, int id)
{
	t_card_slot	slot;

	slot.pos = pos;
	slot.size = size;
	slot.id = id;
	slot.hide = false;
	return (slot);
}
