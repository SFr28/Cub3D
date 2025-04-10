/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_image_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfraslin <sfraslin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:17:47 by sfraslin          #+#    #+#             */
/*   Updated: 2025/04/10 14:13:01 by sfraslin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_test.h"

int	draw_loop(t_game *game)
{
	t_vector	*vec;
	int			x;

	x = 0;
	vec = &game->vectors;
	move_up_down(game, &game->player, &game->vectors);
	clear_image(game);
	while (x < WIDTH)
	{
		vec->camera_x = 2 * x / (double)(WIDTH) - 1;
		vec->raydir_x = vec->dir_x + vec->plane_x * vec->camera_x;
		vec->raydir_y = vec->dir_y + vec->plane_y * vec->camera_x;
		draw_line(game, vec, x);
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

static void	ft_steps(int steps[2], t_vector *vec)
{
	if (vec->dir_x < 0)
		steps[0] = -1;
	else
		steps[0] = 1;
	if (vec->dir_y < 0)
		steps[1] = -1;
	else
		steps[1] = 1;
}

static void	ft_sides(double sides[2], t_vector *vec, double delta[2])
{
	int			mx;
	int			my;
	
	mx = (int)vec->pos_x;
	my = (int)vec->pos_y;
	if (vec->dir_x < 0)
		sides[0] = (vec->pos_x - mx) * delta[0];
	else
		sides[0] = (mx + 1.0 - vec->pos_x) * delta[0];
	if (vec->dir_y < 0)
		sides[1] = (vec->pos_y - my) * delta[1];
	else
		sides[1] = (my + 1.0 - vec->pos_y) * delta[1];
}

void	draw_line(t_game *game, t_vector *vec, int start_x)
{
	double		sides[2];
	double		delta[2];
	double		distance;
	int			steps[2];
	int			wall_side;

	if (vec->raydir_x == 0)
		delta[0] = (double)pow(10, 30);
	else
		delta[0] = fabs(1 / vec->raydir_x);
	// else
	// 	delta[0] = sqrt(1 + (vec->raydir_y * vec->raydir_y) / (vec->raydir_x * vec->raydir_x));
	if (vec->raydir_y == 0)
		delta[1] = (double)pow(10, 30);
	else
		delta[1] = fabs(1 / vec->raydir_y);	
	// else
	// 	delta[1] = sqrt(1 + (vec->raydir_x * vec->raydir_x) / (vec->raydir_y * vec->raydir_y));
	ft_steps(steps, vec);
	ft_sides(sides, vec, delta);
	wall_side = ft_touch(game, sides, steps, delta);
	if (wall_side == 0)
		distance = (sides[0] - delta[0]);
	else
		distance = (sides[1] - delta[1]);
	// printf("distance: %f\n", distance);
	draw_blocks(game, (int)(HEIGHT / distance), wall_side, start_x);
}

void	draw_blocks(t_game *game, int cube_h, int side, int start_x)
{
	int	start_y;
	int	end;
	int	color;

	// printf("DRAW_BLOCKS\n");
	// printf("cub_h: %d\n", cube_h);
	start_y = (HEIGHT - cube_h ) / 2;
	if (start_y < 0)
		start_y = 0;
	end = (HEIGHT + cube_h) / 2;
	if (end > HEIGHT)
		end = HEIGHT - 1;
	// printf("start_y: %d ; end: %d\n start_x: %d\n", start_y, end, start_x);
	while (start_y < end)
	{
		color = which_color(game, &game->vectors, side);
		img_pixel_put(game, start_x, start_y, color);
		start_y++;
	}
}

// ((double)recup->ray.mapy - recup->ray.posy + (1 - (double)recup->ray.stepy) / 2) / recup->ray.raydiry;
// 	recup->ray.lineheight = (int)(recup->ry / recup->ray.perpwalldist)