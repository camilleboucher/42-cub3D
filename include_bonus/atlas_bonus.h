/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atlas_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboucher <private_mail>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 14:04:38 by cboucher          #+#    #+#             */
/*   Updated: 2026/10/07 14:36:33 by cboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ATLAS_BONUS_H
# define ATLAS_BONUS_H

# define TEX_0 "assets/gui/play_button.png"
# define TEX_1 "assets/gui/play_button_hover.png"
# define TEX_2 "assets/stone.png"
# define TEX_7 "assets/gui/one.png"
# define TEX_8 "assets/gui/two.png"
# define TEX_9 "assets/gui/three.png"
# define TEX_10 "assets/gui/four.png"
# define TEX_11 "assets/gui/one_hover.png"
# define TEX_12 "assets/gui/two_hover.png"
# define TEX_13 "assets/gui/three_hover.png"
# define TEX_14 "assets/gui/four_hover.png"
# define TEX_15 "assets/gui/how_many_players_sign.png"
# define TEX_16 "assets/gui/controler.png"
# define TEX_17 "assets/gui/keyboard_mouse.png"
# define TEX_18 "assets/gui/keyboard.png"
# define TEX_19 "assets/gui/input_slot.png"
# define TEX_20 "assets/gui/ok.png"
# define TEX_21 "assets/gui/ok_hover.png"
# define TEX_22 "assets/anim/maomao.png"
# define TEX_23 "assets/door_closed.png"
# define TEX_24 "assets/door_almost_closed.png"
# define TEX_25 "assets/door_almost_opened.png"
# define TEX_26 "assets/door_opened.png"
# define TEX_27 "assets/map/indicator_east.png"
# define TEX_28 "assets/map/indicator_west.png"
# define TEX_29 "assets/map/indicator_south.png"
# define TEX_30 "assets/map/indicator_north.png"
# define TEX_31 "assets/map/frame.png"
# define TEX_32 "assets/map/minimap_wall.png"
# define TEX_33 "assets/map/minimap_door.png"
# define TEX_34 "assets/map/minimap_door2.png"
# define TEX_35 "assets/map/minimap_door3.png"
# define TEX_36 "assets/map/minimap_door4.png"
# define TEX_37 "assets/player/mao_mao-s.png"
# define TEX_38 "assets/player/jinshi-s.png"
# define TEX_39 "assets/player/gaoshun-s.png"
# define TEX_40 "assets/player/xiaolan-s.png"

bool	atlas_load_buttons(t_app *app);
void	free_all_images(t_app *app);

#endif
