/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfraslin <sfraslin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:17:47 by sfraslin          #+#    #+#             */
/*   Updated: 2025/04/07 18:48:54 by sfraslin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_test.h"

//verifie si on touche un mur, et l'orientation dudit mur
int	touch(float px, float py, t_game *game)
{
	int	x;
	int	y;

	x = px / BLOCK;
	y = py / BLOCK;
	if (game->map[y][x] == '1')
	{
		if (game->player.x >= x && game->player.y >= y)
			return (1);
		else
			return (2);
	}
	return (0);
}

void	draw_line(t_player *player, t_game *game, float start_x, int i)
{
	float	ray_x;
	float	ray_y;
	float	cos_angle;
	float	sin_angle;
	// float	dist;
	// float	height;
	// int		start_y;
	// int		end;
	// int		color;
	// int		j;

	ray_x = player->x;
	ray_y = player->y;
	cos_angle = cos(start_x);
	sin_angle = sin(start_x);
	// while (!touch(ray_x, ray_y, game))
	// {
	// 	if (DEBUG)
	// 		img_pixel_put(game, ray_x, ray_y, 0xFF0000);
	// 	ray_x += cos_angle;
	// 	ray_y += sin_angle;
	// }
	improved_touch(game, i, start_x);
	// if (!DEBUG)
	// {
	// 	dist = distance(ray_x, player->x, ray_y, player->y, game);
	// 	height = (BLOCK / dist) * (WIDTH / 2);
	// 	start_y = (HEIGHT - height) / 2;
	// 	j = start_y;
	// 	end = start_y + height;
	// 	while (start_y < end)
	// 	{
	// 		// color = wall_direction(player, i, j, 1);
	// 		img_pixel_put(game, i, start_y, 0xFF0000);
	// 		start_y++;
	// 	}
	// }
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

int	get_color(t_game *game, void *img, int x, int y)
{
	int	pixel;
	int	color;

	color = 0;
	printf("x: %d ; y: %d\n", x, y);
	game->data2 = mlx_get_data_addr(img, &game->bpp2, &game->len2, &game->endian2);
	printf("game->len2: %u\n", game->len2);
	pixel = (y * game->len2) + (x * 4);
	printf("pixel = %d\n", pixel);
	if (game->endian2 == 1)
	{
		printf("1\n");
		color += game->data2[pixel + 0];
		color += game->data2[pixel + 1];
		color += game->data2[pixel + 2];
		color += game->data2[pixel + 3];
	}
	else if (game->endian2 == 0)
	{
		printf("0\n");
		color += game->data2[pixel + 3];
		printf("data2[pixel + 3]: %d ", game->data2[pixel + 3]);
		color += game->data2[pixel + 2];
		printf("data2[pixel + 2]: %d ", game->data2[pixel + 2]);
		color += game->data2[pixel + 1];
		printf("data2[pixel + 1]: %d ", game->data2[pixel + 1]);
		color += game->data2[pixel + 0];
		printf("data2[pixel + 0]: %d\n", game->data2[pixel + 0]);
	}
	return (color);
}
