/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfraslin <sfraslin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:41:11 by sovincen          #+#    #+#             */
/*   Updated: 2025/04/23 14:02:19 by sfraslin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

//Check if the path is a path to an xpm file
static int	check_path(char *path)
{
	char	*format;
	int		i;
	int		len;

	len = ft_strlen(path);
	format = ft_strnstr(path, ".xpm", len);
	if (format == NULL)
		return (FALSE);
	i = 4;
	while (format[i])
	{
		if (ft_isspace(format[i]) == 0)
			return (0);
		format[i] = '\0';
		i++;
	}
	return (TRUE);
}

//Get the path of the texture
//Check if the path is a path to an xpm file
char	*get_path(char *line, t_game *game)
{
	int		i;
	int		len;
	char	*path;

	i = 3;
	len = ft_strlen(line);
	line[len - 1] = '\0';
	while (line && ft_isspace(line[i]) == TRUE)
		i++;
	if (check_path(&line[i]) == FALSE)
		error_exit("Invalid texture path: ", line, game);
	path = ft_strdup(&line[i]);
	return (path);
}

//Open the texture by converting the xpm file into an mlx image
static void	*open_texture2(char *path, t_game *game)
{
	int		h;
	int		w;
	void	*ptr_img;

	ptr_img = mlx_xpm_file_to_image(game->mlx_ptr, path, &w, &h);
	if (ptr_img == NULL)
		error_exit("Failed to open texture files", path, game);
	if (w != BLOCK || h != BLOCK)
	{
		mlx_destroy_image(game->mlx_ptr, ptr_img);
		error_exit("Invalid texture: ", path, game);
	}
	return (ptr_img);
}

void	open_texture(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		game->texture[i].img_ptr = open_texture2(game->tex_path[i], game);
		game->texture[i].addr = mlx_get_data_addr(game->texture[i].img_ptr,
				&game->texture[i].bpp, &game->texture[i].line_len,
				&game->texture[i].endian);
		free(game->tex_path[i]);
		game->tex_path[i] = NULL;
		i++;
	}
}
