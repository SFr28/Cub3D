/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sovincen <sovincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:49:37 by sovincen          #+#    #+#             */
/*   Updated: 2025/04/09 14:30:45 by sovincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

//Color a pixel with the according color on an image
void	img_pixel_put(t_env *img, int x, int y, int color)
{
	int	pixel;

	if (!(x > 0 && x < WIDHT) || !(y > 0 && y < HEIGHT))
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

void	draw_square(int x, int y, int size, int color, t_env *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		img_pixel_put(game, x + i, y, color);
		img_pixel_put(game, x + i, y + size, color);
		i++;
	}
	j = 0;
	while (j < size)
	{
		img_pixel_put(game, x, y + j, color);
		img_pixel_put(game, x + size, y + j, color);
		j++;
	}
	img_pixel_put(game, x + size, y + size, color);
}

void	draw_player(int x, int y, int color, t_env *game)
{
	int	i;
	int	j;

	i = -4;
	while (i < 4)
	{
		j = -4;
		while (j < 4)
		{
			if (!(i == -4 && j == -4) && !(i == 3 && j == 3) && !(i == -4 && j == 3) && !(i == 3 && j == -4))
				img_pixel_put(game, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	clear_image(t_env *env)
{
	int x;
	int	y;

	x = 0;
	while (x < WIDHT)
	{
		y = 0;
		while (y < HEIGHT)
		{
			img_pixel_put(env, x, y, 0);
			y++;
		}
		x++;
	}
}
