/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Camille <private_mail>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 14:21:24 by Camille           #+#    #+#             */
/*   Updated: 2025/11/01 15:01:44 by Camille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdio.h"
#include "ft_string.h"

int	ft_putstr_fd(char *s, int fd)
{
	size_t	size;

	if (!s)
		return (0);
	size = ft_strlen(s);
	write(fd, s, size);
	return ((int)size);
}
