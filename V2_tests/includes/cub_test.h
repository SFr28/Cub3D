/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_test.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfraslin <sfraslin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:26:14 by sfraslin          #+#    #+#             */
/*   Updated: 2025/04/10 13:47:43 by sfraslin         ###   ########.fr       */
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

# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363
# define PSPEED 0.5
# define RSPEED 0.03

# define PI 3.14159265359
# define MAX 2147483647

# define DEBUG 0

typedef struct s_vector
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	camera_x;
	double	raydir_x;
	double	raydir_y;
}				t_vector;

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
	int		mx;
	int		my;
	void	*texture[4];
	
	t_player	player;
	t_vector	vectors;
}			t_game;

int		draw_loop(t_game *game);
void	draw_line(t_game *game, t_vector *vec, int i);
void	draw_blocks(t_game *game, int cube_h, int side, int start_x);

void	img_pixel_put(t_game *game, int x, int y, int color);
void	clear_image(t_game *game);
int		ft_touch(t_game *game, double side[2], int step[2], double delta[2]);
int		which_color(t_game *game, t_vector *vec, int side);

void	init_game(t_game *game);
void	init_player(t_game *game);
void	init_vectors(t_vector *vectors);

int		key_press(int keycode, t_player *player);
int		key_release(int keycode, t_player *player);
int		ft_close(t_game *game);
void	move_up_down(t_game *game, t_player *player, t_vector *vec);
void	rotation(t_player *player, t_vector *vec);

#endif
