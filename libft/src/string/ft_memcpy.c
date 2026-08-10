/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Camille <private_mail>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 19:01:16 by Camille           #+#    #+#             */
/*   Updated: 2025/10/22 19:11:14 by Camille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	if (!dest && !src)
		return (NULL);
	while (n)
	{
		n--;
		((char *)dest)[n] = ((char *)src)[n];
	}
	return (dest);
}
