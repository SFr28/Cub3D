/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils_test.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfraslin <sfraslin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:17:47 by sfraslin          #+#    #+#             */
/*   Updated: 2025/04/10 13:56:16 by sfraslin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_test.h"

int	ft_touch(t_game *game, double sides[2], int steps[2], double delta[2])
{
	int	mx;
	int	my;
	int	wall_side;

	mx = (int)game->vectors.pos_x;
	my = (int)game->vectors.pos_y;
	wall_side = 2;
	// printf("mx: %d ; my: %d\n", mx, my);
	while (game->map[mx][my] != '1')
	{
		if (sides[0] < sides[1])
		{
			sides[0] += delta[0];
			mx += steps[0];
			wall_side = 0;
		}
		else
		{
			sides[1] += delta[1];
			my += steps[1];
			wall_side = 1;	
		}
	}
	game->mx = mx;
	game->my = my;
	return (wall_side);
}

int	which_color(t_game *game, t_vector *vec, int side)
{
	int	color;

	if (side == 0)
	{
		if (vec->pos_x > game->mx)
			color = 0xFF66FF;
		else
			color = 0xFFFF00;
	}
	else
	{
		if (vec->pos_y > game->my)
			color = 0xFF3300;
		else
			color = 0xFFFF00;
	}
	// printf("COLOR: %d\n", color);
	return (color);
}

void	img_pixel_put(t_game *game, int x, int y, int color)
{
	int	pixel;

	if (!(x > 0 && x < WIDTH) || !(y > 0 && y < HEIGHT))
		return ;
	pixel = (y * game->len) + (x * 4);
	if (game->endian == 1)
	{
		game->data[pixel + 0] = (color >> 24);
		game->data[pixel + 1] = (color >> 16) & 0xFF;
		game->data[pixel + 2] = (color >> 8) & 0xFF;
		game->data[pixel + 3] = color & 0xFF;
	}
	else if (game->endian == 0)
	{
		game->data[pixel + 0] = color & 0xFF;
		game->data[pixel + 1] = (color >> 8) & 0xFF;
		game->data[pixel + 2] = (color >> 16) & 0xFF;
		game->data[pixel + 3] = (color >> 24);
	}
}

void	clear_image(t_game *game)
{
	int	y;
	int	x;
	
	y = 0;
	while (y < HEIGHT)
	{
		x = -1;
		while (x++ < WIDTH)
		img_pixel_put(game, x, y, 0);
		y++;
	}
}
