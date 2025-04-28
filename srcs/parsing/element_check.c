/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sovincen <sovincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:06:10 by sovincen          #+#    #+#             */
/*   Updated: 2025/04/22 11:39:12 by sovincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

//Check the type of the element contain in the line of the game file
//If the line begin with NO, SO, EA, WE, F or C increment the according 
//element
//End the program if the line did not begin with a space, a newline, or a
//character in the charset of the map (1, 0, N, W, S, E)
static void	element_count(char *line, t_elem *elements, t_game *game)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		elements->north++;
	else if (ft_strncmp(line, "SO ", 3) == 0)
		elements->south++;
	else if (ft_strncmp(line, "EA ", 3) == 0)
		elements->east++;
	else if (ft_strncmp(line, "WE ", 3) == 0)
		elements->west++;
	else if (line[0] == 'F' && line[1] == ' ')
		elements->floor++;
	else if (line[0] == 'C' && line[1] == ' ')
		elements->ceiling++;
	else if (is_empty_line(line) == 0 && is_map_line(line) == 0)
		error_exit("Wrong elements in the file: ", line, game);
}

//Read the game file a first time for checks
//Check if:	-the file can be open
//			-there is exactly one element of each (NO, SO, WE, EA, F, C)
void	check_element(t_game *game)
{
	t_elem	elem;
	int		i;

	i = 0;
	init_elements(&elem);
	while (game->game_data[i] && is_map_line(game->game_data[i]) == 0)
	{
		element_count(game->game_data[i], &elem, game);
		i++;
	}
	if (elem.north != 1 || elem.south != 1 || elem.east != 1
		|| elem.west != 1 || elem.floor != 1 || elem.ceiling != 1)
		error_exit("Invalid file content", NULL, game);
}
