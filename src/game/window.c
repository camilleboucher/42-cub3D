/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 17:10:01 by yben-dje          #+#    #+#             */
/*   Updated: 2026/11/23 17:10:28 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	handle_resize_event(t_app *app)
{
	int	width;
	int	height;

	mlx_get_window_size(app->ctx, app->window, &width, &height);
	if (!resize_frame_buffer(app, width, height))
		app->request_immediate_abort = true;
}

void	window_event_handle(int event, void *param)
{
	t_app	*app;

	app = param;
	if (app->request_immediate_abort)
		return ;
	if (event == 0)
	{
		mlx_loop_end(app->ctx);
	}
	else if (event == MLX_WINDOW_SIZE_CHANGED)
	{
		printf("Resized\n");
		handle_resize_event(app);
		if (app->request_immediate_abort)
			mlx_loop_end(app->ctx);
	}
}
