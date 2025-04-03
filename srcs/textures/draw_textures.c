/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfraslin <sfraslin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:56:13 by sfraslin          #+#    #+#             */
/*   Updated: 2025/04/03 17:23:44 by sfraslin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	img_pixel_put(t_game *game, int x, int y, int color)
{
	int	pixel;

	if (!(x > 0 && x < WIDTH) || !(y > 0 && y < HEIGHT))
		return ;
	pixel = (y * game->len) + (x * 4);
	if (game->endian == 1)
	{
		game->data[pixel + 0] = (color >> 24);
		game->data[pixel + 1] = (color >> 16) & 0xFF;
		game->data[pixel + 2] = (color >> 8) & 0xFF;
		game->data[pixel + 3] = color & 0xFF;
	}
	else if (game->endian == 0)
	{
		game->data[pixel + 0] = color & 0xFF;
		game->data[pixel + 1] = (color >> 8) & 0xFF;
		game->data[pixel + 2] = (color >> 16) & 0xFF;
		game->data[pixel + 3] = (color >> 24);
	}
}

void	draw_textures(t_game *game, int x, int y)
{
	t_data_line	l_data;
	void		*img;
	int			color;

	color = get_color(game, img, x, y);
	initialise_data_line(game, &l_data);
	img_pixel_put(game, x, y, color);
}
