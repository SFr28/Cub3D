/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfraslin <sfraslin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:07:52 by sovincen          #+#    #+#             */
/*   Updated: 2025/04/22 15:45:55 by sfraslin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

//Calculate the distance which should separate the player with the wall
void	distance_to_wall(t_data *data)
{
	if (data->side == 0)
		data->perp_walldist = data->sidedist_x - data->deltadist_x;
	else
		data->perp_walldist = data->sidedist_y - data->deltadist_y;
	if (data->perp_walldist == 0)
		data->perp_walldist = 1e30;
}

//Calculate the height of the wall depending on the distance from the wall
//Allow to find the start and end point for drawing the line of pixel
//who represent the wall, on the screen
void	walls_height(t_data *data, t_game *game)
{
	data->lineheight = (int)(game->h / data->perp_walldist);
	if (data->lineheight == 0)
		data->lineheight = 2147483647;
	data->drawstart = -(data->lineheight) / 2 + game->h / 2;
	if (data->drawstart < 0)
		data->drawstart = 0;
	data->drawend = data->lineheight / 2 + game->h / 2;
	if (data->drawend >= game->h)
		data->drawend = game->h - 1;
}

//Return the index of the texture to draw on the screen
//texture[0] = North
//texture[1] = South
//texture[2] = East
//texture[3] = Weast
int	which_texture(t_data *data, t_camera *camera)
{
	int	texture;

	if (data->side == 0)
	{
		if (camera->raydir_x > 0)
			texture = 2;
		else
			texture = 3;
	}
	else
	{
		if (camera->raydir_y > 0)
			texture = 1;
		else
			texture = 0;
	}
	return (texture);
}

static void	get_coord_tex(int i, t_data *data, t_camera *camera, t_game *game)
{
	int	d;

	data->tex_x = (int)(data->wall_x * (double)BLOCK);
	if (data->tex_x < 0)
		data->tex_x = 0;
	if (data->tex_x >= BLOCK)
		data->tex_x = BLOCK - 1;
	if ((data->side == 0 && camera->raydir_x > 0)
		|| (data->side == 1 && camera->raydir_y < 0))
		data->tex_x = BLOCK - data->tex_x - 1;
	d = i * 2 - game->h + data->lineheight;
	data->tex_y = (((d * BLOCK) / data->lineheight)) / 2;
	if (data->tex_y < 0)
		data->tex_y = 0;
	if (data->tex_y >= BLOCK)
		data->tex_y = BLOCK - 1;
}

int	which_color_tex(int i, t_data *data, t_camera *camera, t_game *game)
{
	int		color;
	int		texture;

	if (data->side == 0)
		data->wall_x = game->player.vect.y + data->perp_walldist
			* camera->raydir_y;
	else
		data->wall_x = game->player.vect.x + data->perp_walldist
			* camera->raydir_x;
	data->wall_x -= floor(data->wall_x);
	get_coord_tex(i, data, camera, game);
	texture = which_texture(data, camera);
	color = img_pixel_get(texture, data->tex_x, data->tex_y, game);
	return (color);
}
