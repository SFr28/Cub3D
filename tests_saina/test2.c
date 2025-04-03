/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfraslin <sfraslin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:17:47 by sfraslin          #+#    #+#             */
/*   Updated: 2025/04/03 14:22:02 by sfraslin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_test.h"

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

void	draw_line(t_player *player, t_game *game, float start_x, int i)
{
	float	ray_x;
	float	ray_y;
	float	cos_angle;
	float	sin_angle;
	float	dist;
	float	height;
	int		start_y;
	int		end;

	ray_x = player->x;
	ray_y = player->y;
	cos_angle = cos(start_x);
	sin_angle = sin(start_x);
	while (!touch(ray_x, ray_y, game))
	{
		if (DEBUG)
			img_pixel_put(game, ray_x, ray_y, 0xFF0000);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
	if (!DEBUG)
	{
		dist = distance(ray_x, player->x, ray_y, player->y, game);
		height = (BLOCK / dist) * (WIDTH / 2);
		start_y = (HEIGHT - height) / 2;
		end = start_y + height;
		while (start_y < end)
		{
			img_pixel_put(game, i, start_y, 255);
			start_y++;
		}
	}
}

float	distance(int ray_x, int player_x, int ray_y, int player_y, t_game *game)
{
	float	delta_x;
	float	delta_y;
	float	angle;
	float	distance;

	delta_x = ray_x - player_x;
	delta_y = ray_y - player_y;
	angle = atan2(delta_y, delta_x) - game->player.angle;
	distance = sqrt(pow(delta_x, 2) + pow(delta_y, 2)) * cos(angle);
	return (distance);
}
