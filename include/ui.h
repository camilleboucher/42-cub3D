/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboucher <private_mail>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 14:11:47 by cboucher          #+#    #+#             */
/*   Updated: 2026/10/07 14:11:48 by cboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UI_H
# define UI_H


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

bool				tex_button_update(t_app *app, t_tex_button button);
t_tex_button		tex_button_create(t_vec2i pos, t_vec2i size,
						t_region *default_image, t_region *hover_image);
void				draw_image_strech(t_app *app, t_vec2i pos, t_vec2i size,
						t_region *image);
void				draw_rect(t_app *app, t_vec2i pos, t_vec2i size,
						mlx_color color);

void				grab_card_update(t_app *app, t_grab_card *card,
						t_card_slot slots[4], double delta_time);
t_grab_card			grab_card_create(t_vec2f pos, t_vec2i size, int device_id);

t_card_slot			card_slot_create(t_app *app, t_vec2i pos, t_vec2i size,
						int id);

#endif
