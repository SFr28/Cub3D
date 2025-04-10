/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_V2_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfraslin <sfraslin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:17:47 by sfraslin          #+#    #+#             */
/*   Updated: 2025/04/10 13:52:31 by sfraslin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_test.h"

int	main(void)
{
	t_game	game;

	init_game(&game);
	if (!game.texture[0])
	{
		ft_close(&game);
		return (1);
	}
	mlx_hook(game.win, 2, 1L << 0, key_press, &game.player);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game.player);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_hook(game.win, 17, 1L << 17, ft_close, &game);
	mlx_loop(game.mlx);
	return (0);
}

int	ft_close(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_image(game->mlx, game->img);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free(game->map);
	exit (0);
}
