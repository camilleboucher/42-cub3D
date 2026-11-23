/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_menu_logic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 17:10:01 by yben-dje          #+#    #+#             */
/*   Updated: 2026/11/23 17:10:28 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_main_menu(t_app *app)
{
	app->main_menu.play_button = tex_button_create((t_vec2i){0, 0},
			(t_vec2i){485, 202}, app->image_atlas.images[0],
			app->image_atlas.images[1]);
}

void	main_menu_window_update(t_app *app)
{
	clear_frame_buffer(app, (mlx_color){.rgba = 0x305050FF});
	if (tex_button_update(app, app->main_menu.play_button))
		app->game_state = player_count_select;
	push_buffer_to_screen_image(app, 0);
	push_frame_buffer_to_screen(app);
}
