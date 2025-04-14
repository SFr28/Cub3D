/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sovincen <sovincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:52:14 by sovincen          #+#    #+#             */
/*   Updated: 2025/04/01 15:53:01 by sovincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_close(t_env *env)
{
	mlx_destroy_image(env->mlx_ptr, env->img_ptr);
	mlx_destroy_window(env->mlx_ptr, env->win_ptr);
	mlx_destroy_display(env->mlx_ptr);
	free(env->mlx_ptr);
	exit(0);
}

int key_press(int keysym, t_env *env)
{
	if (keysym == ESCAPE)
		ft_close(env);
	if (keysym == S)
		env->player.key_down = 1;
	if (keysym == W)
		env->player.key_up = 1;
	if (keysym == A)
		env->player.key_left = 1;
	if (keysym == D)
		env->player.key_right = 1;
	if (keysym == LEFT)
		env->player.left_rotate = 1;
	if (keysym == RIGHT)
		env->player.right_rotate = 1;
	return (0);
}

int key_release(int keysym, t_player *player)
{
	if (keysym == S)
		player->key_down = 0;
	if (keysym == W)
		player->key_up = 0;
	if (keysym == A)
		player->key_left = 0;
	if (keysym == D)
		player->key_right = 0;
	if (keysym == LEFT)
		player->left_rotate = 0;
	if (keysym == RIGHT)
		player->right_rotate = 0;
	return (0);
}

void	set_hooks(t_env *env)
{
	mlx_hook(env->win_ptr, 2, 1L<<0, key_press, env);
	mlx_hook(env->win_ptr, 3, 1L<<1, key_release, &env->player);
	mlx_hook(env->win_ptr, 17, 1L << 17, ft_close, env);
}
