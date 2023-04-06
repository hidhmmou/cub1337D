/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidhmmou <hidhmmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:11:07 by hidhmmou          #+#    #+#             */
/*   Updated: 2023/04/06 01:16:46 by hidhmmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <mlx.h>
# include <math.h>
# include <fcntl.h>
# include <pthread.h>
# include "../libft/libft.h"
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define RESET "\033[0m"
/*--keys--*/
# define RIGHT_MOVE 2
# define LEFT_MOVE 0
# define DOWN_MOVE 1
# define UP_MOVE 13
# define RIGHT_ROW 124
# define LEFT_ROW 123
# define TAB 48
# define SPACE 49
# define NUM_1 18
# define CTRL 256
# define SHIFT 257
# define ESC 53
# define OPEN_DOOR 14
# define CLOSE 17
# define HORIZONTAL 0
# define VERTICAL 1
# define PI 3.14159265358979323846264338327950288
# define WIDTH 1280
# define HEIGHT 720
# define FOV 60
# define SIZE 1024
# define SIZE_2D 10
# define SIZE_BIG_2D 20
# define ANGLE_SIZE FOV / WIDTH
# define ROTATE_ANGLE 5
#define MIN(a,b) ((a) < (b) ? (a) : (b))
# define P 3.14159265
# define SPEED 600
# define LEFT_CLICK 1
# define RIGHT_CLICK 2
# define MIDDLE_CLICK 3
# define SCROLL_UP 4
# define SCROLL_DOWN 5
# define WEAPON_H 487
# define WEAPON_W 450
typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;


typedef struct s_draw
{
	float	radiant;
	int		dx;
	int		dy;
	int 	x;
	float	ray_angle;
	float	ray_angle_2d;
	int		pixel_nbr;
	float	increment_x;
	float	increment_y;
	float	distance;
	float	real_distance;
	float	distance_to_player;
	float	wall_height;
	float	draw_start;
	float	draw_end;
	int		color;
	float	wallHitX;
	float	wallHitY;
	int		wallHitContent;
	int		size;
	int		offset;
	int 	texture_step;
	int 	texture_pos;
}	t_draw;

typedef struct s_player
{
	int			x;
	int			y;
	float 		angle;
	float		direction;
}	t_player;
typedef struct s_map
{
	int			rows;
	int			cols;
	t_player	player;
	char		**content;
	char		**check_map;
	char		**square_map;
	char		**map;
	char		*so_texture;
	char		*no_texture;
	char		*ea_texture;
	char		*we_texture;
	char		*f_color;
	char		*c_color;
	t_color		*floor_color;
	t_color		*ciel_color;
	int			empty_nbr;
	size_t		max_len;
	int			len;
	int			minimap_size;
}		t_map;

typedef struct s_img
{
	void		*img;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	char		*addr;
	int			width;
	int			height;
}	t_img;

enum e_texture
{
	NO,
	SO,
	WE,
	EA,
	DOOR
};

enum e_key
{
	W,
	A,
	S,
	D,
	LEFT,
	RIGHT,
	TABB,
	SHIFTT,
};

typedef struct t_mouse
{
	int		x;
	int		y;
	int		shown;
}	t_mouse;

typedef struct s_sound
{
	int		pid;
	int		music_background;
	int		steps_sound;
	int		shoot;
	int		playing_sound;
}	t_sound;

typedef struct s_cub3d
{
	t_img		*img_2d;
	t_img		*img;
	t_img		textures[5];
	t_img		*no_texture;
	t_img		*img_weapon;
	t_map		*map;
	t_draw		*draw;
	t_mouse		*mouse;
	t_sound		*sound;
	int			keys[10];
	void		*mlx;
	void		*win;
	int			win_width;
	int			win_height;
	int			start;
	int			minimap;
	int 		shoot;
	int 		change;
	int 		weapon;
	char		*middle_ray_block;
	int 		facing_close_door;
	int 		facing_open_door;
	int 		pid;
	int			ray_hit_direction;
}	t_cub3d;


void	ft_error(char *message, t_cub3d *cub3d);
void	free_float(char **content);
void	ft_free(t_cub3d *cub3d);
char	*get_next_line(int fd);
void	pre_check_map(char *file);
void	fill_content(char *map_file, t_cub3d *cub3d);
void	check_content(t_cub3d *cub3d);
char	*get_from_file(char **content, char *target);
int		find(char **content, char *target, int flag);
void	get_colors(t_cub3d *cub3d);
void	get_textures(t_cub3d *cub3d);
void	check_textures(char	**content);
void	check_colors(char	**content);
int		get_rgb(int color);
void	get_colors(t_cub3d *cub3d);
int		check_colors_format(char **tab);
void	check_player(t_cub3d *cub3d);
int		in_set(char c, char *set);
int		check_surrounded(t_cub3d *cub3d);
int		check_outsider_floor(t_cub3d *cub3d);
int		rgb_to_int(t_color color);
int		check_floor_outside_1(char **map);
int		check_floor_outside_2(char **map);
int		fast_check(char	*line, int i, int len);
int		in_set(char c, char *set);
int		map_len(char **content);
int		len_float(char **map);
void	ft_func_helper(t_cub3d *cub3d, int x, int y);
void	virus_floor(t_cub3d *cub3d, int x, int y);
void	get_check_map(t_cub3d *cub3d);
void	get_square_map(t_cub3d *cub3d);
void	get_map(t_cub3d *cub3d);
char	**splite_colors(char const *s);
int		check_commas(char *floor, char *ciel);
void	cub3d_init(t_cub3d **cub3d);
int		is_wall(char c);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
int		rotate(int key, t_cub3d *cub3d);
float	to_radian(float angle);
void	press_start(int button, int x, int y, t_cub3d *cub3d);
void	get_wall_color(t_cub3d *cub3d);
int		release(int key, t_cub3d *cub3d);
int		loop(t_cub3d *cub3d);
int		mouse_move(int x, int y, t_cub3d *cub3d);
float 	to_radian(float angle);
int is_door(char c);
#endif