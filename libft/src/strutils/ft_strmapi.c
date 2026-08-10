/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Camille <private_mail>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 13:47:37 by Camille           #+#    #+#             */
/*   Updated: 2025/11/01 14:18:24 by Camille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "strutils.h"
#include "ft_string.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*s2;
	size_t	i;

	if (!s || !f)
		return (NULL);
	s2 = ft_strdup(s);
	if (!s2)
		return (NULL);
	i = 0;
	while (s2[i])
	{
		s2[i] = f(i, s2[i]);
		i++;
	}
	return (s2);
}
