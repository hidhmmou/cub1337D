/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_00.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidhmmou <hidhmmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 17:42:58 by hidhmmou          #+#    #+#             */
/*   Updated: 2023/04/01 21:40:49 by hidhmmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"


void	get_wall_color(t_cub3d *cub3d, float y, float x)
{
	if (cub3d->map->player.direction == NO)
		cub3d->draw->color = 23212;
	if (cub3d->map->player.direction == SO)
		cub3d->draw->color = 54321;
	if (cub3d->map->player.direction == EA)
		cub3d->draw->color = 3214;
	if (cub3d->map->player.direction == WE)
		cub3d->draw->color = 34614;
}

void check_direction(t_cub3d *cub3d, float y, float x, float *tmp)
{
	if (cub3d->map->player.direction == VERTICAL && x - tmp[0] > 0)
		cub3d->map->player.direction = EA;
	if (cub3d->map->player.direction == VERTICAL && x - tmp[0] < 0)
		cub3d->map->player.direction = WE;
	if (cub3d->map->player.direction == HORIZONTAL && y - tmp[1] < 0)
		cub3d->map->player.direction = NO;
	if (cub3d->map->player.direction == HORIZONTAL && y - tmp[1] > 0)
		cub3d->map->player.direction = SO;
	get_wall_color(cub3d, y, x);
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

void	cast_mid_ray(t_cub3d *cub3d)
{
	float	pixel_x;
	float	pixel_y;
	float	tmp[2];

	pixel_x = cub3d->map->player.x;
	pixel_y = cub3d->map->player.y;
	tmp[0] = pixel_x;
	tmp[1] = pixel_y;
	cub3d->draw->ray_angle = cub3d->map->player.angle;
	init_draw(cub3d);
	while (1)
	{
		pixel_x += cub3d->draw->increment_x;
		if (check_hit_wall(cub3d, pixel_y, pixel_x, SIZE))
		{
			cub3d->map->player.direction = VERTICAL;
			check_direction(cub3d, pixel_y, pixel_x, tmp);
			break ;
		}
		pixel_y += cub3d->draw->increment_y;
		if (check_hit_wall(cub3d, pixel_y, pixel_x, SIZE))
		{
			cub3d->map->player.direction = HORIZONTAL;
			check_direction(cub3d, pixel_y, pixel_x, tmp);
			break ;
		}
	}
	cub3d->draw->distance = (float)sqrt(pow(pixel_x - tmp[0], 2) + pow(pixel_y - tmp[1], 2));
    cub3d->draw->wall_height = (float)HEIGHT / cub3d->draw->distance;
	cub3d->draw->wall_height = (float)pow(cub3d->draw->wall_height, -1) * 7000;
    cub3d->draw->draw_start = (float)(-cub3d->draw->wall_height / 2.0 + HEIGHT / 2.0);
    cub3d->draw->draw_end = (float)(cub3d->draw->wall_height / 2.0 + HEIGHT / 2.0);
    if (cub3d->draw->draw_start < 0)
        cub3d->draw->draw_start = 0;
    if (cub3d->draw->draw_end >= HEIGHT)
        cub3d->draw->draw_end = HEIGHT - 1;
	cub3d->draw->x--;
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