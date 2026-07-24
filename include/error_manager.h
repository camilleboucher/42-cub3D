/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboucher <private_mail>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 16:09:17 by cboucher          #+#    #+#             */
/*   Updated: 2026/07/24 15:51:29 by cboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_MANAGER_H
# define ERROR_MANAGER_H

typedef enum e_error
{
	ERR_NONE = 0u,
	ERR_SYS = 1u << 0,
	ERR_NO_ARG = 1u << 1,
	ERR_WRONG_PATH = 1u << 2
}	t_error;

# define MASK_ERR_PARSER 0x4

# define MSG_USAGE "\x1b[38:5:213mUsage:\x1b[0m "
# define MSG_ERROR "\x1b[38:5:196mError\x1b[0m"

// USAGE ERROR MESSAGE:
# define MSG_NO_ARG "cub3D needs a path to the .cub map as the parameter."

// PARSING ERRORS MESSAGES:
# define MSG_WRONG_PATH "The specified path is not a .cub map."

void	error_exit(uint64_t eflag);//TODO:ajouter struct principal quel nom ?

#endif
