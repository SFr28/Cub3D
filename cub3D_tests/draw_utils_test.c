/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils_test.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfraslin <sfraslin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:17:47 by sfraslin          #+#    #+#             */
/*   Updated: 2025/04/14 16:04:38 by sfraslin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_test.h"

int	ft_touch(t_game *game, t_vector *vec, double delta[2])
{
	int	wall_side;

	game->mx = (int)game->vectors.pos_x;
	game->my = (int)game->vectors.pos_y;
	wall_side = 0;
	while (game->map[game->mx][game->my] != '1')
	{
		// if (DEBUG)
		// 	img_pixel_put(&game->picture, game->mx * BLOCK, game->my * BLOCK, 0xFF66FF);
		if (vec->side_x < vec->side_y)
		{
			vec->side_x += delta[0];
			game->mx += vec->step_x;
			wall_side = 0;
		}
		else
		{
			vec->side_y += delta[1];
			game->my += vec->step_y;
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
		if (vec->pos_x > game->mx) //N
			color = 0x990000;
		else
			color = 0x009900; //S
	}
	else
	{
		if (vec->pos_y > game->my)
			color = 0xFFCC00; //W
		else
			color = 0x9999FF; //E
	}
	return (color);
}

void	ft_fps(t_game *game)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	game->old_time = game->time;
	game->time = (t.tv_sec * 1000 + t.tv_usec / 1000) - game->start_time;
	game->frame_time = (game->time - game->old_time) / 1000.0;
	game->p_speed = game->frame_time * 3.0;
	game->r_speed = game->frame_time * 1.0;
}

void	set_cube_height(int *start_y, int *end, int cube_h)
{
	*start_y = (HEIGHT - cube_h ) / 2;
	if (*start_y < 0)
		*start_y = 0;
	*end = (HEIGHT + cube_h) / 2;
	if (*end > HEIGHT)
		*end = HEIGHT - 1;
}
