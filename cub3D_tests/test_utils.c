/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfraslin <sfraslin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:17:47 by sfraslin          #+#    #+#             */
/*   Updated: 2025/04/14 13:18:22 by sfraslin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_test.h"

void	img_pixel_put(t_picture *img, int x, int y, int color)
{
	int	pixel;

	if (!(x > 0 && x < WIDTH) || !(y > 0 && y < HEIGHT))
		return ;
	pixel = (y * img->len) + (x * 4);
	if (img->endian == 1)
	{
		img->data[pixel + 0] = (color >> 24);
		img->data[pixel + 1] = (color >> 16) & 0xFF;
		img->data[pixel + 2] = (color >> 8) & 0xFF;
		img->data[pixel + 3] = color & 0xFF;
	}
	else if (img->endian == 0)
	{
		img->data[pixel + 0] = color & 0xFF;
		img->data[pixel + 1] = (color >> 8) & 0xFF;
		img->data[pixel + 2] = (color >> 16) & 0xFF;
		img->data[pixel + 3] = (color >> 24);
	}
}

void	clear_image(t_game *game)
{
	int	y;
	int	x;
	
	y = 0;
	while (y < HEIGHT)
	{
		x = -1;
		while (x++ < WIDTH)
		img_pixel_put(&game->picture, x, y, 0);
		y++;
	}
}
