/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboucher <private_mail>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 17:12:31 by cboucher          #+#    #+#             */
/*   Updated: 2026/10/28 16:57:01 by cboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

// for input_device.h
typedef enum e_device_type
{
	device_controller,
	device_keyboard,
	device_keyboard_and_mouse,
}					t_device_type;

typedef struct s_input_device
{
	bool			active;
	t_vec2f			move_vector;
	double          angle;
	t_device_type	type;
    int             controller_slot;
}					t_input_device;

// for input_handler.h
typedef struct s_input_handler {
  t_vec2i mouse_pos;
  t_vec2f total_mouse_pos;
  bool registered_click;
  int keys[255];
  bool	action_key;
  t_vec2i old_mouse_pos;
  unsigned int player_count;
  unsigned int controller_count;
  t_input_device devices[6];
  bool mouse_down;
  bool mouse_is_busy;
} t_input_handler;

// for frame_buffer.h
typedef struct s_region {
  unsigned int width;
  unsigned int height;
  mlx_color buffer[];
} t_region;

typedef struct s_frame_buffer {
  t_region *buffer;
  t_region *shader_buffer;
  unsigned int width;
  unsigned int height;
  mlx_image screen_image;
  unsigned int screen_width;
  unsigned int screen_height;
} t_frame_buffer;

// for animated_sprite.h
typedef struct s_animated_sprite {
    t_region *frames;
    unsigned int frame_count;
    double frame_time;
    double timer;
    unsigned int frame_index;
    bool playing;
    unsigned int frame_width;
} t_animated_sprite;

// for atlas.h
typedef struct s_image_atlas {
    t_region *images[50];
    t_animated_sprite animated_sprite[10];
    unsigned image_amount;
} t_image_atlas;

// for player.h
typedef struct s_player
{
	t_vec2f	pos;
	double		angle;
	t_vec2f	forward;
	t_vec2f right;
	t_vec2f speed;
	int device_id;
}	t_player;

// for ui.h
typedef struct s_tex_button
{
	t_vec2i			pos;
	t_vec2i			size;
	bool			is_hover;
	bool			is_down;
	t_region		*default_image;
	t_region		*hover_image;
	bool            hide;
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
	int				device_id;
	int             docked_slot_index;
	bool            hide;
}					t_grab_card;

typedef struct s_card_slot
{
	t_vec2i			pos;
	t_vec2i			size;
	unsigned int	id;
	bool			hide;
	int             docked_card_id;
}					t_card_slot;

typedef struct s_label
{
	t_vec2i			pos;
	bool			is_hover;
	bool			is_down;
	mlx_color		color;
}					t_label;

typedef struct s_player_count_menu
{
	t_tex_button	one_button;
	t_tex_button	two_button;
	t_tex_button	three_button;
	t_tex_button	four_button;
}					t_player_count_menu;

typedef struct s_input_select_menu
{
	t_grab_card		cards[6];
	t_card_slot		card_slots[4];
	int				controler_ids[4];
	unsigned int    docked_cards_count;
	t_tex_button        valid_button;
}					t_input_select_menu;

typedef struct s_main_menu
{
	t_tex_button	play_button;
}					t_main_menu;

// for the parser
typedef enum e_direction
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
	FLOOR,
	CEILING,
	NO_DIRECTION
}	t_direction;

typedef enum e_rgb
{
	R,
	G,
	B
}	t_rgb;

typedef struct s_map
{
	char		*cell;
	uint16_t	width;
	uint16_t	height;
	char		*path_textures[4];
	uint8_t		floor_rgb[3];
	uint8_t		ceiling_rgb[3];
	mlx_color	floor_color;
	mlx_color	ceil_color;
}	t_map;

// for game.h
typedef struct s_door
{
	int		cell;
	bool	opening;
	double	progress;
}	t_door;

typedef struct s_objects
{
	int		nb_doors;
	t_door	*door;
}	t_objects;

// for app.h
typedef enum e_game_state {
    ingame,
    player_count_select,
    input_select,
    main_menu,
} t_game_state;

typedef struct s_time
{
	double	now;
	double	last;
	double	delta;
}	t_time;

typedef struct s_app
{
    mlx_context ctx;
    mlx_window window;
    mlx_window_create_info info;
    t_input_handler input_handler;
    t_frame_buffer frame_buffer;
    bool request_immediate_abort;
    t_image_atlas image_atlas;
    t_map map;
    t_player players[4];
    t_objects	objects;
    t_game_state game_state;
    t_main_menu main_menu;
    t_player_count_menu player_count_menu;
    t_input_select_menu input_select_menu;
    t_time		time;
} t_app;

#endif
