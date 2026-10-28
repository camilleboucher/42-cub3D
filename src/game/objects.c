/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboucher <private_mail>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 14:15:33 by cboucher          #+#    #+#             */
/*   Updated: 2026/10/28 18:23:31 by cboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool	create_doors(t_app *app, int count_doors);

bool	create_objects(t_app *app)
{
	int	i;
	int	last_cell;
	int	count_doors;

	i = 0;
	last_cell = app->map.height * app->map.width;
	count_doors = 0;
	while (i < last_cell)
	{
		if (app->map.cell[i] == ID_DOOR_CLOSED)
			count_doors++;
		i++;
	}
	if (!create_doors(app, count_doors))
		return (false);
	return (true);
}

static bool	create_doors(t_app *app, int count_doors)
{
	int	i;
	int	door;

	app->objects.door = malloc(count_doors * sizeof(t_door));
	if (!app->objects.door)
		return (false);
	app->objects.nb_doors = count_doors;
	i = 0;
	door = 0;
	while (door < count_doors)
	{
		if (app->map.cell[i] == ID_DOOR_CLOSED)
		{
			app->objects.door[door].cell = i;
			app->objects.door[door].opening = false;
			app->objects.door[door].progress = 0;
			door++;
		}
		i++;
	}
	return (true);
}
