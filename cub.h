/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sovincen <sovincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:26:14 by sfraslin          #+#    #+#             */
/*   Updated: 2025/04/14 15:57:21 by sovincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "libft.h"
# include "mlx.h"

# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>

# define WIDHT 1366
# define HEIGHT 768
# define BLOCK 64

# define DEBUG 0

//Color
# define WHITE 0xFFFFFF
# define DARK_CYAN 0x008B8B
# define GREEN 0x00FF7F
# define VIOLET 0x7B68EE
# define CYAN 0x00FFFF
# define YELLOW 0xADFF2F
# define ORANGE 0xFF8C00

//keyboard
# define ESCAPE 0xff1b
# define LEFT 0xff51
# define UP 0xff52
# define RIGHT 0xff53
# define DOWN 0xff54
# define Z 0x007a
# define X 0x0078
# define W 0x0077
# define A 0x0061
# define S 0x0073
# define D 0x0064
# define C 0x0063

typedef struct s_vect
{
	float	x;
	float	y;
}			t_vect;

typedef struct s_camera
{
	double	camera_x;
	double	raydir_x;
	double	raydir_y;
	double	dir_x;
	double	dir_y;
	double	fov;
	double	plane_x;
	double	plane_y;
}			t_camera;

typedef struct s_player
{
	t_vect	vect;
	float	angle;
	float	cos_angle;
	float	sin_angle;
	
	int		key_up;
	int		key_down;
	int		key_left;
	int		key_right;
	int		left_rotate;
	int		right_rotate;
}			t_player;

typedef struct s_env
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	t_player	player;
	char		**map;
}			t_env;

void	img_pixel_put(t_env *img, int x, int y, int color);
void	draw_square(int x, int y, int size, int color, t_env *game);
void	move_player(t_player *player);
int		draw_loop(t_env *env);
char 	**get_map(void);
void	set_hooks(t_env *env);
void	init_game(t_env *env);
void	error_exit(char *err_msg);
void	draw_map(t_env *env);
void	clear_image(t_env *env);
void	draw_player(int x, int y, int color, t_env *game);


int		touch(float px, float py, t_env *env);

#endif
