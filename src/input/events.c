/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 17:10:01 by yben-dje          #+#    #+#             */
/*   Updated: 2026/11/23 17:10:28 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	handle_key_down(int key, void *param)
{
	t_app	*app;

	app = param;
	input_handler_set_down(&app->input_handler, key);
	if (key == MLX_KEY_ESCAPE)
		mlx_loop_end(app->ctx);
}

void	handle_key_up(int key, void *param)
{
	t_app	*app;

	app = param;
	input_handler_set_up(&app->input_handler, key);
}
