/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfraslin <sfraslin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:23:00 by sovincen          #+#    #+#             */
/*   Updated: 2025/04/22 17:25:46 by sfraslin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	is_map_line(char *line)
{
	int	i;
	int	b;

	i = 0;
	b = 0;
	while (line && line[i])
	{
		if (is_in_mapset(line[i]) == 1)
			b = 1;
		if (is_in_mapset(line[i]) == 0 && ft_isspace(line[i]) == 0)
			return (FALSE);
		i++;
	}
	if (b == 0)
		return (FALSE);
	return (TRUE);
}

void	get_map(t_game *game)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	len = 0;
	while (game->game_data[len])
		len++;
	i = 0;
	while (game->game_data[i] && is_map_line(game->game_data[i]) == 0)
		i++;
	game->height_map = len - i;
	game->map = malloc(sizeof(char *) * (game->height_map + 1));
	if (game->map == NULL)
		error_exit("Allocation failed: ", "get_map", game);
	j = 0;
	while (game->game_data[i])
	{
		game->map[j++] = game->game_data[i++];
	}
	game->map[j] = NULL;
}

//Erase the '\n' at the end of each line
//Replace the space character in the map by '2'
static void	parse_map(t_game *game)
{
	int	len;
	int	y;
	int	x;

	y = 0;
	while (game->map[y])
	{
		len = ft_strlen(game->map[y]);
		if (game->map[y][len - 1] == '\n')
			game->map[y][len - 1] = '\0';
		x = 0;
		while (game->map[y][x])
		{
			if (ft_isspace(game->map[y][x]) == TRUE)
				game->map[y][x] = '2';
			x++;
		}
		y++;
	}
}

static int	check_map_close(char **map)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == '0')
			{
				if ((int)ft_strlen(map[y + 1]) < x || map[y + 1][x] == '2')
					return (FALSE);
				if (y == 0 || (int)ft_strlen(map[y - 1]) < x
					|| map[y - 1][x] == '2')
					return (FALSE);
				if (map[y][x + 1] == '\0' || map[y][x + 1] == '2')
					return (FALSE);
				if (x == 0 || map[y][x - 1] == '2')
					return (FALSE);
			}
		}
		y++;
	}
	return (TRUE);
}

void	check_map(char **map, t_game *game)
{
	int	i;

	i = 0;
	while (map[i] != NULL)
	{
		if (is_map_line(map[i]) == 0)
			error_exit("Wrong character in the map", NULL, game);
		i++;
	}
	parse_player(map, game);
	parse_map(game);
	if (check_map_close(map) == FALSE)
		error_exit("The map is not closed", NULL, game);
}
