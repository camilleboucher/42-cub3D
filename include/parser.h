/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboucher <private_mail>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 14:21:39 by cboucher          #+#    #+#             */
/*   Updated: 2026/07/24 15:26:15 by cboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

void	parsing(t_map *map, char *path);

void	check_extension(char *path, char *ext, int ext_size);
int		open_map(char *path);

#endif
