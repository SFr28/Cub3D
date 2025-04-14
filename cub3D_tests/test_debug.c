/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_debug.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfraslin <sfraslin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:17:47 by sfraslin          #+#    #+#             */
/*   Updated: 2025/04/11 14:22:48 by sfraslin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_test.h"

void	draw_square(int x, int y, int size, int color, t_game *game)
{
	int	i;

	i = -1;
	while (i++ < size)
		img_pixel_put(&game->picture, (x + i), y, color);
	i = -1;
	while (i++ < size)
		img_pixel_put(&game->picture, x, (y + i), color);
	i = -1;
	while (i++ < size)
		img_pixel_put(&game->picture, (x + size), (y + i), color);
	i = -1;
	while (i++ < size)
		img_pixel_put(&game->picture, (x + i), (y + size), color);

}

void	draw_map(t_game *game)
{
	char	**map;
	int		color;
	int		y;
	int		x;

	map = game->map;
	color = 0x0000FF;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				draw_square(x * BLOCK, y * BLOCK, BLOCK, color, game);
			x++;
		}
		y++;
	}
}

static int	ray_touch(float px, float py, t_game *game)
{
	int	x;
	int	y;

	x = (int)px / BLOCK;
	y = (int)py / BLOCK;
	if (game->map[x][y] == '1')
		return (1);
	return (0);
}

void	draw_ray(t_game *g, int start_x)
{
	t_player	tmp_p;
	float		cos_angle;
	float		sin_angle;

	tmp_p = g->player;
	cos_angle = cos(start_x);
	sin_angle = sin(start_x);
	while (!ray_touch(tmp_p.x, tmp_p.y, g))
	{
		img_pixel_put(&g->picture, g->mx, g->my, 0xFFFFFF);
		tmp_p.x += cos_angle;
		tmp_p.y += sin_angle;
	}
	ft_fps(g);
	debug_mvt(g);
}

void	debug_mvt(t_game *game)
{
	t_player	*player;
	float		cos_angle;
	float		sin_angle;

	player = &game->player;
	if (player->left_rotate)
		player->angle -= game->r_speed * 10;
	if (player->right_rotate)
		player->angle += game->r_speed * 10;
	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * PI;	
	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	if (player->key_up)
	{
		player->x += cos_angle * game->p_speed * 10;
		player->y += sin_angle * game->p_speed * 10;
	}
	if (player->key_down)
	{
		player->x -= cos_angle * game->p_speed * 10;
		player->y -= sin_angle * game->p_speed * 10;
	}
	if (player->key_left)
	{
		player->x += sin_angle * game->p_speed * 10;
		player->y -= cos_angle * game->p_speed * 10;
	}
	if (player->key_right)
	{
		player->x -= sin_angle * game->p_speed * 10;
		player->y += cos_angle * game->p_speed * 10;
	}
}
