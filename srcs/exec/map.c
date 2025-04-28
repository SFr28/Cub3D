/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sovincen <sovincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:06:02 by sovincen          #+#    #+#             */
/*   Updated: 2025/04/23 14:35:56 by sovincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	draw_map(t_game *game)
{
	char	**map;
	int		x;
	int		y;

	map = game->map;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				draw_square(x * BLOCK_MAP,
					(game->height_map - 1 - y) * BLOCK_MAP, GREY, game);
			x++;
		}
		y++;
	}
}

void	draw_square(int x, int y, int color, t_game *game)
{
	int	i;
	int	j;

	i = 0;
	x += 10;
	y = game->h - y - 40;
	while (i < BLOCK_MAP)
	{	
		j = 0;
		while (j < BLOCK_MAP)
		{
			img_pixel_put(game, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	draw_player(int x, int y, int color, t_game *game)
{
	int	i;
	int	j;
	int	p_x;
	int	p_y;

	i = -3;
	p_x = x * BLOCK_MAP + 10 + BLOCK_MAP / 2;
	p_y = game->h - ((game->height_map - 1 - y) * BLOCK_MAP)
		- 40 + BLOCK_MAP / 2;
	while (i < 3)
	{
		j = -3;
		while (j < 3)
		{
			if (!(i == -3 && j == -3) && !(i == 2 && j == 2)
				&& !(i == -3 && j == 2) && !(i == 2 && j == -3))
				img_pixel_put(game, p_x + i, p_y + j, color);
			j++;
		}
		i++;
	}
}
