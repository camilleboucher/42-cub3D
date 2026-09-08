#include <mlx_keycodes.h>
#include "player.h"
#include <math.h>
#include "input_handler.h"
#include "vector.h"

#define PLAYER_MAX_SPEED 2.
#define PLAYER_SPEED_DECREASE 6.
#define PLAYER_FORCE 6.

void player_input(t_player *player, t_input_handler *input_handler, double delta_time) {
    player->forward.x = cos(player->angle);
    player->forward.y = sin(player->angle);

    player->right.x = -sin(player->angle);
    player->right.y = cos(player->angle);
    t_vec2f move = {0., 0.};
    if (is_key_down(input_handler, MLX_KEY_W)) {
        move = vec2f_add(move, player->forward);
    }
    if (is_key_down(input_handler, MLX_KEY_S)) {
        move = vec2f_sub(move, player->forward);
    }
    if (is_key_down(input_handler, MLX_KEY_A)) {
        move = vec2f_sub(move, player->right);
    }
    if (is_key_down(input_handler, MLX_KEY_D)) {
         move = vec2f_add(move, player->right);
    }
    move = vec2f_mul(vec2f_normalize(move), PLAYER_FORCE);
    player->speed = vec2f_add(player->speed, vec2f_mul(move, delta_time));

    //printf("1Speed: %f - %f\n", player->speed.x, player->speed.y);

    if (vec2f_lenght(player->speed) > PLAYER_MAX_SPEED)
        player->speed = vec2f_mul(vec2f_normalize(player->speed), PLAYER_MAX_SPEED);
    
    
    if (vec2f_lenght(move) < 1e-6) {
        if (vec2f_lenght(player->speed) > 0.)
        {
            t_vec2f invert_friction = vec2f_mul(vec2f_normalize(player->speed), PLAYER_SPEED_DECREASE * delta_time);
            if (vec2f_lenght(invert_friction) > vec2f_lenght(player->speed))
                player->speed = (t_vec2f){0., 0.};
            else
                player->speed = vec2f_sub(player->speed, invert_friction);
        }
    }

    //printf("2Speed: %f - %f\n", player->speed.x, player->speed.y);

    player->pos = vec2f_add(player->pos, vec2f_mul(player->speed, delta_time));

    player->angle = input_handler->total_mouse_pos.x / 200.;
    if (player->angle > M_PI)
        player->angle -= M_PI * 2.;
    if (player->angle < -M_PI)
        player->angle += M_PI * 2.;
    
}
