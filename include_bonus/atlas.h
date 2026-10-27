/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atlas.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboucher <private_mail>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 14:04:38 by cboucher          #+#    #+#             */
/*   Updated: 2026/10/07 14:36:33 by cboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ATLAS_H
#define ATLAS_H

typedef struct s_image_atlas {
    t_region *images[50];
    unsigned image_amount;
} t_image_atlas;

bool atlas_load_buttons(t_app *app);
void free_all_images(t_app *app);

#endif
