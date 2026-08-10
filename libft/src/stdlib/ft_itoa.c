/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Camille <private_mail>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 16:15:36 by Camille           #+#    #+#             */
/*   Updated: 2025/10/31 16:28:46 by Camille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdlib.h"

static char	*n_to_string(char *nbr, int n, size_t size)
{
	size_t	i;

	if (!n)
		nbr[0] = '0';
	else
	{
		i = 0;
		if (n < 0)
		{
			nbr[0] = '-';
			nbr[size - i - 1] = (n % -10 * -1) + '0';
			i++;
			n = n / 10 * -1;
		}
		while (n)
		{
			nbr[size - i - 1] = n % 10 + '0';
			i++;
			n /= 10;
		}
	}
	return (nbr);
}

static size_t	find_size_nbr(int n)
{
	size_t	size;

	if (!n)
		return (1);
	size = 0;
	if (n < 0)
		size++;
	while (n)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char	*nbr;
	size_t	size;

	size = find_size_nbr(n);
	nbr = malloc(sizeof(char) * (size + 1));
	if (!nbr)
		return (NULL);
	nbr[size] = '\0';
	nbr = n_to_string(nbr, n, size);
	return (nbr);
}
