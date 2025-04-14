/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfraslin <sfraslin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:07:52 by sovincen          #+#    #+#             */
/*   Updated: 2025/04/14 16:40:56 by sfraslin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	touch(float px, float py, t_env *env)
{
	int	x;
	int	y;

	x = (int)px;
	y = (int)py;
	if (env->map[y][x] == '1')
		return (1);
	return (0);
}

float	distance(float x1, float y1, float x2, float y2)
{
	float	delta_x;
	float	delta_y;
	float	dist;
	
	delta_x = x2 - x1;
	delta_y = y2 - y1;
	dist = sqrt(delta_x * delta_x + delta_y * delta_y);
	return (dist);
}

float	fix_distance(float x1, float y1, float x2, float y2, t_env *env)
{
	float	delta_x;
	float	delta_y;
	float	angle;
	float	dist;
	
	delta_x = x2 - x1;
	delta_y = y2 - y1;
	angle = atan2(delta_y, delta_x) - env->player.angle;
	dist = sqrt(delta_x * delta_x + delta_y * delta_y) * cos (angle);
	return (dist);
}

void	init_camera(t_camera *camera, t_player *player)
{
	camera->dir_x = cos(player->angle);
	camera->dir_y = sin(player->angle);
	camera->fov = 0.66;
	camera->plane_x = -(camera->dir_y) * camera->fov;
	camera->plane_y = camera->dir_x * camera->fov;
}

int	which_color(int	side, double x, double y, t_env *game)
{
	int	color;
	
	if (side == 0)
	{
		if (x > game->player.vect.x / BLOCK)
			color = VIOLET;
		else
			color = YELLOW;
	}
	else
	{
		if (y > game->player.vect.y / BLOCK)
			color = DARK_CYAN;
		else
			color = ORANGE;
	}
	return (color);
}
// void	init_raydir(t_camera *camera, t_data *data)
// {
// 	if (camera->raydir_x == 0)
// 		data->deltadist_x = 1e30;
// 	else
// 		data->deltadist_x = fabs(1/ camera->raydir_x);
// 	if (camera->raydir_y == 0)
// 		data->deltadist_y = 1e30;
// 	else
// 		data->deltadist_y = fabs(1 / camera->raydir_y);
// }

void	draw_line(t_player *player, t_camera *camera, t_env *game, int i)
{
	int	x;
	int	y;
	double	deltadist_x;
	double	deltadist_y;
	double	sidedist_x;
	double	sidedist_y;
	int		step_x;
	int		step_y;
	int		side;

	x = (int)player->vect.x / BLOCK;
	y = (int)player->vect.y / BLOCK;
	// init_raydir(&camera, &data);
	if (camera->raydir_x == 0)
		deltadist_x = 1e30;
	deltadist_x = fabs(1/ camera->raydir_x);
	
	if (camera->raydir_y == 0)
		deltadist_y = 1e30;
	else
		deltadist_y = fabs(1 / camera->raydir_y);


	if (camera->raydir_x < 0)
	{
		step_x = -1;
		sidedist_x = ((player->vect.x / BLOCK) - x) * deltadist_x;
	}
	else
	{
		step_x = 1;
		sidedist_x = (x + 1.0 - (player->vect.x / BLOCK)) * deltadist_x;
	}
	if (camera->raydir_y < 0)
	{
		step_y = -1;
		sidedist_y = ((player->vect.y / BLOCK) - y) * deltadist_y;
	}
	else
	{
		step_y = 1;
		sidedist_y = (y + 1.0 - (player->vect.y / BLOCK)) * deltadist_y;
	}
	
	while (touch(x, y, game) == 0)
	{
		if (sidedist_x < sidedist_y)
		{
			sidedist_x += deltadist_x;
			x += step_x;
			side = 0;
		}
		else
		{	
			sidedist_y += deltadist_y;
			y += step_y;
			side = 1;
		}
	}
	double	perp_walldist;
	if (side == 0)
		perp_walldist = sidedist_x - deltadist_x;
	else
		perp_walldist = sidedist_y - deltadist_y;
	
	int	lineheight;
	int	drawstart;
	int	drawend;
	
	lineheight = (int)(HEIGHT / perp_walldist);
	drawstart = -lineheight / 2 + HEIGHT /2;
	if (drawstart < 0)
		drawstart = 0;
	drawend = lineheight / 2 + HEIGHT / 2;
	if (drawend >= HEIGHT)
		drawend = HEIGHT - 1;
	int	color;
	while(drawstart < drawend)
	{
		color = which_color(side, x, y, game);
		img_pixel_put(game, i, drawstart, color);
		drawstart++;
	}
}

int	draw_loop(t_env *env)
{
	t_player	*player;
	t_camera	camera;
	int			i;

	player = &env->player;
	move_player(player);
	clear_image(env);
	init_camera(&camera, player);
	i = 0;
	while (i < WIDHT)
	{
		camera.camera_x = 2 * i / (double)WIDHT - 1;
		camera.raydir_x = camera.dir_x + camera.plane_x * camera.camera_x;
		camera.raydir_y = camera.dir_y + camera.plane_y * camera.camera_x;
		draw_line(player, &camera, env, i);
		i++;
	}
	if (DEBUG == 1)
	{
		draw_map(env);
		draw_player(player->vect.x, player->vect.y, VIOLET, env);
	}
	mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->img_ptr, 0, 0);
	return (0);
}

//proteger contre define de WIDHT ou HEIGHT de 0