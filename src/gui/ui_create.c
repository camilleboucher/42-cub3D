/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_create.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 18:19:16 by yben-dje          #+#    #+#             */
/*   Updated: 2026/11/20 18:19:16 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
	button.hide = false;
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
	card.hide = true;
	card.docked_slot_index = -1;
	return (card);
}

t_card_slot	card_slot_create(t_vec2i pos, t_vec2i size, int id)
{
	t_card_slot	slot;

	slot.pos = pos;
	slot.size = size;
	slot.id = id;
	slot.hide = false;
	slot.docked_card_id = -1;
	return (slot);
}
