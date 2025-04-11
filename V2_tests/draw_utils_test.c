/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils_test.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfraslin <sfraslin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:17:47 by sfraslin          #+#    #+#             */
/*   Updated: 2025/04/11 11:34:07 by sfraslin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_test.h"

int	ft_touch(t_game *game, double sides[2], int steps[2], double delta[2])
{
	int	wall_side;

	game->mx = (int)game->vectors.pos_x;
	game->my = (int)game->vectors.pos_y;
	wall_side = 2;
	while (game->map[game->mx][game->my] != '1')
	{
		if (sides[0] < sides[1])
		{
			sides[0] += delta[0];
			game->mx += steps[0];
			wall_side = 0;
		}
		else
		{
			sides[1] += delta[1];
			game->my += steps[1];
			wall_side = 1;	
		}
	}
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

void	img_pixel_put(t_picture *img, int x, int y, int color)
{
	int	pixel;

	if (!(x > 0 && x < WIDTH) || !(y > 0 && y < HEIGHT))
		return ;
	pixel = (y * img->len) + (x * 4);
	if (img->endian == 1)
	{
		img->data[pixel + 0] = (color >> 24);
		img->data[pixel + 1] = (color >> 16) & 0xFF;
		img->data[pixel + 2] = (color >> 8) & 0xFF;
		img->data[pixel + 3] = color & 0xFF;
	}
	else if (img->endian == 0)
	{
		img->data[pixel + 0] = color & 0xFF;
		img->data[pixel + 1] = (color >> 8) & 0xFF;
		img->data[pixel + 2] = (color >> 16) & 0xFF;
		img->data[pixel + 3] = (color >> 24);
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
		img_pixel_put(&game->picture, x, y, 0);
		y++;
	}
}

void	ft_fps(t_game *game)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	game->old_time = game->time;
	game->time = (t.tv_sec * 1000 + t.tv_usec / 1000) - game->start_time;
	game->frame_time = (game->time - game->old_time) / 1000.0;
	game->p_speed = game->frame_time * 5.0;
	game->r_speed = game->frame_time * 3.0;
}
