/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfraslin <sfraslin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:17:47 by sfraslin          #+#    #+#             */
/*   Updated: 2025/04/08 18:12:11 by sfraslin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_test.h"

int	wall_direction(t_player *player, int wx, int wy, int touch)
{
	if (touch == 0)
	{
		if (player->y > wy)
			return (0xFF3300);
		if (player->y <= wy)
			return (0xFFFF00);
	}
	if (touch == 1)
	{
		if (player->x <= wx)
			return (0xFF66FF);
		if (player->x > wx)
			return (0xFFFF00);
	}
	return (0);
}

// int	wall_direction(t_game *game, int wx, int wy, int touch)
// {
// 	static int	x;
// 	static int	y;
	
// 	if (touch == 2)
// 	{
// 		if (game->player.x <= wx)
// 			return (get_color(game, game->texture[0], x, y));
// 		if (game->player.x > wx)
// 			return (get_color(game, game->texture[1], x, y));
// 	}
// 	if (touch == 1)
// 	{
// 		if (game->player.y <= wy)
// 			return (get_color(game, game->texture[2], x, y));
// 		if (game->player.y < wy)
// 			return (get_color(game, game->texture[3], x, y));
// 	}
// 	return (0x000000);
// }

//calculate step_x (tab[0] = direction left/right) and
//side_x(tab[2] = distance ray has to travel to hit first 'x' side from start)
static void	step_side_x(t_player *player, float start_x, float tab[4], float d)
{
	float	px;
	int		mx;

	mx = (int)player->x / BLOCK;
	px = player->x / BLOCK;
	if (cos(start_x) < 0)
	{
		tab[0] = -1;
		tab[2] = (px - mx) * d;
	}
	else
	{
		tab[0] = 1;
		tab[2] = (mx + BLOCK - px) * d;
	}
}

//calculate step_y (tab[1] = direction up/down) and
//side_y(tab[3] = distance ray has to travel to hit first 'y' side from start)
static void	step_side_y(t_player *player, float start_x, float tab[4], float d)
{
	float	py;
	int		my;

	my = (int)player->y / BLOCK;
	py = player->y / BLOCK;
	if (sin(start_x) < 0)
	{
		tab[1] = 1;
		tab[3] = (my + BLOCK - py) * d;
	}
	else
	{
		tab[1] = -1;
		tab[3] = (py - my) * d;
	}
}

int	improved_touch(t_game *game, int i, float start_x)
{
	float	deltax;
	float	deltay;
	int		mx;
	int		my;
	int		wall_side;
	float	stepnside[4];
	float	dist;
	float	height;
	int		start_y;
	int		end;
	int		color;
	// float	angle;

	mx = (int)(game->player.x / BLOCK);
	my = (int)(game->player.y / BLOCK);
	printf("mx: %d ; my: %d\n", mx, my);
	if (cos(start_x) == 0)
		deltax = (float)MAX;
	else
		deltax = 1 / fabs(cos(start_x));
	// else
	// 	deltax = sqrt(BLOCK) / fabs(cos(start_x));
	if (sin(start_x) == 0)
		deltay = (float)MAX;
	else
		deltay = 1 / fabs(sin(start_x));
	// else
	// 	deltay = sqrt(BLOCK) / fabs(sin(start_x));
	step_side_x(&game->player, start_x, stepnside, deltax);
	step_side_y(&game->player, start_x, stepnside, deltay);
	while (game->map[my][mx] != '1')
	{
		if (stepnside[2] < stepnside[3])
		{
			stepnside[2] += deltax;
			mx += stepnside[0];
			wall_side = 0;
		}
		else
		{
			stepnside[3] += deltay;
			my += stepnside[1];
			wall_side = 1;
		}
	}
	// angle = atan2(((stepnside[3] - deltay)), ((stepnside[2] - deltax))) - game->player.angle;
	// dist = sqrt(pow((stepnside[2] - deltax), 2) + pow((stepnside[3] - deltay), 2)) * cos(angle);
	if (wall_side == 0)
		dist = (stepnside[2] - deltax) / BLOCK;
	else
		dist = (stepnside[3] - deltay) / BLOCK;
	printf("DIST: %f\n", dist);
	height = fabs(BLOCK / dist);
	printf("height: %f\n", height);
	start_y = (HEIGHT - height) / 2;
	end = start_y + height / 2;
	printf("side_x: %f ; deltax: %f\n", stepnside[2], deltax);
	printf("side_y: %f ; deltay: %f\n", stepnside[3], deltay);
	printf("start_y: %d ; end: %d ; height: %f\n", start_y, end, height);
	while (start_y < end)
	{
		color = wall_direction(&game->player, (mx * BLOCK), (my * BLOCK), wall_side);
		img_pixel_put(game, i, start_y, color);
		start_y++;
	}
	return (0);
}

// if (game->player.angle > 0 && game->player.angle < PI / 2)
// {
// 	deltax = BLOCK / cos(start_x);
// 	deltay = BLOCK / sin(start_x);
// }
// if (game->player.angle > PI / 2 && game->player.angle < PI)
// {
// 	deltax = BLOCK / (-cos(start_x));
// 	deltay = BLOCK / sin(start_x);
// }
// if (game->player.angle > PI && game->player.angle < 3 * PI / 2)
// {
// 	deltax = BLOCK / (-cos(start_x));
// 	deltay = BLOCK / (-sin(start_x));
// }
// if (game->player.angle > 3 * PI / 2 && game->player.angle < 2 * PI)
// {
// 	deltax = BLOCK / cos(start_x);
// 	deltay = BLOCK / (-sin(start_x));
// }