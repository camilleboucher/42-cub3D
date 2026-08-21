/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboucher <private_mail>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 14:21:39 by cboucher          #+#    #+#             */
/*   Updated: 2026/08/21 18:58:18 by aiga             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef enum e_step
{
	GET_INFOS,
	SKIP_NEW_LINES,
	GET_MAP
}	t_step;

// parser.c
void	parsing(int fd, t_game *game, t_step step);

// parser_utils.c
char	*skip_spaces(char *s);
bool	is_rgb8(char *s);

// element_infos.c
bool	get_info(t_map *map, char *s, t_error *error);

// map_parser.c
void	parsing_map(t_game *game, t_map *map, t_list *map_head, t_error error);

// element_map.c
t_error	save_first_line(char *s, char *cell);
t_error	save_line(char *s, char *cell, t_game *game, t_map *map);

#endif
