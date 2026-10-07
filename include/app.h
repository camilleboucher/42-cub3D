/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboucher <private_mail>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 14:05:07 by cboucher          #+#    #+#             */
/*   Updated: 2026/10/07 14:06:01 by cboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APP_H
#define APP_H

typedef enum e_game_state {
    ingame,
    main_menu,
} t_game_state;

typedef struct s_app
{
    mlx_context ctx;
    mlx_window window;
    mlx_window_create_info info;
    t_input_handler input_handler;
    t_frame_buffer frame_buffer;
    bool request_immediate_abort;
    t_image_atlas image_atlas;
    t_map map;
    t_player player;
    t_game_state game_state;
    t_main_menu main_menu;
} t_app;

bool app_init(t_app *app);

#endif
