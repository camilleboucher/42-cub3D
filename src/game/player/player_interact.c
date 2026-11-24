/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_interact.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 17:10:28 by yben-dje          #+#    #+#             */
/*   Updated: 2026/11/23 17:10:28 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	check_door_activation(t_app *app, t_vec2f target, t_player *player)
{
	int	cell;

	cell = (int)target.x + (int)target.y * app->map.width;
	if (app->map.cell[cell] == ID_DOOR_CLOSED)
		app->objects.door[get_door_id(cell, app->objects.nb_doors,
				app)].opening = true;
	else if (app->map.cell[cell] == ID_DOOR_OPENED
		&& !playerbox_in_door(&app->map, player->pos))
		app->objects.door[get_door_id(cell, app->objects.nb_doors,
				app)].opening = false;
}

void	action_input(t_app *app, t_player *player)
{
	if (app->input_handler.devices[player->device_id].action_key)
		check_door_activation(app, vec2f_add(player->pos, player->forward),
			player);
}
