/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_init_V2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfraslin <sfraslin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:17:47 by sfraslin          #+#    #+#             */
/*   Updated: 2025/04/11 11:20:14 by sfraslin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_test.h"

static char	**get_map(void)
{
	char	**map;

	map = malloc(sizeof(char *) * 15);
	map[0] = "11111111111111111111";
	map[1] = "10000000000000000001";
	map[2] = "10000000000000000001";
	map[3] = "10000000000000000001";
	map[4] = "10000000000111000001";
	map[5] = "10000000000000000001";
	map[6] = "10000100000000000001";
	map[7] = "10000000000000000001";
	map[8] = "10000000000011000001";
	map[9] = "10000000000000000001";
	map[10] = "10000000000000000001";
	map[11] = "10000000000000000001";
	map[12] = "10000000000000000001";
	map[13] = "11111111111111111111";
	map[14] = NULL;
	return (map);
}

void	init_game(t_game *game)
{
	struct timeval	time;
	int	h;
	int	w;
	
	gettimeofday(&time, NULL);
	init_vectors(&game->vectors);
	init_player(game);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Game");
	init_picture(game);
	game->map = get_map();
	game->start_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	game->time = 0;
	game->old_time = 0;
	game->frame_time = 0;
	game->p_speed = 0;
	game->r_speed = 0;
	game->texture[0] = mlx_xpm_file_to_image(game->mlx, "brick_wall_brown.xpm", &w, &h);
}

void	init_player(t_game *game)
{
	t_player	*player;
	
	player = &game->player;
	player->key_down = false;
	player->key_up = false;
	player->key_right = false;
	player->key_left = false;
	player->left_rotate = false;
	player->right_rotate = false;
}

void	init_vectors(t_vector *vectors)
{
	vectors->pos_x = 8;
	vectors->pos_y = 9;
	vectors->dir_x = -1;
	vectors->dir_y = 0;
	vectors->plane_x = 0;
	vectors->plane_y = 0.66;
	vectors->raydir_x = 0;
	vectors->raydir_y = 0;
}

void	init_picture(t_game *game)
{
	t_picture	*p;

	p = &game->picture;
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	p->data = mlx_get_data_addr(game->img, &p->bpp, &p->len, &p->endian);
}
