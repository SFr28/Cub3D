/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_image_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfraslin <sfraslin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:17:47 by sfraslin          #+#    #+#             */
/*   Updated: 2025/04/14 14:42:13 by sfraslin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_test.h"

int	draw_loop(t_game *game)
{
	t_vector	*vec;
	int			x;

	x = 0;
	vec = &game->vectors;
	clear_image(game);
	while (x < WIDTH)
	{
		// if (DEBUG)
		// {
		// 	draw_square(game->player.x, game->player.y, 15, 0x00FF00, game);
		// 	draw_map(game);
		// }
		vec->camera_x = 2 * x / (double)WIDTH - 1;
		vec->raydir_x = vec->dir_x + vec->plane_x * vec->camera_x;
		vec->raydir_y = vec->dir_y + vec->plane_y * vec->camera_x;
		draw_line(game, vec, x);
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

static void	ft_steps(t_vector *vec)
{
	if (vec->dir_x < 0)
		vec->step_x = -1;
	else
		vec->step_x = 1;
	if (vec->dir_y < 0)
		vec->step_y = -1;
	else
		vec->step_y = 1;
}

static void	ft_sides(t_vector *vec, double delta[2])
{
	int			mx;
	int			my;
	
	mx = (int)vec->pos_x;
	my = (int)vec->pos_y;
	if (vec->dir_x < 0)
		vec->side_x = (vec->pos_x - mx) * delta[0];
	else
		vec->side_x = (mx + 1.0 - vec->pos_x) * delta[0];
	if (vec->dir_y < 0)
		vec->side_y = (vec->pos_y - my) * delta[1];
	else
		vec->side_y = (my + 1.0 - vec->pos_y) * delta[1];
}

void	draw_line(t_game *game, t_vector *vec, int start_x)
{
	double		delta[2];
	double		distance;
	int			wall_side;

	if (vec->raydir_x == 0)
		delta[0] = (double)pow(10, 30);
	else
		delta[0] = fabs(1 / vec->raydir_x);
	if (vec->raydir_y == 0)
		delta[1] = (double)pow(10, 30);
	else
		delta[1] = fabs(1 / vec->raydir_y);
	ft_steps(vec);
	ft_sides(vec, delta);
	wall_side = ft_touch(game, vec, delta);
	if (wall_side == 0)
		distance = (vec->side_x - delta[0]);
	else
		distance = (vec->side_y - delta[1]);
	if (!DEBUG)
		draw_blocks(game, (int)(HEIGHT / distance), wall_side, start_x);
	else
		draw_ray(game, start_x);
}

void	draw_blocks(t_game *game, int cube_h, int side, int start_x)
{
	int	start_y;
	int	end;
	int	color;
	int	i;

	i = 0;
	set_cube_height(&start_y, &end, cube_h);
	while (i < HEIGHT)
	{
		if (i < start_y)
			img_pixel_put(&game->picture, start_x, i, game->ceiling_color);
		else if (i >= end)
			img_pixel_put(&game->picture, start_x, i, game->floor_color);
		else
		{
			color = which_color(game, &game->vectors, side);
			img_pixel_put(&game->picture, start_x, i, color);
		}
		i++;
	}
	ft_fps(game);
	move_up_down(game, &game->player, &game->vectors);
}
