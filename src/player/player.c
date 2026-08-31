#include <mlx_keycodes.h>
#include "player.h"
#include <math.h>
#include "input_handler.h"
#include "vector.h"

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
    move = vec2f_mul(vec2f_normalize(move), delta_time * 2);

    player->pos = vec2f_add(player->pos, move);

    player->angle = input_handler->total_mouse_pos.x / 200.;
    if (player->angle > M_PI)
        player->angle -= M_PI * 2.;
    if (player->angle < -M_PI)
        player->angle += M_PI * 2.;
}
