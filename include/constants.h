/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboucher <private_mail>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 16:03:01 by cboucher          #+#    #+#             */
/*   Updated: 2026/10/07 14:20:19 by cboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

// MAP's CONSTANTS :
// =================
# define MAP_SIZE_MAX_VALS 256

# define C_VOID ' '
# define C_FLOOR '0'
# define C_WALL '1'
# define C_DOOR '2'

# define ID_VOID 0
# define ID_WALL 1
# define ID_FLOOR 2
# define ID_DOOR_CLOSED 3
# define ID_DOOR_ALMOST_CLOSED 4
# define ID_DOOR_ALMOST_OPENED 5
# define ID_DOOR_OPENED 6

# define PLAYER_MAX_SPEED 4.
# define PLAYER_SPEED_DECREASE 8.
# define PLAYER_FORCE 15.
# define PLAYER_BOX .1

# define DOOR_SPEED 2

#endif
