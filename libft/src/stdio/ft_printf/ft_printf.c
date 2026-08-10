/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Camille <private_mail>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 09:52:35 by Camille           #+#    #+#             */
/*   Updated: 2025/11/11 11:01:54 by Camille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdio.h"

static void	init_params(int (**print_param)(va_list, int), int *count)
{
	unsigned char	i;

	*count = 0;
	i = 127;
	while (i)
	{
		i--;
		print_param[i] = 0;
	}
	print_param['c'] = print_char;
	print_param['s'] = print_string;
	print_param['p'] = print_pointer;
	print_param['d'] = print_decimal;
	print_param['i'] = print_decimal;
	print_param['u'] = print_unsigned_decimal;
	print_param['x'] = print_hexadecimal_lowercase;
	print_param['X'] = print_hexadecimal_uppercase;
	print_param['%'] = print_percent_sign;
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		(*print_param[127])(va_list, int);
	int		count;

	if (!format)
		return (-1);
	init_params(print_param, &count);
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			if (print_param[(unsigned char)*(format + 1)])
				count += print_param[(unsigned char)*(format + 1)](args, 1);
			else
				count += ft_putchar_fd('%', 1);
			if (!*(++format))
				break ;
		}
		else
			count += ft_putchar_fd(*format, 1);
		format++;
	}
	va_end(args);
	return (count);
}

int	ft_dprintf(int fd, const char *format, ...)
{
	va_list	args;
	int		(*print_param[127])(va_list, int);
	int		count;

	if (!format)
		return (-1);
	init_params(print_param, &count);
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			if (print_param[(unsigned char)*(format + 1)])
				count += print_param[(unsigned char)*(format + 1)](args, fd);
			else
				count += ft_putchar_fd('%', fd);
			if (!*(++format))
				break ;
		}
		else
			count += ft_putchar_fd(*format, fd);
		format++;
	}
	va_end(args);
	return (count);
}
