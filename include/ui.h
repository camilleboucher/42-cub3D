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

bool				tex_button_update(t_app *app, t_tex_button button);
t_tex_button		tex_button_create(t_vec2i pos, t_vec2i size,
						t_region *default_image, t_region *hover_image);
void				draw_image_strech(t_region *buffer, t_vec2i pos, t_vec2i size, t_region *image);
void				draw_rect(t_app *app, t_vec2i pos, t_vec2i size,
						mlx_color color);

void				grab_card_update(t_app *app, t_grab_card *card,
						t_card_slot slots[4], double delta_time);
t_grab_card			grab_card_create(t_vec2f pos, t_vec2i size, int device_id);

t_card_slot			card_slot_create(t_app *app, t_vec2i pos, t_vec2i size,
						int id);
void render_minimap(t_app *app);

#endif
