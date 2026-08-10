/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Camille <private_mail>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:47:27 by Camille           #+#    #+#             */
/*   Updated: 2025/10/30 17:13:31 by Camille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "strutils.h"
#include "ft_string.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	i = ft_strlen(s1);
	if (!i)
	{
		str = ft_strdup(s1);
		return (str);
	}
	while (ft_strchr(set, s1[i - 1]))
		i--;
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, i + 1);
	return (str);
}
