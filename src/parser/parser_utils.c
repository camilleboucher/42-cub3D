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

t_error	check_split_rgb8(char **strs, char *s)
{
	int	i;

	i = 0;
	if (!strs || !ft_isdigit(s[ft_strlen(s) - 1]))
		return (ERR_NOT_RGB8);
	while (strs[i])
		i++;
	if (i == 3)
		return (ERR_NONE);
	return (ERR_NOT_RGB8);
}

bool	is_rgb8(char *s)
{
	int	i;
	int	val;

	if (!s || !*s)
		return (false);
	i = 0;
	val = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (false);
		val = val * 10 + (int)(s[i] - '0');
		if (val > 255)
			return (false);
		i++;
	}
	return (true);
}
