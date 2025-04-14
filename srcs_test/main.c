/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sovincen <sovincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:26:28 by sfraslin          #+#    #+#             */
/*   Updated: 2025/04/01 14:54:38 by sovincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	main(int argc, char *argv[])
{
	t_env	env;

	(void)argc;
	(void)argv;
	init_game(&env);
	set_hooks(&env);
	mlx_loop_hook(env.mlx_ptr, draw_loop, &env);
	mlx_loop(env.mlx_ptr);
	free(env.map);
	return (0);
}
