/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_init_V2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfraslin <sfraslin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:17:47 by sfraslin          #+#    #+#             */
/*   Updated: 2025/04/10 14:11:43 by sfraslin         ###   ########.fr       */
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
	int	h;
	int	w;
	
	init_vectors(&game->vectors);
	init_player(game);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Game");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->len, &game->endian);
	game->map = get_map();
	game->texture[0] = mlx_xpm_file_to_image(game->mlx, "brick_wall_brown.xpm", &w, &h);
}

void	init_player(t_game *game)
{
	t_player	*player;
	
	player = &game->player;
	player->x = 1;
	player->y = 2;
	player->key_down = false;
	player->key_up = false;
	player->key_right = false;
	player->key_left = false;
	player->left_rotate = false;
	player->right_rotate = false;
}

void	init_vectors(t_vector *vectors)
{
	vectors->pos_x = 12;
	vectors->pos_y = 14;
	vectors->dir_x = -1;
	vectors->dir_y = 0;
	vectors->plane_x = 0;
	vectors->plane_y = 0.66;
	vectors->camera_x = 0;
	vectors->raydir_x = 0;
	vectors->raydir_y = 0;
}
