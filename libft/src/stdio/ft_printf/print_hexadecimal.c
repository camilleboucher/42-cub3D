/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hexadecimal.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Camille <private_mail>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 09:52:35 by Camille           #+#    #+#             */
/*   Updated: 2025/11/11 11:07:14 by Camille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdio.h"

int	print_hexadecimal_lowercase(va_list args, int fd)
{
	return (ft_putnbr_base_ui_fd(va_arg(args, unsigned int), "0123456789abcdef",
			16, fd));
}

int	print_hexadecimal_uppercase(va_list args, int fd)
{
	return (ft_putnbr_base_ui_fd(va_arg(args, unsigned int), "0123456789ABCDEF",
			16, fd));
}
