/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sovincen <sovincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:50:28 by sovincen          #+#    #+#             */
/*   Updated: 2025/04/14 15:56:39 by sovincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

//Initialise player position
void	init_player(t_player *player)
{
	player->vect.x = WIDHT / 2;
	player->vect.y = HEIGHT / 2;
	player->angle = (3 * M_PI) / 2;
	player->cos_angle = cos(player->angle);
	player->sin_angle = sin(player->angle);
	player->key_down = 0;
	player->key_up = 0;
	player->key_left = 0;
	player->key_right = 0;
	player->left_rotate = 0;
	player->right_rotate = 0;
}

void	init_game(t_env *env)
{
	init_player(&env->player);
	env->map = get_map();
	env->mlx_ptr = mlx_init();
	if (env->mlx_ptr == NULL)
		error_exit("Connection with graphic server failed");
	env->win_ptr = mlx_new_window(env->mlx_ptr, WIDHT, HEIGHT, "Cub3D");
	if (env->win_ptr == NULL)
	{
		mlx_destroy_display(env->mlx_ptr);
		free(env->mlx_ptr);
		error_exit("Failed to open a new window");
	}
	env->img_ptr = mlx_new_image(env->mlx_ptr, WIDHT, HEIGHT);
	if (env->img_ptr == NULL)
	{
		mlx_destroy_window(env->mlx_ptr, env->win_ptr);
		mlx_destroy_display(env->mlx_ptr);
		free(env->mlx_ptr);
		error_exit("Failed create a new image");
	}
	env->addr = mlx_get_data_addr(env->img_ptr, &env->bpp,
			&env->line_len, &env->endian);
}
