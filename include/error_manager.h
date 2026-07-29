/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboucher <private_mail>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 16:09:17 by cboucher          #+#    #+#             */
/*   Updated: 2026/07/25 19:06:39 by aiga             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_MANAGER_H
# define ERROR_MANAGER_H

typedef enum e_error
{
	ERR_NONE = 0u,
	ERR_SYS = 1u << 0,
	ERR_NO_ARG = 1u << 1,
	ERR_WRONG_PATH = 1u << 2,
	ERR_WRONG_INFO_START = 1u << 3,
	ERR_MISSING_SPACE = 1u << 4,
	ERR_DUPLICATE_INFO = 1u << 5,
	ERR_NO_RGB_FLOOR = 1u << 6,
	ERR_NO_RGB_CEILING = 1u << 7,
	ERR_NOT_RGB8 = 1u << 8
}	t_error;

# define MASK_ERR_PARSER 0x4
# define MASK_ERR_NO_RGBS 0xC0

# define MSG_USAGE "\x1b[38:5:213mUsage:\x1b[0m "
# define MSG_ERROR "\x1b[38:5:196mError\x1b[0m"

// USAGE ERROR MESSAGE:
# define MSG_NO_ARG "cub3D needs a path to the .cub map as the parameter."

// PARSING ERRORS MESSAGES:
# define MSG_WRONG_PATH "- The specified path is not a .cub map."

# define MSG_WRONG_INFO_START_1 "- Incorrect ID encountered at a line start."
# define MSG_WRONG_INFO_START_2 " Only NO, SO, WE, EA, F and C are accepted."

# define MSG_MISSING_SPACE "- Missing space even though it was expected."

# define MSG_DUPLICATE_INFO "- A map's info is already set."

# define MSG_NO_RGB_FLOOR "- The floor's color is missing."
# define MSG_NO_RGB_CEILING "- The ceiling's color is missing."

# define MSG_NOT_RGB8 "- A color is not RGB 8 bits (0-255)."

void	error_exit(uint64_t eflag);//TODO:ajouter struct principal quel nom ?

#endif
