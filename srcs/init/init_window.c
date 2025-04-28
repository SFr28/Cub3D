/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfraslin <sfraslin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 14:49:26 by sovincen          #+#    #+#             */
/*   Updated: 2025/04/22 17:48:27 by sfraslin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

//Initialise the game structure and a graphical environment to work with
void	init_game(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (game->mlx_ptr == NULL)
		error_exit("Connection with graphic server failed", NULL, NULL);
	mlx_get_screen_size(game->mlx_ptr, &game->w, &game->h);
	game->h -= 50;
	game->win_ptr = mlx_new_window(game->mlx_ptr, game->w, game->h, "cub3D");
	if (game->win_ptr == NULL)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
		error_exit("Failed to open a new window", NULL, NULL);
	}
	game->img_ptr = mlx_new_image(game->mlx_ptr, game->w, game->h);
	if (game->img_ptr == NULL)
	{
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
		error_exit("Failed create a new image", NULL, NULL);
	}
	game->addr = mlx_get_data_addr(game->img_ptr, &game->bpp,
			&game->line_len, &game->endian);
	open_texture(game);
}
