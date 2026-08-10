/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Camille <private_mail>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 09:52:35 by Camille           #+#    #+#             */
/*   Updated: 2025/11/08 14:27:11 by Camille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdio.h"

int	print_string(va_list args, int fd)
{
	int		size;
	char	*str;

	str = va_arg(args, char *);
	if (!str)
		size = ft_putstr_fd("(null)", fd);
	else
		size = ft_putstr_fd(str, fd);
	return (size);
}
