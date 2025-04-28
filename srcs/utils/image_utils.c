/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfraslin <sfraslin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:49:37 by sovincen          #+#    #+#             */
/*   Updated: 2025/04/23 11:36:51 by sfraslin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

//Color a pixel with the according color on an image
void	img_pixel_put(t_game *img, int x, int y, int color)
{
	int	pixel;

	if (!(x > 0 && x < img->w) || !(y > 0 && y < img->h))
		return ;
	pixel = (y * img->line_len) + (x * 4);
	if (img->endian == 1)
	{
		img->addr[pixel + 0] = (color >> 24);
		img->addr[pixel + 1] = (color >> 16) & 0xFF;
		img->addr[pixel + 2] = (color >> 8) & 0xFF;
		img->addr[pixel + 3] = color & 0xFF;
	}
	else if (img->endian == 0)
	{
		img->addr[pixel + 0] = color & 0xFF;
		img->addr[pixel + 1] = (color >> 8) & 0xFF;
		img->addr[pixel + 2] = (color >> 16) & 0xFF;
		img->addr[pixel + 3] = (color >> 24);
	}
}

int	img_pixel_get(int i, int x, int y, t_game *game)
{
	int		pixel;
	int		color;
	t_img	img;

	color = 0;
	img = game->texture[i];
	pixel = (y * img.line_len) + (x * 4);
	if (img.endian == 1)
	{
		color = (img.addr[pixel + 0] << 24) + (img.addr[pixel + 1] << 16)
			+ (img.addr[pixel + 2] << 8) + img.addr[pixel + 3];
	}
	else if (img.endian == 0)
	{
		color = (img.addr[pixel + 3] << 24) + (img.addr[pixel + 2] << 16)
			+ (img.addr[pixel + 1] << 8) + img.addr[pixel + 0];
	}
	return (color);
}

void	clear_image(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	while (x < game->w)
	{
		y = 0;
		while (y < game->h)
		{
			img_pixel_put(game, x, y, 0);
			y++;
		}
		x++;
	}
}
