/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboucher <private_mail>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 14:21:55 by cboucher          #+#    #+#             */
/*   Updated: 2026/08/21 17:38:09 by aiga             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*skip_spaces(char *s)
{
	while (ft_isspace((int)*s))
		s++;
	return (s);
}

bool	is_rgb8(char *s)
{
	int	size;

	size = ft_strlen(s);
	if (size > 3)
		return (false);
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (false);
		s++;
	}
	return (true);
}
