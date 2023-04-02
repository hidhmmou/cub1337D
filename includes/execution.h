/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidhmmou <hidhmmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 10:34:46 by ramhouch          #+#    #+#             */
/*   Updated: 2023/04/02 01:15:31 by hidhmmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# include <mlx.h>
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include "../includes/parsing.h"

int     press(int key, t_cub3d *cub3d);
int     close_window(t_cub3d *cub3d);
void	render_map_2d(t_cub3d *cub3d);
void	render_player(t_cub3d *cub3d);
void    put_player(t_cub3d *cub3d, float *tmp);
void	cast_mid_ray(t_cub3d *cub3d);
int     check_hit_wall(t_cub3d *cub3d, float pixel_y, float pixel_x, int size);
void	init_draw(t_cub3d *cub3d);
int 	move_up(t_cub3d *cub3d);
int 	move_down(t_cub3d *cub3d);
int 	move_left(t_cub3d *cub3d);
int 	move_right(t_cub3d *cub3d);
void    check_direction(t_cub3d *cub3d);
void    img_transparent(t_cub3d *cub3d, t_img *img);
int     shader(int color, float distance);
void    minimap(int button, int x, int y, t_cub3d *cub3d);
int     mouse_press(int button, int x, int y, t_cub3d *cub3d);
int     in_range(int x, int y, int x1, int y1, int x2, int y2);
void    press_start(int button, int x, int y, t_cub3d *cub3d);
void	put_xpm_file_to_window(t_cub3d *cub3d, char *path, int x, int y);
int     mlx_mouse_hide();
int     mlx_mouse_show();
int     mlx_mouse_move();
float   intersect_dist(t_cub3d *cub3d);
int     mouse_move(int x, int y, t_cub3d *cub3d);
void    img_transparent(t_cub3d *cub3d, t_img *img);
float   normligize_angle(float angle);
#endif
