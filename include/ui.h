#ifndef UI_H
# define UI_H

typedef struct s_tex_button
{
	t_vec2i			pos;
	t_vec2i			size;
	bool			is_hover;
	bool			is_down;
	t_region		*default_image;
	t_region		*hover_image;
}					t_tex_button;

typedef struct s_grab_card
{
	t_vec2f			origin;
	t_vec2f			target;
	t_vec2f			pos;
	t_vec2i			size;
	bool			is_hover;
	bool			is_grab;
	t_region		*default_image;
	t_vec2i			mouse_rel_pos;
}					t_grab_card;

typedef struct s_card_slot
{
	t_vec2i			pos;
	t_vec2i			size;
	unsigned int	id;
}					t_card_slot;

typedef struct s_label
{
	t_vec2i			pos;
	bool			is_hover;
	bool			is_down;
	mlx_color		color;
}					t_label;

typedef struct s_main_menu
{
	t_tex_button	play_button;
}					t_main_menu;

typedef struct s_player_count_menu
{
	t_tex_button	one_button;
	t_tex_button	two_button;
	t_tex_button	three_button;
	t_tex_button	four_button;
}					t_player_count_menu;

typedef struct s_input_select_menu
{
	t_grab_card		one_card;
	t_grab_card		two_card;
	t_grab_card		three_card;
	t_grab_card		four_card;
	t_card_slot		card_slots[4];
}					t_input_select_menu;

bool				tex_button_update(t_app *app, t_tex_button button);
t_tex_button		tex_button_create(t_vec2i pos, t_vec2i size,
						t_region *default_image, t_region *hover_image);
void				draw_image_strech(t_app *app, t_vec2i pos, t_vec2i size,
						t_region *image);
void				draw_rect(t_app *app, t_vec2i pos, t_vec2i size,
						mlx_color color);

void				grab_card_update(t_app *app, t_grab_card *card,
						t_card_slot slots[4], double delta_time);
t_grab_card			grab_card_create(t_vec2f pos, t_vec2i size,
						t_region *default_image);

t_card_slot			card_slot_create(t_app *app, t_vec2i pos, t_vec2i size,
						unsigned int id);

#endif