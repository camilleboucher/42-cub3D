/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Camille <private_mail>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 11:34:51 by Camille           #+#    #+#             */
/*   Updated: 2025/10/27 12:17:14 by Camille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*chr;

	chr = NULL;
	while (*s)
	{
		if (*s == (char)c)
			chr = s;
		s++;
	}
	if ((*s | (char)c) == '\0')
		chr = s;
	return ((char *)chr);
}
