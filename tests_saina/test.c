/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfraslin <sfraslin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:10:44 by sfraslin          #+#    #+#             */
/*   Updated: 2025/04/04 14:44:52 by sfraslin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_test.h"

char	**get_map(void)
{
	char	**map;

	map = malloc(sizeof(char *) * 11);
	map[0] = "111111111111111";
	map[1] = "100000000000001";
	map[2] = "100000000100001";
	map[3] = "100000001010001";
	map[4] = "100000000100001";
	map[5] = "100000001000001";
	map[6] = "100000010000001";
	map[7] = "100001000000001";
	map[8] = "100000000000001";
	map[9] = "111111111111111";
	map[10] = NULL;
	return (map);
}

void	img_pixel_put(t_game *game, int x, int y, int color)
{
	int	pixel;

	if (!(x > 0 && x < WIDTH) || !(y > 0 && y < HEIGHT))
		return ;
	pixel = (y * game->len) + (x * 4);
	if (game->endian == 1)
	{
		game->data[pixel + 0] = (color >> 24);
		game->data[pixel + 1] = (color >> 16) & 0xFF;
		game->data[pixel + 2] = (color >> 8) & 0xFF;
		game->data[pixel + 3] = color & 0xFF;
	}
	else if (game->endian == 0)
	{
		game->data[pixel + 0] = color & 0xFF;
		game->data[pixel + 1] = (color >> 8) & 0xFF;
		game->data[pixel + 2] = (color >> 16) & 0xFF;
		game->data[pixel + 3] = (color >> 24);
	}
}

void	draw_square(int x, int y, int size, int color, t_game *game)
{
	int	i;

	i = -1;
	while (i++ < size)
		img_pixel_put(game, (x + i), y, color);
	i = -1;
	while (i++ < size)
		img_pixel_put(game, x, (y + i), color);
	i = -1;
	while (i++ < size)
		img_pixel_put(game, (x + size), (y + i), color);
	i = -1;
	while (i++ < size)
		img_pixel_put(game, (x + i), (y + size), color);

}

void	draw_map(t_game *game)
{
	char	**map;
	int		color;
	int		y;
	int		x;

	map = game->map;
	color = 0x0000FF;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				draw_square(x * 50, y * 50, 50, color, game);
			x++;
		}
		y++;
	}
}

void	clear_image(t_game *game)
{
	int	y;
	int	x;
	
	y = 0;
	while (y < HEIGHT)
	{
		x = -1;
		while (x++ < WIDTH)
		img_pixel_put(game, x, y, 0);
		y++;
	}
}

void	init_game(t_game *game)
{
	int	h;
	int	w;
	
	init_player(&game->player);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Game");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->len, &game->endian);
	game->map = get_map();
	game->texture[0] = mlx_xpm_file_to_image(game->mlx, "brick_wall_brown.xpm", &w, &h);
}

int	draw_loop(t_game *game)
{
	t_player	*player;
	float		fraction;
	float		start_x;
	int			i;

	i = 0;
	fraction = PI / 3 / WIDTH;
	player = &game->player;
	start_x = player->angle - PI / 6;
	move_player(player);
	clear_image(game);
	if (DEBUG)
	{
		draw_square(player->x, player->y, 15, 0x00FF00, game);
		draw_map(game);
	}
	while (i < WIDTH)
	{
		draw_line(player, game, start_x, i);
		start_x += fraction;
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

int	main(void)
{
	t_game	game;

	init_game(&game);
	if (!game.texture[0])
	{
		ft_close(&game);
		return (1);
	}
	mlx_hook(game.win, 2, 1L << 0, key_press, &game.player);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game.player);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_hook(game.win, 17, 1L << 17, ft_close, &game);
	mlx_loop(game.mlx);
	return (0);
}
