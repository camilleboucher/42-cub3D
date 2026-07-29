/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Camille <private_mail>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 10:54:33 by Camille           #+#    #+#             */
/*   Updated: 2025/10/30 11:22:54 by Camille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "strutils.h"
#include "ft_string.h"
#include "ft_stdlib.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	size;
	char	*sub_s;

	if (!s)
		return (NULL);
	size = ft_strlen(s);
	if (start > size)
	{
		sub_s = ft_calloc(1, 1);
		return (sub_s);
	}
	size -= start;
	if (len < size)
		size = len;
	sub_s = malloc(sizeof(char) * (size + 1));
	if (!sub_s)
		return (NULL);
	sub_s = ft_memcpy(sub_s, s + start, size);
	sub_s[size] = '\0';
	return (sub_s);
}
