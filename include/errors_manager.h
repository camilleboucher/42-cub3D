/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_manager.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboucher <private_mail>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 16:09:17 by cboucher          #+#    #+#             */
/*   Updated: 2026/07/22 16:39:04 by cboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_MANAGER_H
# define ERRORS_MANAGER_H

# define O_BAD_ARGS 2
# define USAGE_MSG1 "\x1b[38:5:196mUsage:\x1b[0m cub3D needs a path "
# define USAGE_MSG2 "to the .cub map as the parameter\n"

void	error_exit(int oflag);//TODO:ajouter struct principal quel nom ?

#endif
