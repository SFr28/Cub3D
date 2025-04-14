/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sovincen <sovincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:55:36 by sovincen          #+#    #+#             */
/*   Updated: 2025/04/14 15:06:43 by sovincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	rotate_player(t_player *player)
{
	float	angle_speed;
	
	player->cos_angle = cos(player->angle);
	player->sin_angle = sin(player->angle);
	angle_speed = 0.03;
	if (player->left_rotate == 1)
		player->angle -= angle_speed;
	if (player->right_rotate == 1)
		player->angle += angle_speed;
	if (player->angle > 2 * M_PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * M_PI;
}

void	move_player(t_player *player)
{
	int		speed;

	speed = 3; 
	rotate_player(player);
	if (player->key_down == 1)
	{
		player->vect.x -= player->cos_angle * speed;
		player->vect.y -= player->sin_angle * speed;
	}
	if (player->key_up == 1)
	{
		player->vect.x += player->cos_angle * speed;
		player->vect.y += player->sin_angle * speed;
	}
	if (player->key_left == 1)
	{
		player->vect.x += player->sin_angle * speed;
		player->vect.y -= player->cos_angle * speed;
	}
	if (player->key_right == 1)
	{
		player->vect.x -= player->sin_angle * speed;
		player->vect.y += player->cos_angle * speed;
	}
}
