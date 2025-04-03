/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfraslin <sfraslin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:56:13 by sfraslin          #+#    #+#             */
/*   Updated: 2025/04/03 15:34:41 by sfraslin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	get_texture(t_game	*game, char *path[5])
{
	int	i;
	int	w;
	int	h;

	i = 0;
	while (i < 5)
	{
		game->texture[i] = mlx_xpm_file_to_image(game->mlx, path[i], &w, &h);
		if (!game->texture[i])
		{
			ft_putstr_fd("Error\nFailure loading texture ", 2);
			if (i == 0)
				ft_putendl_fd("NO", 2);
			if (i == 1)
				ft_putendl_fd("SO", 2);
			if (i == 2)
				ft_putendl_fd("WE", 2);
			if (i == 3)
				ft_putendl_fd("EA", 2);
			ft_close(game);
		}
		i++;
	}
}

void	ft_destroy_texture(t_game *game)
{
	int	i;

	i = 0;
	while (game->texture[i])
	{
		mlx_destroy_image(game->mlx, game->texture[i]);
		i++;
	}
}

void	ft_close(t_game *game)
{
	int	i;

	i = 0;
	ft_destroy_texture(game);
	//clear map
	//clear everything
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit (0);
}
