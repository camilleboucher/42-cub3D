/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboucher <private_mail>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 16:23:59 by cboucher          #+#    #+#             */
/*   Updated: 2026/07/22 16:41:49 by cboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static	first_pool(int oflag);

void	error_exit(int oflag)//TODO:ajouter struct principal quel nom ?
{
	exit(oflag);
}

static	first_pool(int oflag)
{
	if (oflag & O)
}
