/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboucher <private_mail>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 14:10:04 by cboucher          #+#    #+#             */
/*   Updated: 2026/10/28 18:20:11 by cboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
#define GAME_H

typedef struct s_door
{
	int		cell;
	bool	opening;
	double	progress;
}	t_door;

typedef struct s_objects
{
	int		nb_doors;
	t_door	*door;
}	t_objects;

//objects.c
bool	create_objects(t_app *app);

//game.c
void	main_loop(t_app *app);

#endif
