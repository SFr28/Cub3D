/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfraslin <sfraslin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:05:56 by sovincen          #+#    #+#             */
/*   Updated: 2025/04/24 10:10:47 by sfraslin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	init_player_pos(int x, int y, t_game *game)
{
	float	angle;

	game->player.vect.x = x + 0.5;
	game->player.vect.y = y + 0.5;
	if (game->map[y][x] == 'N')
		angle = (3 * PI) / 2;
	if (game->map[y][x] == 'S')
		angle = PI / 2;
	if (game->map[y][x] == 'W')
		angle = PI;
	if (game->map[y][x] == 'E')
		angle = 0;
	game->player.angle = angle;
}

void	parse_player(char **map, t_game *game)
{
	int	x;
	int	y;
	int	player;

	y = 0;
	player = 0;
	while (map[y] != NULL)
	{
		x = 0;
		while (map[y][x])
		{
			if (is_in_playerset(map[y][x]) == TRUE)
			{
				player++;
				init_player_pos(x, y, game);
				game->map[y][x] = '0';
			}
			if (player > 1)
				error_exit("More than one player in the map", NULL, game);
			x++;
		}
		y++;
	}
	if (player == 0)
		error_exit("No player in the map", NULL, game);
}
