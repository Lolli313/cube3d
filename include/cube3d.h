/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:44:05 by aakerblo          #+#    #+#             */
/*   Updated: 2025/08/21 18:38:38 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <math.h>
# include <mlx.h>
# include <fcntl.h>
# include "libft.h"

# ifdef __linux__
#  include <X11/keysym.h>
# elif __APPLE__
#  define XK_w			13  // W
#  define XK_a			0   // A
#  define XK_s			1   // S
#  define XK_d			2   // D
#  define XK_Escape		53  // Escape
#  define XK_Left		123 // Left Arrow
#  define XK_Right		124 // Right Arrow
# endif

# define RED      			0xFF0000
# define GREEN    			0x00FF00
# define BLUE     			0x0000FF
# define YELLOW   			0xFFFF00
# define CYAN     			0x00FFFF
# define MAGENTA  			0xFF00FF
# define WHITE    			0xFFFFFF
# define BLACK    			0x000000
# define SHADOW_GREEN		0x00BB00
# define SHADOW_RED			0xBB0000
# define SHADOW_MAGENTA 	0xBB00BB
# define PSYCH_RED      	0xFF0066
# define PSYCH_BLUE     	0x0066FF
# define PSYCH_GREEN    	0x66FF00
# define PSYCH_PURPLE   	0xCC00FF
# define PSYCH_YELLOW   	0xFFFF33
# define PSYCH_ORANGE   	0xFF9933
# define PSYCH_TEAL     	0x33FFCC
# define PSYCH_MAGENTA  	0xFF33CC
# define DARK_RED       	0x550000
# define DARK_GREEN     	0x005500
# define DARK_BLUE      	0x000055
# define DARK_YELLOW    	0x555500
# define DARK_CYAN      	0x005555
# define DARK_MAGENTA   	0x550055
# define DARK_PINK  		0x550033

# define WIDTH 800
# define HEIGHT 800
# define MAP_X 33
# define MAP_Y 14
# define PLAYERSIZE 10
# define PLAYERSPEED 1
# define TURNSPEED PI / 256
# define DEBUG 0
# define TILESIZE 64

# define LEFT 1
# define RIGHT 2
# define UP 3
# define DOWN 4

# define KEY_PRESS 2
# define KEY_RELEASE 3
# define DESTROY_WINDOW 17
# define PLAYERDIRECTIONSIZE 2000
# define FOV 0.6

# define PI 3.141592653
# define RADIAN PI / 180


typedef struct s_new_p
{
	int p_new_position_x;
	int p_new_position_y;
}		t_new_p;

typedef struct s_tex
{
	int		tex_x;
	int		tex_y;
	double	tex_pos;
	int		tex_height;
	int		tex_width;
	double	visual_tex_height;
	double	tex_offset;
	double	step;
}			t_tex;

typedef struct s_img
{
	void	*img_addr;
	char	*pixel_addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}			t_img;

typedef struct s_coord
{
	double		start_x;
	double		start_y;
	double	ray_dir_x;
	double	ray_dir_y;
	int		step_x;
	int		step_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		map_x;
	int		map_y;
	double	pos_x;
	double	pos_y;
	double	wall_distance;
	double	perp_wall_dist;
	int		side;
	t_img	*side_detailed;
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
	int		map[MAP_Y][MAP_X];
	t_img	*NO;
	t_img	*SO;
	t_img	*WE;
	t_img	*EA;
	int		floor;
	int		ceiling;
}			t_map;

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
	t_tex		tex;
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
void	draw_ray(t_cube *cube, int screen_x);
void	raycasting(t_cube *cube);

// draw wall functions
void	draw_wall(t_cube *cube, int screen_x);

// check wall side functions
void	check_wall_side(t_cube *cube, int *tex_height, int *tex_width);

// check functions
bool	check_wall_tile(t_cube *cube, int p_new_position_x, int p_new_position_y, int a);

// texture functions
t_img	*load_textures(t_cube *cube, char *path);
int		get_texture_pixel(t_img *img, int x, int y);

// check_maps.c
char *create_map_path(char *map_name);
int find_map(int ac, char **argv);
int load_map(int ac, char **argv, t_cube *cube);

// parsing.c
int		check_name(char **argv);
int check_arg(int ac);
int parse_rgb(char *line);
int parse_texture_line(char *line, t_cube *cube);

//parsing2.c
int parse_map_file(int fd, t_cube *cube);
int process_texture_line(char *line, t_cube *cube, int *texture_count);
int validate_textures_complete(int texture_count);

//parsing3.c
int parse_map_line(char *line, t_cube *cube, int row);
void	set_player_position(t_cube *cube, char direction, int row, int col);
int process_line(char *line, t_cube *cube, int *textures_done, int *texture_count, int *map_row);
int process_map_line(char *line, t_cube *cube, int *map_row);

//parsing4.c
int check_xpm_extension(char *texture);
int check_texture_file(char *path);
int validate_textures(t_map *map);
int validate_map_content(t_cube *cube);
int validate_element_order(int fd);

//parsing5.c
int is_texture_element(char c);
int	is_player_rotation(char c);
int is_map_element(char c);
int process_order_line(char *line, int *texture_count, int *map_started);
void init_texture_counters(int *no, int *so, int *we, int *ea);
void init_color_counters(int *f, int *c);

//parsing6.c
int check_duplicates(int fd);
int count_elements(char *line, int *no, int *so, int *we, int *ea, int *f, int *c);
int check_and_increment(int *count, char *element_name);
int check_map_before_textures(int texture_count, char first_char);
int check_map_characters(char *line);

// parsing_main.c
int	parse_game(int ac, char **argv, t_cube *cube);

#endif
