/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboucher <private_mail>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 15:22:43 by cboucher          #+#    #+#             */
/*   Updated: 2026/07/24 14:21:17 by cboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	start(char *map_path);

int	main(int argc, char *argv[])
{
	if (argc != 2)
		error_exit(ERR_NO_ARG);
	start(argv[1]);
	return (EXIT_SUCCESS);
}

static void	start(char *map_path)
{
	t_map	map;

	parsing(&map, map_path);
}

