/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboucher <private_mail>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 14:19:33 by cboucher          #+#    #+#             */
/*   Updated: 2026/10/07 16:08:27 by cboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

void player_input(t_player *player, t_input_handler *input_handler, double delta_time, t_map *map) {
    bool keyboard_control;
    player->forward.x = cos(player->angle);
    player->forward.y = sin(player->angle);

    player->right.x = -sin(player->angle);
    player->right.y = cos(player->angle);
    t_vec2f move = {0., 0.};
    keyboard_control = false;
    move = vec2f_add(move, vec2f_mul(player->forward, -get_controler_left_vector(input_handler, 0).y));
    move = vec2f_add(move, vec2f_mul(player->right, get_controler_left_vector(input_handler, 0).x));


    if (is_key_down(input_handler, MLX_KEY_W)) {
        move = vec2f_add(move, player->forward);
        keyboard_control = true;
    }
    if (is_key_down(input_handler, MLX_KEY_S)) {
        move = vec2f_sub(move, player->forward);
        keyboard_control = true;
    }
    if (is_key_down(input_handler, MLX_KEY_A)) {
        move = vec2f_sub(move, player->right);
        keyboard_control = true;
    }
    if (is_key_down(input_handler, MLX_KEY_D)) {
        move = vec2f_add(move, player->right);
        keyboard_control = true;
    }

    if (keyboard_control || vec2f_lenght(move) > 1.)
        move = vec2f_normalize(move);
    move = vec2f_mul(move, PLAYER_FORCE);
    player->speed = vec2f_add(player->speed, vec2f_mul(move, delta_time));

    //printf("1Speed: %f - %f\n", player->speed.x, player->speed.y);

    if (vec2f_lenght(player->speed) > PLAYER_MAX_SPEED)
        player->speed = vec2f_mul(vec2f_normalize(player->speed), PLAYER_MAX_SPEED);
    
    
    if (vec2f_lenght(player->speed) > 0.)
    {
        t_vec2f invert_friction = vec2f_mul(vec2f_normalize(player->speed), PLAYER_SPEED_DECREASE * delta_time);
        if (vec2f_lenght(invert_friction) > vec2f_lenght(player->speed))
            player->speed = (t_vec2f){0., 0.};
        else
            player->speed = vec2f_sub(player->speed, invert_friction);
    }

    //printf("2Speed: %f - %f\n", player->speed.x, player->speed.y);
	check_collision();//TODO:
    player->pos = vec2f_add(player->pos, vec2f_mul(player->speed, delta_time));

    player->angle = input_handler->total_mouse_pos.x / 200.;
    if (player->angle > M_PI)
        player->angle -= M_PI * 2.;
    if (player->angle < -M_PI)
        player->angle += M_PI * 2.;
}
