/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboucher <private_mail>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 14:25:17 by cboucher          #+#    #+#             */
/*   Updated: 2026/10/07 14:30:40 by cboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double	get_time(void)
{
	struct timeval tv;
    struct timezone tz;

    gettimeofday(&tv,&tz);

	return ((double)tv.tv_sec + (double)tv.tv_usec / 1000000.);
}
