/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Camille <private_mail>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 15:11:00 by Camille           #+#    #+#             */
/*   Updated: 2025/11/11 11:13:50 by Camille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdio.h"

int	ft_putnbr_i_fd(int n, int fd)
{
	int	count;

	count = 0;
	if (n == -2147483648)
	{
		count = ft_putstr_fd("-2147483648", fd);
		return (count);
	}
	else if (n < 0)
	{
		count += ft_putchar_fd('-', fd);
		count += ft_putnbr_i_fd(-n, fd);
		return (count);
	}
	else if (n >= 10)
		count += ft_putnbr_i_fd(n / 10, fd);
	count += ft_putchar_fd(n % 10 + '0', fd);
	return (count);
}

int	ft_putnbr_ui_fd(unsigned int n, int fd)
{
	int	count;

	count = 0;
	if (n >= 10)
		count += ft_putnbr_ui_fd(n / 10, fd);
	count += ft_putchar_fd(n % 10 + '0', fd);
	return (count);
}

int	ft_putnbr_base_ui_fd(unsigned int n, char *base,
						unsigned int base_size, int fd)
{
	int	count;

	count = 0;
	if (n >= base_size)
		count += ft_putnbr_base_ui_fd(n / base_size, base, base_size, fd);
	count += ft_putchar_fd(base[n % base_size], fd);
	return (count);
}

int	ft_putnbr_base_ul_fd(size_t n, char *base, size_t base_size, int fd)
{
	int	count;

	count = 0;
	if (n >= base_size)
		count += ft_putnbr_base_ul_fd(n / base_size, base, base_size, fd);
	count += ft_putchar_fd(base[n % base_size], fd);
	return (count);
}
