/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboucher <private_mail>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 16:03:01 by cboucher          #+#    #+#             */
/*   Updated: 2026/08/03 14:12:31 by cboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

// MAP's CONSTANTS :
// =================
// MAP_SIZE_MAX_VALUES corresponds to the max number of values for the map
// inferior size type.
# define TYPE_MAP_SIZE uint16_t
# define MAP_SIZE_MAX_VALS 256

# define C_VOID ' '
# define C_FLOOR '0'
# define C_WALL '1'

// The minimp's size relative to the screen height
# define MINIMAP_SCREEN_FRACTION 4
# define MINIMAP_POS_SCREEN_FRACTION 4

#endif
