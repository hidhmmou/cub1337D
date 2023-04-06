/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidhmmou <hidhmmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 17:36:04 by hidhmmou          #+#    #+#             */
/*   Updated: 2023/04/06 03:42:25 by hidhmmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

int is_wall(char c)
{
	return (c == '1' || c == 'D');
}

int is_door(char c)
{
	if (c == 'D')
		return (1);
	if (c == 'X')
		return (2);
	return (0);
}

int	check_hit_wall(t_cub3d *cub3d, float pixel_y, float pixel_x, int size)
{
	if (is_wall(cub3d->map->square_map[(int)pixel_y / size][(int)pixel_x / size]))
		return (1);
	if (is_wall(cub3d->map->square_map[((int)pixel_y + 1) / size][(int)pixel_x / size])
		&& is_wall(cub3d->map->square_map[(int)pixel_y / size][((int)pixel_x + 1) / size]))
		return (1);
	if (is_wall(cub3d->map->square_map[((int)pixel_y - 1) / size][(int)pixel_x / size])
		&& is_wall(cub3d->map->square_map[(int)pixel_y / size][((int)pixel_x + 1) / size]))
		return (1);
	return (0);
}

void	init_draw(t_cub3d *cub3d)
{
	cub3d->draw->radiant = to_radian(cub3d->draw->ray_angle);
	cub3d->draw->dx = 500 * cos(cub3d->draw->radiant);
	cub3d->draw->dy = 500 * sin(cub3d->draw->radiant);
	if (abs(cub3d->draw->dx) > abs(cub3d->draw->dy))
		cub3d->draw->pixel_nbr = abs(cub3d->draw->dx);
	else
		cub3d->draw->pixel_nbr = abs(cub3d->draw->dy);
	cub3d->draw->increment_x = cub3d->draw->dx / (float)cub3d->draw->pixel_nbr;
	cub3d->draw->increment_y = cub3d->draw->dy / (float)cub3d->draw->pixel_nbr;
	cub3d->draw->ray_angle += 60.0 / WIDTH;
}

static void draw_initializer(t_cub3d *cub3d)
{
	cub3d->draw->size = cub3d->draw->wall_height / SIZE;
	cub3d->draw->texture_pos = 0;
	cub3d->draw->texture_step = 0;
	if (cub3d->draw->draw_end == HEIGHT - 1)
		cub3d->draw->texture_pos = (cub3d->draw->wall_height - HEIGHT) / 2;
}

int	get_pexel_from_img(t_img *img, int x, int y)
{
	char	*dst;

	if (x >= img->width || x < 0 || y >= img->height || y < 0)
		return (-1);
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

static int get_color(t_cub3d *cub3d, int i, int my, float size)
{
	int	x;
	int	y;

	if (cub3d->ray_hit_direction)
	{
		x = (int)cub3d->draw->wallHitY % SIZE;
		y = (i + my) / size;
		if (cub3d->draw->wallHitContent == 'D')
			return (get_pexel_from_img(&cub3d->textures[DOOR], x, y));
		if (cub3d->draw->wallHitContent == 'X')
			return (get_pexel_from_img(&cub3d->textures[O_DOOR], x, y));
		if (cub3d->map->player.direction == WE)
			return (get_pexel_from_img(&cub3d->textures[WE] , x, y));
		return (get_pexel_from_img(&cub3d->textures[EA], x, y));
	}
	else
	{
		x = (int)cub3d->draw->wallHitX % SIZE;
		y = (i + my) / size;
		if (cub3d->draw->wallHitContent == 'D')
			return (get_pexel_from_img(&cub3d->textures[DOOR], x, y));
		if (cub3d->draw->wallHitContent == 'X')
			return (get_pexel_from_img(&cub3d->textures[O_DOOR], x, y));
		if (cub3d->map->player.direction == NO)
			return (get_pexel_from_img(&cub3d->textures[NO], x, y));
		return (get_pexel_from_img(&cub3d->textures[SO], x, y));
	}
	return (0);
}

void draw_wall(t_cub3d *cub3d)
{
	int 	i;
	float	size;
	int		m;
	int		n;
	int		my;

	i = -1;
	size = cub3d->draw->wall_height / SIZE;
	m = 0;
	n = 0;
	my = 0;
	if (cub3d->draw->draw_end == HEIGHT - 1)
		my = (cub3d->draw->wall_height - HEIGHT) / 2;
	//draw_initializer(cub3d);
	while (++i < cub3d->draw->draw_start)
		my_mlx_pixel_put(cub3d->img, cub3d->draw->x, i, shader(rgb_to_int(*cub3d->map->ciel_color), ((HEIGHT / 2.0) - i) * 100.0 / (HEIGHT / 2.0)));
	while (i < cub3d->draw->draw_end)
	{
		cub3d->draw->color = get_color(cub3d, n, my, size);
		my_mlx_pixel_put(cub3d->img, cub3d->draw->x, i++, shader(cub3d->draw->color, cub3d->draw->wall_height * 100 / HEIGHT));
		n++;
	}
	i--;
	while (++i < HEIGHT)
		my_mlx_pixel_put(cub3d->img, cub3d->draw->x, i, shader(rgb_to_int(*cub3d->map->floor_color), ((HEIGHT / 2.0) + i - HEIGHT) * 100.0 / (HEIGHT / 2.0)));
	cub3d->draw->x++;
}

void calc(t_cub3d *cub3d)
{
	cub3d->draw->real_distance = intersect_dist(cub3d);
	cub3d->draw->distance = cub3d->draw->real_distance * (cos(cub3d->draw->radiant - to_radian(cub3d->map->player.angle)));
	cub3d->draw->distance_to_player = (float)((WIDTH / 2.0) / tan(60.0 / 2.0 * PI / 180.0));
	cub3d->draw->wall_height = (float)((float)SIZE / cub3d->draw->distance ) * cub3d->draw->distance_to_player;
    cub3d->draw->draw_start = (float)(HEIGHT / 2.0 - cub3d->draw->wall_height / 2.0);
    cub3d->draw->draw_end = (float)cub3d->draw->draw_start + (float)cub3d->draw->wall_height;
    if (cub3d->draw->draw_start < 0)
        cub3d->draw->draw_start = 0;
    if (cub3d->draw->draw_end >= HEIGHT)
        cub3d->draw->draw_end = HEIGHT - 1;
}

void	cast_ray(t_cub3d *cub3d)
{
	init_draw(cub3d);
	calc(cub3d);
	check_direction(cub3d);
	if (cub3d->draw->ray_angle == cub3d->map->player.angle)
	{
		cast_mid_ray(cub3d);
		cub3d->draw->color = 0;
	}
	draw_wall(cub3d);
}

void	render_scene(t_cub3d *cub3d)
{
	int 	i;

	i = -1;
	cub3d->draw->x = 0;
	cub3d->draw->ray_angle = cub3d->map->player.angle - 30;
	while (++i <= WIDTH)
		cast_ray(cub3d);
	mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->img->img, 0, 0);
	if (cub3d->weapon == 1)
		mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->img_weapon->img, WIDTH / 2 - WEAPON_W / 2, HEIGHT - WEAPON_H);
	show_2d_map(cub3d);
}
