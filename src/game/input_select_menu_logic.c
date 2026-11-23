/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_select_menu_logic.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 17:10:01 by yben-dje          #+#    #+#             */
/*   Updated: 2026/11/23 17:10:28 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	create_slots(t_app *app)
{
	app->input_select_menu.card_slots[0] = card_slot_create((t_vec2i){-200,
			-300}, (t_vec2i){192, 192}, 0);
	app->input_select_menu.card_slots[1] = card_slot_create((t_vec2i){200,
			-300}, (t_vec2i){192, 192}, 1);
	app->input_select_menu.card_slots[2] = card_slot_create((t_vec2i){-600,
			-300}, (t_vec2i){192, 192}, 2);
	app->input_select_menu.card_slots[3] = card_slot_create((t_vec2i){600,
			-300}, (t_vec2i){192, 192}, 3);
	app->input_select_menu.docked_cards_count = 0;
	if (app->input_handler.player_count < 2)
		app->input_select_menu.card_slots[1].hide = true;
	if (app->input_handler.player_count < 3)
		app->input_select_menu.card_slots[2].hide = true;
	if (app->input_handler.player_count < 4)
		app->input_select_menu.card_slots[3].hide = true;
}

static void	set_card_image(t_app *app, t_grab_card *card)
{
	if (app->input_handler.devices[card->device_id].type == device_controller)
		card->default_image = app->image_atlas.images[16];
	if (app->input_handler.devices[card->device_id].type
		== device_keyboard_and_mouse)
		card->default_image = app->image_atlas.images[17];
	if (app->input_handler.devices[card->device_id].type == device_keyboard)
		card->default_image = app->image_atlas.images[18];
}

void	init_input_select_menu(t_app *app)
{
	int							i;
	unsigned int				devices_count;

	i = 0;
	devices_count = 2 + app->input_handler.controller_count;
	while (i < 2 + (int)app->input_handler.controller_count)
	{
		app->input_select_menu.cards[i]
			= grab_card_create((t_vec2f){(0 - (int)devices_count) * 100
				+ 192 / 2 + 200 * i + (200 - 192) / 2, 0}, (t_vec2i){192,
				192}, i);
		set_card_image(app, &app->input_select_menu.cards[i]);
		app->input_select_menu.cards[i].hide = false;
		i++;
	}
	create_slots(app);
	app->input_select_menu.valid_button = tex_button_create((t_vec2i){0, 250},
			(t_vec2i){485, 202}, app->image_atlas.images[20],
			app->image_atlas.images[21]);
	app->input_select_menu.valid_button.hide = true;
}

static void	update_cards(t_app *app)
{
	unsigned int	i;
	t_card_slot		slot;

	i = 0;
	while (i < 4)
	{
		slot = app->input_select_menu.card_slots[i];
		if (!slot.hide)
			draw_image_strech(app->frame_buffer.buffer, (t_vec2i){slot.pos.x
				+ 1, slot.pos.y - 4}, (t_vec2i){342, 320},
				app->image_atlas.images[19]);
		i++;
	}
	i = 0;
	while (i < 2 + app->input_handler.controller_count)
	{
		if (!app->input_select_menu.cards[i].hide)
			grab_card_update(app, &app->input_select_menu.cards[i],
				app->input_select_menu.card_slots, app->time.delta);
		i++;
	}
}

void	input_select_menu_window_update(t_app *app)
{
	app->time.now = get_time();
	app->time.delta = app->time.now - app->time.last;
	if (app->time.last == 0.)
		app->time.last = app->time.now;
	clear_frame_buffer(app, (mlx_color){.rgba = 0x305050FF});
	update_cards(app);
	app->input_select_menu.valid_button.hide
		= !(app->input_select_menu.docked_cards_count
			== app->input_handler.player_count);
	app->input_select_menu.cards[1].hide
		= app->input_select_menu.cards[0].docked_slot_index >= 0;
	app->input_select_menu.cards[0].hide
		= app->input_select_menu.cards[1].docked_slot_index >= 0;
	if (tex_button_update(app, app->input_select_menu.valid_button))
		start_game(app);
	push_buffer_to_screen_image(app, 0);
	push_frame_buffer_to_screen(app);
	app->time.last = app->time.now;
}
