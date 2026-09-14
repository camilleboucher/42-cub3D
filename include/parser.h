/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 14:21:39 by cboucher          #+#    #+#             */
/*   Updated: 2026/08/24 18:32:13 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "cube3D2.h"

typedef enum e_step
{
	GET_INFOS,
	SKIP_NEW_LINES,
	GET_MAP
}	t_step;

// parser.c
void	parsing(int fd, t_app *app);
char	*skip_spaces(char *s);
bool	is_rgb8(char *s);

// element_infos.c
bool	get_info(t_map *map, char *s, t_error *error);

// element_map.c
t_error	get_map_line(t_app *app, t_map *map, char *s, t_step *step);

#endif
