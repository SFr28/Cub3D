/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sovincen <sovincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:58:12 by sovincen          #+#    #+#             */
/*   Updated: 2025/04/22 13:34:01 by sovincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

//Print the appropriate error message on the screen 
//and quit the program
void	error_exit(char *msg, char *msg2, t_game *game)
{
	ft_putendl_fd("Error", 2);
	if (msg2 == NULL)
		ft_putendl_fd(msg, 2);
	else
	{
		ft_putstr_fd(msg, 2);
		ft_putendl_fd(msg2, 2);
	}
	if (game != NULL)
		clean_game(game);
	exit(1);
}

//Free the split of the color value before printing error message
//and quit the program
void	error_exit_color(int type, t_game *game, char *line, char **rgb_code)
{
	int	i;

	if (line != NULL)
		free(line);
	if (rgb_code)
	{
		i = 0;
		while (rgb_code && rgb_code[i])
		{
			free(rgb_code[i]);
			i++;
		}
		free(rgb_code);
	}
	if (type == 1)
		error_exit("Invalid rgb color", NULL, game);
	else
		error_exit("Allocation failed: ", "get_color", game);
}
