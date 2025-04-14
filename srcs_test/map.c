/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sovincen <sovincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:06:02 by sovincen          #+#    #+#             */
/*   Updated: 2025/04/09 13:24:57 by sovincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	draw_map(t_env *env)
{
	char	**map;
	int		x;
	int		y;

	map = env->map;
	y = 0;
	while (y < 10)
	{
		x = 0;
		while (x < 15)
		{
			if (map[y][x] == '1')
				draw_square(x * BLOCK, y * BLOCK, BLOCK, DARK_CYAN, env);
			x++;
		}
		y++;
	}
}
