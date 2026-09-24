/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboucher <private_mail>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 17:12:50 by cboucher          #+#    #+#             */
/*   Updated: 2026/09/24 17:27:55 by cboucher         ###   ########.fr       */
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
void	parsing(int fd, t_app *app, t_step step);

// parser_utils.c
char	*skip_spaces(char *s);
t_error	check_split_rgb8(char **rgb, char *s);
bool	is_rgb8(char *s);

// element_infos.c
bool	get_info(t_map *map, char *s, t_error *error);

// map_parser.c
void	parsing_map(t_app *game, t_map *map, t_list *map_head, t_error error);

// element_map.c
t_error	save_first_line(char *s, char *cell);
t_error	save_line(char *s, char *cell, t_app *app, t_map *map);

#endif
