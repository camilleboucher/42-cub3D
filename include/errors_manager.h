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

typedef enum e_error
{
	ERR_NONE = 0u,
	ERR_SYS = 1u << 0,
	ERR_NO_ARG = 1u << 1
}	t_error;

# define MSG_USAGE "\x1b[38:5:196mUsage:\x1b[0m "
# define MSG_NO_ARG "cub3D needs a path to the .cub map as the parameter."

void	error_exit(uint64_t eflag);//TODO:ajouter struct principal quel nom ?

#endif
