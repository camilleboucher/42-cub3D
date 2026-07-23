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

static void	parsing_error(uint64_t eflag);

void	error_exit(uint64_t eflag)//TODO:ajouter struct principal quel nom ?
{
	parsing_error(eflag);
	exit(eflag);
}

static void	parsing_error(uint64_t eflag)
{
	if (eflag & ERR_NO_ARG)
		printf("%s%s\n", MSG_USAGE, MSG_NO_ARG);
}
