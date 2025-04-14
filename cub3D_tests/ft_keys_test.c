/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keys_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfraslin <sfraslin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:17:47 by sfraslin          #+#    #+#             */
/*   Updated: 2025/04/11 14:11:48 by sfraslin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_test.h"

int	key_press(int keycode, t_player *player)
{
	if (keycode == XK_w)
		player->key_up = true;
	if (keycode == XK_s)
		player->key_down = true;
	if (keycode == XK_a)
		player->key_left = true;
	if (keycode == XK_d)
		player->key_right = true;
	if (keycode == XK_Left)
		player->left_rotate = true;
	if (keycode == XK_Right)
		player->right_rotate = true;
	return (0);
}

int	key_release(int keycode, t_player *player)
{
	if (keycode == XK_w)
		player->key_up = false;
	if (keycode == XK_s)
		player->key_down = false;
	if (keycode == XK_a)
		player->key_left = false;
	if (keycode == XK_d)
		player->key_right = false;
	if (keycode == XK_Left)
		player->left_rotate = false;
	if (keycode == XK_Right)
		player->right_rotate = false;
	return (0);
}

static void	move_left_right(t_game *game, t_player *player, t_vector *vec)
{	
	if (player->key_right)
	{
		if (game->map[(int)(vec->pos_x + vec->plane_x * game->p_speed)]
			[(int)vec->pos_y] != '1')
			vec->pos_x += vec->plane_x * game->p_speed;
		if (game->map[(int)vec->pos_x]
			[(int)(vec->pos_y + vec->plane_y * game->p_speed)] != '1')
			vec->pos_y += vec->plane_y * game->p_speed;
	}
	if (player->key_left)
	{
		if (game->map[(int)(vec->pos_x - vec->plane_x * game->p_speed)]
			[(int)vec->pos_y] != '1')
			vec->pos_x -= vec->plane_x * game->p_speed;
		if (game->map[(int)vec->pos_x]
			[(int)(vec->pos_y - vec->plane_y * game->p_speed)] != '1')
			vec->pos_y -= vec->plane_y * game->p_speed;
	}
}

void	move_up_down(t_game *game, t_player *player, t_vector *vec)
{
	rotation(game, player, vec);
	if (player->key_up)
	{
		if (game->map[(int)(vec->pos_x + vec->dir_x * game->p_speed)]
			[(int)vec->pos_y] != '1')
			vec->pos_x += vec->dir_x * game->p_speed;
		if (game->map[(int)vec->pos_x]
			[(int)(vec->pos_y + vec->dir_y * game->p_speed)] != '1')
			vec->pos_y += vec->dir_y * game->p_speed;
	}
	if (player->key_down)
	{
		if (game->map[(int)(vec->pos_x - vec->dir_x * game->p_speed)]
			[(int)vec->pos_y] != '1')
			vec->pos_x -= vec->dir_x * game->p_speed;
		if (game->map[(int)vec->pos_x]
			[(int)(vec->pos_y - vec->dir_y * game->p_speed)] != '1')
			vec->pos_y -= vec->dir_y * game->p_speed;
	}
	move_left_right(game, player, vec);
}

void	rotation(t_game *game, t_player *player, t_vector *vec)
{
	double	old_dir_x;
	double	old_plane_x;
	double	speed;

	old_dir_x = vec->dir_x;
	old_plane_x = vec->plane_x;
	speed = game->r_speed;
	if (player->right_rotate)
	{
		vec->dir_x = vec->dir_x * cos(-speed) - vec->dir_y * sin(-speed);
		vec->dir_y = old_dir_x * sin(-speed) + vec->dir_y * cos(-speed);
		vec->plane_x = vec->plane_x * cos(-speed) - vec->plane_y * sin(-speed);
		vec->plane_y = old_plane_x * sin(-speed) + vec->plane_y * cos(-speed);
	}
	if (player->left_rotate)
	{
		vec->dir_x = vec->dir_x * cos(speed) - vec->dir_y * sin(speed);
		vec->dir_y = old_dir_x * sin(speed) + vec->dir_y * cos(speed);
		vec->plane_x = vec->plane_x * cos(speed) - vec->plane_y * sin(speed);
		vec->plane_y = old_plane_x * sin(speed) + vec->plane_y * cos(speed);
	}
}
