/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboucher <private_mail>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 14:09:59 by cboucher          #+#    #+#             */
/*   Updated: 2026/10/28 18:37:04 by cboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

void input_handler_set_down(t_input_handler *handler, int key);

void input_handler_set_up(t_input_handler *handler, int key);

bool is_key_down(t_input_handler *handler, int key);

t_vec2f get_controler_left_vector(t_input_handler *handler, unsigned int controler_index);

t_vec2f get_controler_right_vector(t_input_handler *handler, unsigned int controler_index);

void input_handler_update(t_input_handler *handler, mlx_context ctx);

#endif
