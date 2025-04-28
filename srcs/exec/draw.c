/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfraslin <sfraslin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:16:53 by sovincen          #+#    #+#             */
/*   Updated: 2025/04/23 11:20:01 by sfraslin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	draw_line(t_player *player, t_camera *camera, t_game *game, int x)
{
	t_data	data;
	int		color;
	int		i;

	init_data(&data, player);
	init_raydir(camera, &data);
	find_step(camera, &data, &player->vect);
	dda_algo(&data, game);
	distance_to_wall(&data);
	walls_height(&data, game);
	i = 0;
	while (i < game->h)
	{
		if (i < data.drawstart)
			img_pixel_put(game, x, i, game->c_color);
		else if (i > data.drawend)
			img_pixel_put(game, x, i, game->f_color);
		else
		{
			color = which_color_tex(i, &data, camera, game);
			img_pixel_put(game, x, i, color);
		}
		i++;
	}
}

int	draw_loop(t_game *game)
{
	t_player	*player;
	t_camera	camera;
	int			i;

	player = &game->player;
	ft_fps(game);
	clear_image(game);
	init_camera(&camera, player);
	i = 0;
	while (i < game->w)
	{
		camera.camera_x = 2 * i / (double)game->w - 1;
		camera.raydir_x = camera.dir_x + camera.plane_x * camera.camera_x;
		camera.raydir_y = camera.dir_y + camera.plane_y * camera.camera_x;
		move_player_ws(player, game);
		draw_line(player, &camera, game, i);
		i++;
	}
	draw_map(game);
	draw_player(player->vect.x, player->vect.y, WHITE, game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img_ptr, 0, 0);
	return (0);
}
