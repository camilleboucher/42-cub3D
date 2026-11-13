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

int	get_door_id(int cell, int nb_doors, t_app *app)
{
	while (nb_doors)
	{
		nb_doors--;
		if (app->objects.door[nb_doors].cell == cell)
			return (nb_doors);
	}
	return (-1);
}

void	update_doors(t_app *app, t_door *door, int nb_doors)
{
	double	progress;

	progress = app->time.delta / DOOR_SPEED;
	while (nb_doors)
	{
		nb_doors--;
		if (door[nb_doors].progress <= 1 && door[nb_doors].opening)
		{
			door[nb_doors].progress += progress;
			if (door[nb_doors].progress > 1)
				door[nb_doors].progress = 1;
			app->map.cell[door[nb_doors].cell] = door[nb_doors].progress * 3
				+ 3;
		}
		else if (door[nb_doors].progress >= 0 && !door[nb_doors].opening)
		{
			door[nb_doors].progress -= progress;
			if (door[nb_doors].progress < 0)
				door[nb_doors].progress = 0;
			app->map.cell[door[nb_doors].cell] = door[nb_doors].progress * 3
				+ 3;
		}
	}
}
