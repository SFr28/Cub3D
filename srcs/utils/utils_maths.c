/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_maths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfraslin <sfraslin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 17:17:00 by sfraslin          #+#    #+#             */
/*   Updated: 2025/04/03 17:29:42 by sfraslin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_str_to_bi(char color[4])
{
	int	binary;
	int	i;

	i = 0;
	binary = 0;
	while (i < 5)
	{
		binary *= 10;
		binary += color[i] - 48;
		i++;
	}
	return (binary);
}

float	distance(int ray_x, int ray_y, t_game *game)
{
	float	delta_x;
	float	delta_y;
	float	angle;
	float	distance;

	delta_x = ray_x - game->player.x;
	delta_y = ray_y - game->player.y;
	angle = atan2(delta_y, delta_x) - game->player.angle;
	distance = sqrt(pow(delta_x, 2) + pow(delta_y, 2)) * cos(angle);
	return (distance);
}

bool	touch(float px, float py, t_game *game)
{
	int	x;
	int	y;

	x = px / BLOCK;
	y = py / BLOCK;
	if (game->map[y][x] == '1')
		return (true);
	return (false);
}
