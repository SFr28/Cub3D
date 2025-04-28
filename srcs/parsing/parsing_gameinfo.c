/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_gameinfo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sovincen <sovincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 12:13:29 by sovincen          #+#    #+#             */
/*   Updated: 2025/04/23 10:26:53 by sovincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

//Check that the argument given is a ".cub" file
//  - 0 : the file is NOT a ".cub"
//  - 1 : the file is a ".cub"
static int	check_filename(char *filename)
{
	int		len;
	char	*format;

	len = ft_strlen(filename);
	format = &filename[len - 4];
	if (ft_strncmp(format, ".cub", 4) == 0)
		return (TRUE);
	return (FALSE);
}

static int	count_line(char *gamefile)
{
	int		fd;
	char	*line;
	int		count;

	count = 0;
	fd = open(gamefile, O_RDONLY);
	if (fd < 0)
		error_exit("Can't open gamefile", NULL, NULL);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		free(line);
		count++;
	}
	close(fd);
	return (count);
}

static void	read_gamefile(char *gamefile, t_game *game)
{
	int		fd;
	int		i;
	char	*line;
	int		nb_line;

	i = 0;
	nb_line = count_line(gamefile);
	game->game_data = malloc(sizeof(char *) * (nb_line + 1));
	if (game->game_data == NULL)
		error_exit("Allocation failed: ", "read_gamefile", NULL);
	fd = open(gamefile, O_RDONLY);
	if (fd < 0)
		error_exit("Can't open gamefile", NULL, NULL);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		game->game_data[i] = ft_strdup(line);
		free(line);
		i++;
	}
	game->game_data[i] = NULL;
	close(fd);
}

//Check the number of argument and the format of the argument given(*.cub)
//Check the element in the file
//Check the map
//Get the texture and color
//Get the map
void	parse_gameinfo(int argc, char **argv, t_game *game)
{
	if (argc != 2)
		error_exit("Wrong number of arguments : ./cub3d *.cub", NULL, NULL);
	if (BLOCK <= 0 || BLOCK > 256)
		error_exit("Wrong define BLOCK", NULL, NULL);
	if (check_filename(argv[1]) == FALSE)
		error_exit("Wrong map format: *.cub", NULL, NULL);
	init_gameinfo(game);
	read_gamefile(argv[1], game);
	check_element(game);
	get_texture(game);
	get_map(game);
	check_map(game->map, game);
}
