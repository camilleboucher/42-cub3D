/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboucher <private_mail>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 15:22:43 by cboucher          #+#    #+#             */
/*   Updated: 2026/07/22 16:23:25 by cboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char *argv[])
{
	if (argc != 2)
		error_exit(O_BAD_ARGS, USAGE_MSG1, USAGE_MSG2);
	return (EXIT_SUCCESS);
}
