/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboucher <private_mail>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 14:11:08 by cboucher          #+#    #+#             */
/*   Updated: 2026/10/07 14:11:12 by cboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_H
#define RAYCASTER_H

typedef struct s_raycaster {
    t_vec2f camera_pos;
    double  camera_rot;
    t_vec2f camera_dir;
} t_raycaster;

void draw_raycast(t_app *app, t_raycaster *raycaster);

#endif
