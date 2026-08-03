/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboucher <private_mail>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 16:23:59 by cboucher          #+#    #+#             */
/*   Updated: 2026/08/03 14:25:41 by cboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	parsing_error(uint64_t eflag);
static void	parsing_error_map_data(uint64_t eflag);

void	error_exit(uint64_t eflag)//TODO:ajouter struct principal quel nom ?
{
	if (eflag & ERR_NO_ARG)
		printf("%s%s\n", MSG_USAGE, MSG_NO_ARG);
	parsing_error(eflag);
	parsing_error_map_data(eflag);
	if (eflag & ERR_SYS)
		printf("%s\n%s\n", MSG_ERROR, strerror(errno));
	exit(eflag);
}

static void	parsing_error(uint64_t eflag)
{
	if (eflag & MASK_ERR_PARSER)
		printf("%s\nPARSING:\n", MSG_ERROR);
	if (eflag & ERR_WRONG_PATH)
		printf("%s\n", MSG_WRONG_PATH);
	if (eflag & ERR_WRONG_INFO_START)
		printf("%s%s\n", MSG_WRONG_INFO_START_1, MSG_WRONG_INFO_START_2);
	if (eflag & ERR_MISSING_SPACE)
		printf("%s\n", MSG_MISSING_SPACE);
	if (eflag & ERR_DUPLICATE_INFO)
		printf("%s\n", MSG_DUPLICATE_INFO);
	if (eflag & ERR_NO_RGB_FLOOR)
		printf("%s\n", MSG_NO_RGB_FLOOR);
	if (eflag & ERR_NO_RGB_CEILING)
		printf("%s\n", MSG_NO_RGB_CEILING);
	if (eflag & ERR_NOT_RGB8)
		printf("%s\n", MSG_NOT_RGB8);
}

static void	parsing_error_map_data(uint64_t eflag)
{
	if (eflag & ERR_EMPTY_LINE)
		printf("%s\n", MSG_EMPTY_LINE);
	if (eflag & ERR_MAP_OVERFLOW)
		printf("%s%d%s\n", MSG_MAP_OVERFLOW_1, MAP_SIZE_MAX_VALS, MSG_MAP_OVERFLOW_2);
	if (eflag & ERR_OPEN_MAP)
		printf("%s\n", MSG_OPEN_MAP);
	if (eflag & ERR_INVALID_C)
		printf("%s\n", MSG_INVALID_C);
}
