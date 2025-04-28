/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sovincen <sovincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:26:28 by sfraslin          #+#    #+#             */
/*   Updated: 2025/04/21 16:20:16 by sovincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	main(int argc, char *argv[])
{
	t_game	game;
	int		i;

	i = 0;
	parse_gameinfo(argc, argv, &game);
	init_game(&game);
	set_hooks(&game);
	mlx_loop_hook(game.mlx_ptr, draw_loop, &game);
	mlx_loop(game.mlx_ptr);
	clean_game(&game);
	return (0);
}
