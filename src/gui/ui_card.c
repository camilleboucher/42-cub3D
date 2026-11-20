/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_card.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 18:55:45 by yben-dje          #+#    #+#             */
/*   Updated: 2026/11/20 18:59:17 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	card_set_in_slot(t_app *app, t_grab_card *card, t_card_slot slots[4],
		int i)
{
	if (card->docked_slot_index >= 0)
	{
		slots[card->docked_slot_index].docked_card_id = -1;
		card->docked_slot_index = -1;
		app->input_select_menu.docked_cards_count--;
	}
	card->target = (t_vec2f){slots[i].pos.x, slots[i].pos.y};
	slots[i].docked_card_id = card->device_id;
	card->docked_slot_index = i;
	app->input_select_menu.docked_cards_count++;
}

bool	check_in_slot(t_app *app, t_grab_card *card, t_card_slot slots[4])
{
	int		i;
	bool	in_slot;

	i = 0;
	in_slot = false;
	while (i < 4)
	{
		if (!slots[i].hide && (slots[i].docked_card_id == -1
				|| slots[i].docked_card_id == card->device_id)
			&& box_to_box_collision(slots[i].pos, slots[i].size,
				(t_vec2i){card->pos.x, card->pos.y}, card->size))
		{
			card_set_in_slot(app, card, slots, i);
			in_slot = true;
		}
		i++;
	}
	return (in_slot);
}

void	card_handle_grab(t_app *app, t_grab_card *card)
{
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
}

void	card_move(t_app *app, t_grab_card *card, double delta_time)
{
	t_vec2f	home_vector;

	if (card->is_grab)
	{
		card->pos.x = app->input_handler.mouse_pos.x - card->mouse_rel_pos.x;
		card->pos.y = app->input_handler.mouse_pos.y - card->mouse_rel_pos.y;
	}
	else
	{
		home_vector = vec2f_mul(vec2f_normalize(vec2f_sub(card->target,
						card->pos)), 1500 * delta_time);
		if (vec2f_length(home_vector) > vec2f_dist(card->target, card->pos))
			home_vector = vec2f_sub(card->target, card->pos);
		card->pos = vec2f_add(card->pos, home_vector);
	}
}

// Supports up to 4 slots. I don't care, it'll be used only one time.
void	grab_card_update(t_app *app, t_grab_card *card, t_card_slot slots[4],
		double delta_time)
{
	t_vec2i	pos;

	if (card->hide)
		return ;
	pos = (t_vec2i){card->pos.x, card->pos.y};
	card->is_hover = mouse_perfect_collision(app, pos, card->size,
			card->default_image);
	draw_image_strech(app->frame_buffer.buffer, pos, card->size,
		card->default_image);
	card_handle_grab(app, card);
	card_move(app, card, delta_time);
	if (!check_in_slot(app, card, slots))
	{
		card->target = card->origin;
		if (card->docked_slot_index >= 0)
		{
			slots[card->docked_slot_index].docked_card_id = -1;
			card->docked_slot_index = -1;
			app->input_select_menu.docked_cards_count--;
		}
	}
}
