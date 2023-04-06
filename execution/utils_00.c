/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_00.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidhmmou <hidhmmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 17:42:58 by hidhmmou          #+#    #+#             */
/*   Updated: 2023/04/05 02:49:02 by hidhmmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"


void	get_wall_color(t_cub3d *cub3d)
{
	if (cub3d->draw->wallHitContent == 'D')
		cub3d->draw->color = 0xFF5733;
	else if (cub3d->map->player.direction == NO)
		cub3d->draw->color = 23212;
	else if (cub3d->map->player.direction == SO)
		cub3d->draw->color = 54321;
	else if (cub3d->map->player.direction == EA)
		cub3d->draw->color = 3214;
	else if (cub3d->map->player.direction == WE)
		cub3d->draw->color = 34614;
}

void check_direction(t_cub3d *cub3d)
{
	if (cub3d->map->player.direction == VERTICAL && cub3d->draw->wallHitX - cub3d->map->player.x > 0)
		cub3d->map->player.direction = EA;
	if (cub3d->map->player.direction == VERTICAL && cub3d->draw->wallHitX - cub3d->map->player.x < 0)
		cub3d->map->player.direction = WE;
	if (cub3d->map->player.direction == HORIZONTAL && cub3d->draw->wallHitY - cub3d->map->player.y < 0)
		cub3d->map->player.direction = NO;
	if (cub3d->map->player.direction == HORIZONTAL && cub3d->draw->wallHitY - cub3d->map->player.y > 0)
		cub3d->map->player.direction = SO;
	get_wall_color(cub3d);
}

void put_player(t_cub3d *cub3d, float *tmp)
{
	my_mlx_pixel_put(cub3d->img_2d, tmp[0] , tmp[1], 0x00FF00);
	my_mlx_pixel_put(cub3d->img_2d, tmp[0], tmp[1] - 1, 0x00FF00);
	my_mlx_pixel_put(cub3d->img_2d, tmp[0], tmp[1] + 1, 0x00FF00);
	my_mlx_pixel_put(cub3d->img_2d, tmp[0], tmp[1] - 2, 0x00FF00);
	my_mlx_pixel_put(cub3d->img_2d, tmp[0], tmp[1] + 2, 0x00FF00);
	my_mlx_pixel_put(cub3d->img_2d, tmp[0] - 1, tmp[1], 0x00FF00);
	my_mlx_pixel_put(cub3d->img_2d, tmp[0] + 1, tmp[1], 0x00FF00);
	my_mlx_pixel_put(cub3d->img_2d, tmp[0] - 2, tmp[1], 0x00FF00);
	my_mlx_pixel_put(cub3d->img_2d, tmp[0] + 2, tmp[1], 0x00FF00);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}


float to_radian(float angle)
{
	return (angle * (M_PI / 180));
}

int in_range(int x, int y, int x1, int y1, int x2, int y2)
{
	if (x >= x1 && x <= x2 && y >= y1 && y <= y2)
		return (1);
	return (0);
}

void	put_xpm_file_to_window(t_cub3d *cub3d, char *path, int x, int y)
{
	t_img img;

	img.img = mlx_xpm_file_to_image(cub3d->mlx, path, &img.width, &img.height);
	mlx_put_image_to_window(cub3d->mlx, cub3d->win, img.img, x, y);
	mlx_destroy_image(cub3d->mlx, img.img);
}

void img_transparent(t_cub3d *cub3d, t_img *img)
{
	int		i;
	int		j;
	int		color;

	i = 0;
	while (i < HEIGHT)
	{
		j = -1;
		while (++j < WIDTH)
			my_mlx_pixel_put(img, j, i, 0xFFFFFFFF);
		i++;
	}
}
void	cast_mid_ray(t_cub3d *cub3d)
{
	float	pixel_x;
	float	pixel_y;

	pixel_x = cub3d->map->player.x;
	pixel_y = cub3d->map->player.y;
	cub3d->draw->ray_angle = cub3d->map->player.angle;
	cub3d->facing_open_door = 0;
	cub3d->facing_close_door = 0;
	init_draw(cub3d);
	int i = 0;
	while (i++ < 700)
	{
		pixel_x -= cub3d->draw->increment_x;
		pixel_y -= cub3d->draw->increment_y;
		cub3d->middle_ray_block = &cub3d->map->square_map[(int)pixel_y / SIZE][(int)pixel_x / SIZE];
		if (is_door(*cub3d->middle_ray_block) == 1)
		{
			cub3d->facing_close_door = 1;
			break ;
		}
		else if (is_door(*cub3d->middle_ray_block) == 2)
		{
			cub3d->facing_open_door = 1;
			break ;
		}
		else if (is_wall(*cub3d->middle_ray_block))
			break ;
	}
}