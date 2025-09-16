/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:44:05 by aakerblo          #+#    #+#             */
/*   Updated: 2025/09/16 17:12:02 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "libft.h"
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <limits.h>
# include <X11/Xlib.h>
# include <X11/extensions/Xfixes.h>

# ifdef __linux__
#  include <X11/keysym.h>
# elif __APPLE__
#  define XK_w 13      // W
#  define XK_a 0       // A
#  define XK_s 1       // S
#  define XK_d 2       // D
#  define XK_e 14      // E
#  define XK_Escape 53 // Escape
#  define XK_Left 123  // Left Arrow
#  define XK_Right 124 // Right Arrow
# endif

# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define YELLOW 0xFFFF00
# define CYAN 0x00FFFF
# define MAGENTA 0xFF00FF
# define WHITE 0xFFFFFF
# define BLACK 0x000000
# define SHADOW_GREEN 0x00BB00
# define SHADOW_RED 0xBB0000
# define SHADOW_MAGENTA 0xBB00BB
# define PSYCH_RED 0xFF0066
# define PSYCH_BLUE 0x0066FF
# define PSYCH_GREEN 0x66FF00
# define PSYCH_PURPLE 0xCC00FF
# define PSYCH_YELLOW 0xFFFF33
# define PSYCH_ORANGE 0xFF9933
# define PSYCH_TEAL 0x33FFCC
# define PSYCH_MAGENTA 0xFF33CC
# define DARK_RED 0x550000
# define DARK_GREEN 0x005500
# define DARK_BLUE 0x000055
# define DARK_YELLOW 0x555500
# define DARK_CYAN 0x005555
# define DARK_MAGENTA 0x550055
# define DARK_PINK 0x550033

# define WIDTH 800
# define HEIGHT 800
# define MAP_X 200
# define MAP_Y 200
# define PLAYERSIZE 10
# define PLAYERSPEED 1
# define TURNSPEED 1.570796327
# define MOUSE_SENSITIVITY 0.002
# define MINIMAP_SIZE 200
# define PAINTINGVALUE 10
# define DEBUG 0
# define TILESIZE 64
# define DOOR_TEXTURE "assets/someyt_5x5.xpm"
# define SOMEYT_INTERVAL 1000

# define LEFT 1
# define RIGHT 2
# define UP 3
# define DOWN 4

# define KEY_PRESS 2
# define KEY_RELEASE 3
# define MOTION_NOTIFY 6
# define DESTROY_WINDOW 17
# define PLAYERDIRECTIONSIZE 2000
# define FOV 0.6

# define PI 3.141592653
# define RADIAN 0.017453293

typedef struct s_new_p
{
	int				p_new_position_x;
	int				p_new_position_y;
}					t_new_p;

typedef struct s_parse
{
	int				textures_done;
	int				map_row;
	int				texture_count;
}					t_parse;

typedef struct s_count
{
	int				no_count;
	int				so_count;
	int				we_count;
	int				ea_count;
	int				f_count;
	int				c_count;
}					t_count;

typedef struct s_door
{
	int				door_x;
	int				door_y;
	bool			is_open;
	struct s_door	*next;
}					t_door;

typedef struct s_tex
{
	int				tex_x;
	int				tex_y;
	double			tex_pos;
	int				tex_height;
	int				tex_width;
	double			visual_tex_height;
	double			tex_offset;
	double			step;
}					t_tex;

typedef struct s_img
{
	void			*img_addr;
	char			*pixel_addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				width;
	int				height;
}					t_img;

typedef struct s_coord
{
	double			start_x;
	double			start_y;
	double			ray_dir_x;
	double			ray_dir_y;
	int				step_x;
	int				step_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	int				map_x;
	int				map_y;
	double			pos_x;
	double			pos_y;
	double			wall_distance;
	double			perp_wall_dist;
	int				side;
	t_img			*side_detailed;
}					t_coord;

typedef struct s_keys
{
	int				w_pressed;
	int				a_pressed;
	int				s_pressed;
	int				d_pressed;
	int				e_pressed;
	int				esc_pressed;
	int				left_pressed;
	int				right_pressed;
}					t_keys;

typedef struct s_someyt
{
	bool			has_anim_wall;
	bool			is_anim_wall;
	double			start_time;
	double			new_time;
	t_img			*current_tex;
	t_img			*tex_1;
	t_img			*tex_2;
	t_img			*tex_3;
	t_img			*tex_4;
}					t_someyt;

typedef struct s_map
{
	int				**map;
	int				**accessibility_map;
	int				width;
	int				height;
	int				nbr_doors;
	t_img			*no;
	t_img			*so;
	t_img			*we;
	t_img			*ea;
	t_img			*door;
	int				floor;
	int				ceiling;
}					t_map;

typedef struct s_player
{
	int				position_x;
	int				position_y;
	double			precise_x;
	double			precise_y;
	double			error_x;
	double			error_y;
	double			delta_x;
	double			delta_y;
	int				square_x;
	int				square_y;
	double			cam_x;
	double			cam_y;
	int				height;
	double			distance;
	double			player_direction;
}					t_player;

typedef struct s_cube
{
	void			*mlx;
	void			*mlx_win;
	int				color;
	t_player		p;
	t_img			img;
	t_map			map;
	t_keys			keys;
	t_coord			coord;
	t_tex			tex;
	t_door			*door;
	t_someyt		someyt;
}					t_cube;

// accessibility_map.c
int					**create_accessibility_map(t_cube *cube);
void				free_accessibility_map(int **accessibility_map, int height);

// allocate_map.c
int					allocate_map_from_file(char *filename, t_cube *cube);

// check_maps.c
int					load_map(int ac, char **argv, t_cube *cube);

// check_open_walls.c
int					check_open_walls(int **visited, t_map *map);

// check_wall_side.c
void				check_wall_side(t_cube *cube, int *tex_height, int *tex_width);

// check.c
bool				check_wall_tile(t_cube *cube, int new_x, int new_y, int a);

// cleanup.c
int					cleanup(t_cube *cube);

// door.c
t_door				*find_door(t_cube *cube);
bool				is_door_open(t_cube *cube);
void				parse_door(t_cube *cube, int row, int col);
int					validate_doors(t_cube *cube);

// draw_rays.c
void				draw_ray(t_cube *cube, int screen_x);

// draw_wall.c
void				draw_wall(t_cube *cube, int screen_x);

// draw.c
void				draw_pixel(t_img *img, int x, int y, int color);
double				scale(double value, double origin_max,
						double target_min, double target_max);
void				render_image(t_cube *cube);

// flood_fill.c
int					is_valid_position(int x, int y, t_map *map);
void				flood_fill_recursive(t_map *map_struct, int **visited,
						int x, int y);

// flood_fill2.c
int					validate_map_boundaries(t_cube *cube);

// flood_fill3.c
int					check_player_on_external_wall(t_map *map, int player_x, int player_y);

// get_time.c
double				get_delta_time(void);
double				get_total_time(void);

// handle_door.c
void				handle_door(t_cube *cube);

// handle_door2.c
int					get_map_value(t_cube *cube, int x, int y);
void				open_door(t_cube *cube, int tile_x, int tile_y);
void				close_door(t_cube *cube, int tile_x, int tile_y);
int					*get_key_pressed(void);

// hooks.c
int					key_press_handler(int keysym, t_cube *cube);
int					key_release_handler(int keysym, t_cube *cube);
int					mouse_handler(int x, int y, t_cube *cube);
int					game_loop(t_cube *cube);

// init.c
void				init_visited_map(int **visited, t_map *map);
void				init_image(t_cube *cube);
void				init_keys(t_cube *cube);
void				init_hooks(t_cube *cube);
void				init_cube(t_cube *cube);

// minimap.c
void				draw_minimap(t_cube *cube);

// parse_dimentions.c
int					check_width(int fd);
int					check_height(int fd);

// parse_helpers.c
void				finish_file_reading(int fd);
void				assign_max_width(char *line, int *max_width);
int					handle_empty_line(char *line);
int					check_arg(int ac);
int					check_name(char **argv);

// parse_main.c
int					process_texture_line(char *line, t_cube *cube, int *texture_count);
int					validate_textures_complete(int texture_count);
int					parse_map_file(int fd, t_cube *cube, char *filename);
int					parse_game(int ac, char **argv, t_cube *cube);

// parse_map_content.c
int					process_order_line(char *line, int *texture_count, int *map_started);
int					process_line(char *line, t_cube *cube, char *filename, t_parse *parse);

// parse_textures.c
int					parse_texture_line(char *line, t_cube *cube);

// parse_utils.c
int					is_texture_element(char c);
int					is_player_rotation(char c);
int					is_map_element(char c);
void				set_player_position(t_cube *cube, char direction, int row, int col);
void				init_counters(t_count *counter);

// parse_validation.c
int					check_map_before_textures(int texture_count, char first_char);
int					check_duplicates(int fd);
int					check_map_characters(char *line);

// raycasting.c
void				raycasting(t_cube *cube);

// someyt.c
t_img				*handle_someyt(t_cube *cube);
void				init_someyt(t_cube *cube, int row, int col);
// textures.c
t_img				*load_textures(t_cube *cube, char *path_plus_newline);
int					get_texture_pixel(t_img *img, int x, int y);

// update_player.c
void				update_player_position(t_cube *cube, int dir);

// validate_map.c
int					check_xpm_extension(char *texture);
int					check_texture_file(char *path);
int					validate_textures(t_map *map);
int					validate_element_order(int fd);
int					validate_map_content(t_cube *cube);

#endif
