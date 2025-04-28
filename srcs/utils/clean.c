/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sovincen <sovincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 14:36:14 by sovincen          #+#    #+#             */
/*   Updated: 2025/04/21 16:59:19 by sovincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	clean_img_texture(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->tex_path[i] != NULL)
			free(game->tex_path[i]);
		if (game->texture[i].img_ptr != NULL)
			mlx_destroy_image(game->mlx_ptr, game->texture[i].img_ptr);
		i++;
	}
}

//Free and destroy all to close the program proprely
void	clean_game(t_game *game)
{
	if (game->game_data != NULL)
		free_array(game->game_data);
	if (game->map != NULL)
		free(game->map);
	clean_img_texture(game);
	if (game->img_ptr != NULL)
		mlx_destroy_image(game->mlx_ptr, game->img_ptr);
	if (game->win_ptr != NULL)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (game->mlx_ptr != NULL)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
}
