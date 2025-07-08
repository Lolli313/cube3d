/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:44:05 by aakerblo          #+#    #+#             */
/*   Updated: 2025/07/08 11:38:23 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <stdlib.h>
# include <stdio.h>
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

typedef struct s_map
{
	int		map[8][8];
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
}				t_img;

typedef struct s_cube
{
	void	*mlx;
	void	*mlx_win;
	int		color;
	t_img	img;
	t_map	map;
}			t_cube;

#endif