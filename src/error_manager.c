/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboucher <private_mail>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 16:23:59 by cboucher          #+#    #+#             */
/*   Updated: 2026/07/24 15:50:34 by cboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	parsing_error(uint64_t eflag);

void	error_exit(uint64_t eflag)//TODO:ajouter struct principal quel nom ?
{
	parsing_error(eflag);
	if (eflag & ERR_SYS)
		printf("%s\n%s\n", MSG_ERROR, strerror(errno));
	exit(eflag);
}

static void	parsing_error(uint64_t eflag)
{
	if (eflag & ERR_NO_ARG)
		printf("%s%s\n", MSG_USAGE, MSG_NO_ARG);
	if (eflag & MASK_ERR_PARSER)
		printf("%s\n", MSG_ERROR);
	if (eflag & ERR_WRONG_PATH)
		printf("%s\n", MSG_WRONG_PATH);
}
