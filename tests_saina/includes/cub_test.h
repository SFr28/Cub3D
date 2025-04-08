/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_test.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfraslin <sfraslin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:26:14 by sfraslin          #+#    #+#             */
/*   Updated: 2025/04/08 14:06:36 by sfraslin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "mlx.h"
# include "libft.h"
# include "mlx_int.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include <fcntl.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <stdbool.h>

# define WIDTH 1280
# define HEIGHT 720
# define BLOCK 50

# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363

# define PI 3.14159265359
# define MAX 2147483647

# define DEBUG 0

typedef struct s_picture
{
	int		len;
	int		heigh;
	int		endian;
	char	*addr;
	void	*picture_ptr;
}			t_picture;

typedef struct s_player
{
	float	x;
	float	y;
	float	angle;
	
	bool	key_up;
	bool	key_down;
	bool	key_left;
	bool	key_right;
	
	bool	left_rotate;
	bool	right_rotate;
}		t_player;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	void	*img;

	char	*data;
	int		bpp;
	int		len;
	int		endian;
	
	char	*data2;
	int		bpp2;
	int		len2;
	int		endian2;

	char	**map;
	void	*texture[4];
	
	t_player	player;
}			t_game;


void	init_player(t_player *player);
void	init_game(t_game *game);
void	img_pixel_put(t_game *game, int x, int y, int color);
void	draw_square(int x, int y, int size, int color, t_game *game);

int		key_press(int keycode, t_player *player);
int		key_release(int keycode, t_player *player);
void	move_player(t_player *player);

int		touch(float px, float py, t_game *game);
void	draw_line(t_player *player, t_game *game, float start_x, int i);
float	distance(int ray_x, int player_x, int ray_y, int player_y, t_game *game);
int		ft_close(t_game *game);

int	get_color(t_game *game, void *img, int x, int y);
int	wall_direction(t_player *player, int wx, int wy, int touch);
int	improved_touch(t_game *game, int i, float start_x);

#endif
