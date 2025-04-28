/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfraslin <sfraslin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:26:14 by sfraslin          #+#    #+#             */
/*   Updated: 2025/04/24 10:13:36 by sfraslin         ###   ########.fr       */
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
# include <sys/time.h>

# define BLOCK 64
# define BLOCK_MAP 6

# define FALSE 0
# define TRUE 1

# define PI 3.14159265358979323846

# define DEBUG 0

//Color
# define BLACK 0x000000
# define WHITE 0xFFFFFF
# define DARK_CYAN 0x008B8B
# define GREEN 0x00FF7F
# define VIOLET 0x7B68EE
# define CYAN 0x00FFFF
# define YELLOW 0xADFF2F
# define ORANGE 0xFF8C00
# define BROWN 0x8B4513
# define RED 0xB22222
# define GREY 0x708090

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

typedef struct s_fps
{
	double	start_time;
	double	time;
	double	old_time;
	double	frame_time;
	double	p_speed;
	double	r_speed;
}			t_fps;

typedef struct s_elem
{
	int	north;
	int	south;
	int	east;
	int	west;
	int	ceiling;
	int	floor;
}		t_elem;

typedef struct s_info
{
	char	*no_path;
	char	*so_path;
	char	*ea_path;
	char	*we_path;
	int		f_color;
	int		c_color;
}			t_info;

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

typedef struct s_data
{
	int		x;
	int		y;
	double	deltadist_x;
	double	deltadist_y;
	double	sidedist_x;
	double	sidedist_y;
	int		step_x;
	int		step_y;
	int		side;
	double	perp_walldist;
	int		lineheight;
	int		drawstart;
	int		drawend;
	double	wall_x;
	int		tex_x;
	int		tex_y;
}			t_data;

typedef struct s_player
{
	t_vect	vect;
	float	angle;
	float	cos_angle;
	float	sin_angle;
	int		move_up;
	int		move_down;
	int		move_left;
	int		move_right;
	int		left_rotate;
	int		right_rotate;
	int		run;
}			t_player;

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}			t_img;

typedef struct s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			h;
	int			w;
	void		*img_ptr;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	t_player	player;
	t_fps		fps_info;
	char		**map;
	int			height_map;
	int			width_map;
	int			f_color;
	int			c_color;
	char		*tex_path[5];
	t_img		texture[5];
	char		**game_data;
}				t_game;

//Init
void	init_game(t_game *game);
void	init_gameinfo(t_game *game);
void	init_elements(t_elem *elements);
void	init_data(t_data *data, t_player *player);
void	init_fps(t_fps *fps_info);

//Parsing
void	parse_gameinfo(int argc, char **argv, t_game *game);
void	check_element(t_game *game);
int		is_map_line(char *line);
void	get_texture(t_game *game);
void	open_texture(t_game *game);
char	*get_path(char *line, t_game *game);
void	get_map(t_game *game);
void	check_map(char **map, t_game *game);
void	parse_player(char **map, t_game *game);
void	error_exit(char *msg, char *msg2, t_game *game);
void	error_exit_color(int type, t_game *game, char *line, char **rgb_code);

//Utils
int		is_in_mapset(char c);
int		is_in_playerset(char c);
void	free_array(char **arg);
int		ft_isspace(char c);
int		is_empty_line(char *line);
void	clear_image(t_game *game);
void	clean_game(t_game *game);
void	img_pixel_put(t_game *img, int x, int y, int color);
int		img_pixel_get(int texture, int x, int y, t_game *img);
void	draw_square(int x, int y, int color, t_game *game);

//Execution
int		draw_loop(t_game *game);
void	set_hooks(t_game *game);
void	draw_map(t_game *game);
void	draw_player(int x, int y, int color, t_game *game);
int		touch(float px, float py, t_game *game);
void	init_camera(t_camera *camera, t_player *player);
void	init_raydir(t_camera *camera, t_data *data);
void	find_step(t_camera *camera, t_data *data, t_vect *vect);
void	dda_algo(t_data *data, t_game *game);
int		which_color_tex(int i, t_data *data, t_camera *camera, t_game *game);
void	distance_to_wall(t_data *data);
void	walls_height(t_data *data, t_game *game);

//Movements
void	move_player_ws(t_player *player, t_game *game);
void	rotate_player(t_player *player, double angle_speed);
void	ft_fps(t_game *game);

#endif
