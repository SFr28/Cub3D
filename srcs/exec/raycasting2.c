/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sovincen <sovincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:42:19 by sovincen          #+#    #+#             */
/*   Updated: 2025/04/23 14:53:19 by sovincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

//Check if the coordinate given touch a wall or not
int	touch(float px, float py, t_game *game)
{
	int	x;
	int	len;
	int	y;

	x = (int)px;
	y = (int)py;
	len = 0;
	if (y < 0 || y > game->height_map - 1)
		return (TRUE);
	while (game->map[y] && game->map[y][len])
		len++;
	if (x < 0 || x > len || game->map[y][x] == '\0')
		return (TRUE);
	if (game->map[y][x] == '1')
		return (TRUE);
	return (FALSE);
}

//Initialise value for the camera (point of vue of the player)
//dir_x :
//dir_y :
//fov :
//plane_x :
//plane_y :
void	init_camera(t_camera *camera, t_player *player)
{
	camera->dir_x = cos(player->angle);
	camera->dir_y = sin(player->angle);
	camera->fov = 0.66;
	camera->plane_x = -(camera->dir_y) * camera->fov;
	camera->plane_y = camera->dir_x * camera->fov;
}

//Initialise the direction of the direction of the ray
//(check if raydir x or y == 0 to avoid division by 0)
void	init_raydir(t_camera *camera, t_data *data)
{
	if (camera->raydir_x == 0)
		data->deltadist_x = 1e30;
	else
		data->deltadist_x = fabs(1 / camera->raydir_x);
	if (camera->raydir_y == 0)
		data->deltadist_y = 1e30;
	else
		data->deltadist_y = fabs(1 / camera->raydir_y);
}

//Depending of the direction of the ray, determine the value of the
//step to take (positive or negative / axe x or y)
void	find_step(t_camera *camera, t_data *data, t_vect *vect)
{
	if (camera->raydir_x < 0)
	{
		data->step_x = -1;
		data->sidedist_x = ((vect->x) - data->x) * data->deltadist_x;
	}
	else
	{
		data->step_x = 1;
		data->sidedist_x = (data->x + 1.0 - (vect->x)) * data->deltadist_x;
	}
	if (camera->raydir_y < 0)
	{
		data->step_y = -1;
		data->sidedist_y = ((vect->y) - data->y) * data->deltadist_y;
	}
	else
	{
		data->step_y = 1;
		data->sidedist_y = (data->y + 1.0 - (vect->y)) * data->deltadist_y;
	}
}

//Base of the DDA algotith
//While the ray did not touch a wall, increase the ray by step
//step x or step y depending which one is the closer (smallest sidedist)
//side : if we increase in x -> 0 (mean we are on the north/south axis)
//		 if we increase in y -> 1 (mean we are on the east/west axis)
void	dda_algo(t_data *data, t_game *game)
{
	while (touch(data->x, data->y, game) == 0)
	{
		if (data->sidedist_x < data->sidedist_y)
		{
			data->sidedist_x += data->deltadist_x;
			data->x += data->step_x;
			data->side = 0;
		}
		else
		{	
			data->sidedist_y += data->deltadist_y;
			data->y += data->step_y;
			data->side = 1;
		}
	}
}
