/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keys_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfraslin <sfraslin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:17:47 by sfraslin          #+#    #+#             */
/*   Updated: 2025/04/10 13:57:49 by sfraslin         ###   ########.fr       */
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
		if (game->map[(int)(vec->pos_x + vec->plane_x * PSPEED)]
			[(int)vec->pos_y] != '1')
			vec->pos_x += vec->plane_x * PSPEED;
		if (game->map[(int)vec->pos_x]
			[(int)(vec->pos_y + vec->plane_y * PSPEED)] != '1')
			vec->pos_y += vec->plane_y * PSPEED;
	}
	if (player->key_left)
	{
		if (game->map[(int)(vec->pos_x - vec->plane_x * PSPEED)]
			[(int)vec->pos_y] != '1')
			vec->pos_x -= vec->plane_x * PSPEED;
		if (game->map[(int)vec->pos_x]
			[(int)(vec->pos_y - vec->plane_y * PSPEED)] != '1')
			vec->pos_y -= vec->plane_y * PSPEED;
	}
}

void	move_up_down(t_game *game, t_player *player, t_vector *vec)
{
	rotation(player, vec);
	if (player->key_up)
	{
		if (game->map[(int)(vec->pos_x + vec->dir_x * PSPEED)]
			[(int)vec->pos_y] != '1')
			vec->pos_x += vec->dir_x * PSPEED;
		if (game->map[(int)vec->pos_x]
			[(int)(vec->pos_y + vec->dir_y * PSPEED)] != '1')
			vec->pos_y += vec->dir_y * PSPEED;
	}
	if (player->key_down)
	{
		if (game->map[(int)(vec->pos_x - vec->dir_x * PSPEED)]
			[(int)vec->pos_y] != '1')
			vec->pos_x -= vec->dir_x * PSPEED;
		if (game->map[(int)vec->pos_x]
			[(int)(vec->pos_y - vec->dir_y * PSPEED)] != '1')
			vec->pos_y -= vec->dir_y * PSPEED;
	}
	move_left_right(game, player, vec);
}

void	rotation(t_player *player, t_vector *vec)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = vec->dir_x;
	old_plane_x = vec->plane_x;
	if (player->right_rotate)
	{
		vec->dir_x = vec->dir_x * cos(-RSPEED) - vec->dir_y * sin(-RSPEED);
		vec->dir_y = old_dir_x * sin(-RSPEED) + vec->dir_y * cos(-RSPEED);
		vec->plane_x = vec->plane_x * cos(-RSPEED) - vec->plane_y * sin(-RSPEED);
		vec->plane_y = old_plane_x * sin(-RSPEED) + vec->plane_y * cos(-RSPEED);
	}
	if (player->left_rotate)
	{
		vec->dir_x = vec->dir_x * cos(RSPEED) - vec->dir_y * sin(RSPEED);
		vec->dir_y = old_dir_x * sin(RSPEED) + vec->dir_y * cos(RSPEED);
		vec->plane_x = vec->plane_x * cos(RSPEED) - vec->plane_y * sin(RSPEED);
		vec->plane_y = old_plane_x * sin(RSPEED) + vec->plane_y * cos(RSPEED);
	}
}
