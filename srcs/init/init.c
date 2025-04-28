/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfraslin <sfraslin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:42:06 by sovincen          #+#    #+#             */
/*   Updated: 2025/04/23 11:44:33 by sfraslin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	init_player(t_player *player)
{
	player->move_up = FALSE;
	player->move_down = FALSE;
	player->move_left = FALSE;
	player->move_right = FALSE;
	player->left_rotate = FALSE;
	player->right_rotate = FALSE;
	player->run = FALSE;
	player->angle = 0;
	player->cos_angle = cos(0);
	player->sin_angle = sin(0);
}

//Initialise the number of each type of element in the file at 0
void	init_elements(t_elem *elements)
{
	elements->north = 0;
	elements->south = 0;
	elements->east = 0;
	elements->west = 0;
	elements->ceiling = 0;
	elements->floor = 0;
}

//Initialise data of the game
void	init_gameinfo(t_game *game)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		game->tex_path[i] = NULL;
		game->texture[i].img_ptr = NULL;
		i++;
	}
	game->game_data = NULL;
	game->map = NULL;
	game->mlx_ptr = NULL;
	game->win_ptr = NULL;
	game->img_ptr = NULL;
	init_fps(&game->fps_info);
	init_player(&game->player);
}

void	init_data(t_data *data, t_player *player)
{
	data->deltadist_x = 0;
	data->deltadist_y = 0;
	data->drawend = 0;
	data->drawstart = 0;
	data->lineheight = 0;
	data->perp_walldist = 0;
	data->side = 0;
	data->sidedist_x = 0;
	data->sidedist_y = 0;
	data->step_x = 0;
	data->step_y = 0;
	data->tex_x = 0;
	data->tex_y = 0;
	data->wall_x = 0;
	data->x = (int)player->vect.x;
	data->y = (int)player->vect.y;
}

void	init_fps(t_fps *fps_info)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	fps_info->frame_time = 0;
	fps_info->old_time = 0;
	fps_info->p_speed = 0;
	fps_info->r_speed = 0;
	fps_info->time = 0;
	fps_info->start_time = t.tv_sec * 1000 + t.tv_usec / 1000;
}
