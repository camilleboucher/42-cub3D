/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Camille <private_mail>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 09:52:35 by Camille           #+#    #+#             */
/*   Updated: 2025/11/10 19:06:05 by Camille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdio.h"

int	print_pointer(va_list args, int fd)
{
	size_t	address;

	address = va_arg(args, size_t);
	if (!address)
	{
		ft_putstr_fd("(nil)", fd);
		return (5);
	}
	ft_putstr_fd("0x", fd);
	return (ft_putnbr_base_ul_fd(address, "0123456789abcdef", 16, fd) + 2);
}
