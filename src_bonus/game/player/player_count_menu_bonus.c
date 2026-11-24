/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_count_menu_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 17:10:01 by yben-dje          #+#    #+#             */
/*   Updated: 2026/11/23 17:10:28 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static void	choose_player_count(t_app *app, unsigned int player_count)
{
	app->input_handler.player_count = player_count;
	app->game_state = input_select;
	init_input_select_menu(app);
}

void	player_count_menu_window_update(t_app *app)
{
	clear_frame_buffer(app, (mlx_color){.rgba = 0x305050FF});
	draw_image_strech(app->frame_buffer.buffer, (t_vec2i){0, -200},
		(t_vec2i){619, 311}, app->image_atlas.images[15]);
	if (tex_button_update(app, app->player_count_menu.one_button))
		choose_player_count(app, 1);
	if (tex_button_update(app, app->player_count_menu.two_button))
		choose_player_count(app, 2);
	if (tex_button_update(app, app->player_count_menu.three_button))
		choose_player_count(app, 3);
	if (tex_button_update(app, app->player_count_menu.four_button))
		choose_player_count(app, 4);
	push_buffer_to_screen_image(app, 0);
	push_frame_buffer_to_screen(app);
}

void	init_player_count_menu(t_app *app)
{
	app->player_count_menu.one_button = tex_button_create((t_vec2i){-150, 50},
			(t_vec2i){260, 200}, app->image_atlas.images[7],
			app->image_atlas.images[11]);
	app->player_count_menu.two_button = tex_button_create((t_vec2i){150, 50},
			(t_vec2i){260, 200}, app->image_atlas.images[8],
			app->image_atlas.images[12]);
	app->player_count_menu.three_button = tex_button_create((t_vec2i){-150,
			300}, (t_vec2i){260, 200}, app->image_atlas.images[9],
			app->image_atlas.images[13]);
	app->player_count_menu.four_button = tex_button_create((t_vec2i){150, 300},
			(t_vec2i){260, 200}, app->image_atlas.images[10],
			app->image_atlas.images[14]);
}
