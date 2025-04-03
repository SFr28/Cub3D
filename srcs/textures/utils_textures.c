/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfraslin <sfraslin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 17:17:00 by sfraslin          #+#    #+#             */
/*   Updated: 2025/04/03 17:27:45 by sfraslin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	initialise_data_line(t_game *game, t_data_line *data)
{
	data->ray_x = game->player.x;
	data->ray_y = game->player.y;
	data->start_x = game->player.angle - PI / 6;
	data->cos_angle = cos(data->start_x);
	data->sin_angle = sin(data->start_x);
}

int	get_color(t_game *game, void *img, int x, int y)
{
	char	color[4];
	int		pixel;

	game->data = mlx_get_data_addr(img, &game->bpp, &game->len, &game->endian);
	pixel = (y * game->len) + (x * 4);
	if (game->endian == 1)
	{
		color[0] = game->data[pixel + 0];
		color[1] = game->data[pixel + 1];
		color[2] = game->data[pixel + 2];
		color[3] = game->data[pixel + 3];
	}
	else if (game->endian == 0)
	{
		color[3] = game->data[pixel + 3];
		color[2] = game->data[pixel + 2];
		color[1] = game->data[pixel + 1];
		color[0] = game->data[pixel + 0];
	}
	return (ft_str_to_bi(color));
}
