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

# include "cub3D.h"
//objects.c
bool	create_objects(t_app *app);
int		get_door_id(int cell, int nb_doors, t_app *app);
void	update_doors(t_app *app, t_door *door, int nb_doors);

//game.c
void	main_loop(t_app *app);

#endif
