/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sovincen <sovincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:09:15 by sovincen          #+#    #+#             */
/*   Updated: 2025/04/22 14:59:10 by sovincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

//Check if the given string is composed only of digit (3 digit max)
//Space are allowed at the begining of the string only for the first one
//Return :	-FALSE if not a digit or more than 3
//			-TRUE else
static int	check_format_rgb(char *str)
{
	int	i;
	int	count;

	i = 0;
	while (str && str[i])
	{
		count = 0;
		while (str[i] && str[i] != ',')
		{
			if (ft_isdigit(str[i]) == FALSE)
				return (FALSE);
			count++;
			i++;
		}
		if (count == 0 || count > 3)
			return (FALSE);
		if (str[i] && str[i + 1])
			i++;
	}
	return (TRUE);
}

//Convert the color in RGB format given in the file in int
//Check that there are 3 numbers separate by a comma
//and between 0 and 255
//Then construct the int using bitshifting
static int	get_color(char *line, t_game *game)
{
	int		i;
	int		color;
	int		rgb[3];
	char	**rgb_code;

	i = 0;
	if (check_format_rgb(line) == FALSE)
		error_exit_color(1, game, line, NULL);
	rgb_code = ft_split(line, ',');
	if (rgb_code == NULL)
		error_exit_color(2, game, line, NULL);
	while (rgb_code[i] != NULL && i < 3)
	{
		rgb[i] = ft_atoi(rgb_code[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
			error_exit_color(1, game, line, rgb_code);
		i++;
	}
	if (i != 3 || rgb_code[i] != NULL)
		error_exit_color(1, game, line, rgb_code);
	free_array(rgb_code);
	color = (rgb[0] << 16) + (rgb[1] << 8) + rgb[2];
	return (color);
}

//Get the color if the line is F or C
static void	get_fc_color(char *line, t_game *game)
{
	char	*line_trim;

	if (line[0] == 'F' && line[1] == ' ')
	{
		line_trim = ft_strtrim(&line[2], " \t\n\v\f\r");
		game->f_color = get_color(line_trim, game);
		free(line_trim);
	}
	if (line[0] == 'C' && line[1] == ' ')
	{
		line_trim = ft_strtrim(&line[2], " \t\n\v\f\r");
		game->c_color = get_color(line_trim, game);
		free(line_trim);
	}
}

//Get the path for each direction and open it to get the image 
//ready 
static void	get_texture_path(char *line, t_game *game)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		game->tex_path[0] = get_path(line, game);
	if (ft_strncmp(line, "SO ", 3) == 0)
		game->tex_path[1] = get_path(line, game);
	if (ft_strncmp(line, "EA ", 3) == 0)
		game->tex_path[2] = get_path(line, game);
	if (ft_strncmp(line, "WE ", 3) == 0)
		game->tex_path[3] = get_path(line, game);
}

void	get_texture(t_game *game)
{
	int	i;

	i = 0;
	while (game->game_data && game->game_data[i])
	{
		get_texture_path(game->game_data[i], game);
		get_fc_color(game->game_data[i], game);
		i++;
	}
	game->tex_path[4] = NULL;
}
