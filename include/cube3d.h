/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:44:05 by aakerblo          #+#    #+#             */
/*   Updated: 2025/08/02 17:35:55 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <math.h>
# include <mlx.h>
# include <X11/keysym.h>

# define RED      0xFF0000
# define GREEN    0x00FF00
# define BLUE     0x0000FF
# define YELLOW   0xFFFF00
# define CYAN     0x00FFFF
# define MAGENTA  0xFF00FF
# define WHITE    0xFFFFFF
# define BLACK    0x000000
# define PSYCH_RED      0xFF0066
# define PSYCH_BLUE     0x0066FF
# define PSYCH_GREEN    0x66FF00
# define PSYCH_PURPLE   0xCC00FF
# define PSYCH_YELLOW   0xFFFF33
# define PSYCH_ORANGE   0xFF9933
# define PSYCH_TEAL     0x33FFCC
# define PSYCH_MAGENTA  0xFF33CC
# define DARK_RED       0x550000
# define DARK_GREEN     0x005500
# define DARK_BLUE      0x000055
# define DARK_YELLOW    0x555500
# define DARK_CYAN      0x005555
# define DARK_MAGENTA   0x550055
# define DARK_PINK  	0x550033

# define WIDTH 800
# define HEIGHT 800
# define MAP_X 8
# define MAP_Y 8
# define PLAYERSIZE 10
# define PLAYERSPEED 1
# define TURNSPEED PI / 128
# define DEBUG 0

# define LEFT 1
# define RIGHT 2
# define UP 3
# define DOWN 4

# define KEY_PRESS 2
# define KEY_RELEASE 3
# define DESTROY_WINDOW 17
# define PLAYERDIRECTIONSIZE 2000
# define FOV PI / 3

# define PI 3.141592653
# define RADIAN PI / 180


typedef struct s_new_p
{
	int p_new_position_x;
	int p_new_position_y;
}		t_new_p;

typedef struct s_coord
{
	int		start_x;
	int		start_y;
	int		end_x;
	int		end_y;
	int		dx;
	int		dy;
	int		dir_x;
	int		dir_y;
	int		err;
	int		temp_err;
}			t_coord;

typedef struct s_keys
{
	int	w_pressed;
	int	a_pressed;
	int	s_pressed;
	int	d_pressed;
	int	esc_pressed;
	int	left_pressed;
	int	right_pressed;
}		t_keys;

typedef struct s_map
{
	int		map[MAP_X][MAP_Y];
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	int		floor;
	int		ground;
}			t_map;

typedef struct s_img
{
	void	*img_addr;
	char	*pixel_addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_img;

typedef struct s_player
{
	int		position_x;
	int		position_y;
	double	precise_x;
	double	precise_y;
	double	error_x;
	double	error_y;
	double	delta_x;
	double	delta_y;
	int		square_x;
	int		square_y;
	double	cam_x;
	double	cam_y;
	double	distance;
	int		height;
	double	player_direction;
}			t_player;

typedef struct s_cube
{
	void		*mlx;
	void		*mlx_win;
	int			color;
	t_player	p;
	t_img		img;
	t_map		map;
	t_keys		keys;
	t_coord		coord;
}				t_cube;

void	render_image(t_cube *cube);
void	update_player_position(t_cube *cube, int dir);

// init functions
void	init_image(t_cube *cube);
void	init_keys(t_cube *cube);
void	init_hooks(t_cube *cube);
void	init_cube(t_cube *cube);

// hook functions
int		key_press_handler(int keysym, t_cube *cube);
int		key_release_handler(int keysym, t_cube *cube);
int		game_loop(t_cube *cube);
int		cleanup(t_cube *cube);

// draw functions
void	draw_pixel(t_img *img, int x, int y, int color);
double	scale(double value, double origin_max,
			double target_min, double target_max);
void	render_image(t_cube *cube);

// draw ray functions
void	draw_line(t_cube *cube, double angle, int screen_x);
void	raycasting(t_cube *cube);

// check functions
bool	check_wall_tile(t_cube *cube, int p_new_position_x, int p_new_position_y, int a);

#endif
