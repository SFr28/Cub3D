/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sovincen <sovincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:55:36 by sovincen          #+#    #+#             */
/*   Updated: 2025/04/23 17:14:53 by sovincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	rotate_player(t_player *player, double angle_speed)
{
	player->cos_angle = cos(player->angle);
	player->sin_angle = sin(player->angle);
	if (player->left_rotate == 1)
		player->angle -= angle_speed;
	if (player->right_rotate == 1)
		player->angle += angle_speed;
	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * PI;
}

void	collision2(t_vect *vect, int move, double speed, t_player *player)
{
	if (move == 1)
	{
		vect->x = player->vect.x - player->cos_angle * speed;
		vect->y = player->vect.y - player->sin_angle * speed;
	}
	if (move == 2)
	{
		vect->x = player->vect.x + player->cos_angle * speed;
		vect->y = player->vect.y + player->sin_angle * speed;
	}
	if (move == 3)
	{
		vect->x = player->vect.x + player->sin_angle * speed;
		vect->y = player->vect.y - player->cos_angle * speed;
	}
	if (move == 4)
	{
		vect->x = player->vect.x - player->sin_angle * speed;
		vect->y = player->vect.y + player->cos_angle * speed;
	}
}

int	collision(t_player *player, double speed, int move, t_game *game)
{
	t_vect	vect;

	collision2(&vect, move, speed, player);
	if (touch(vect.x, vect.y, game) == TRUE)
		return (TRUE);
	if (touch(vect.x + 0.1, vect.y + 0.1, game) == TRUE)
		return (TRUE);
	if (touch(vect.x - 0.1, vect.y - 0.1, game) == TRUE)
		return (TRUE);
	if (touch(vect.x + 0.1, vect.y - 0.1, game) == TRUE)
		return (TRUE);
	if (touch(vect.x - 0.1, vect.y + 0.1, game) == TRUE)
		return (TRUE);
	return (FALSE);
}

void	move_player_ws(t_player *player, t_game *game)
{
	double		speed;

	speed = game->fps_info.p_speed + game->fps_info.p_speed * player->run;
	rotate_player(player, game->fps_info.r_speed);
	if (player->move_down == 1 && collision(player, speed, 1, game) == FALSE)
	{
		player->vect.x -= player->cos_angle * speed;
		player->vect.y -= player->sin_angle * speed;
	}
	if (player->move_up == 1 && collision(player, speed, 2, game) == FALSE)
	{
		player->vect.x += player->cos_angle * speed;
		player->vect.y += player->sin_angle * speed;
	}
	if (player->move_left == 1 && collision(player, speed, 3, game) == FALSE)
	{
		player->vect.x += player->sin_angle * speed;
		player->vect.y -= player->cos_angle * speed;
	}
	if (player->move_right == 1 && collision(player, speed, 4, game) == FALSE)
	{
		player->vect.x -= player->sin_angle * speed;
		player->vect.y += player->cos_angle * speed;
	}
}

void	ft_fps(t_game *game)
{
	struct timeval	t;
	t_fps			*fps;

	gettimeofday(&t, NULL);
	fps = &game->fps_info;
	fps->old_time = fps->time;
	fps->time = (t.tv_sec * 1000 + t.tv_usec / 1000) - fps->start_time;
	fps->frame_time = (fps->time - fps->old_time) / 1000.0;
	fps->p_speed = fps->frame_time * 0.0015;
	fps->r_speed = fps->frame_time * 0.001;
}
