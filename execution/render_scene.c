/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidhmmou <hidhmmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 17:36:04 by hidhmmou          #+#    #+#             */
/*   Updated: 2023/04/02 02:45:22 by hidhmmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

int is_wall(char c)
{
	return (c == '1');
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

void draw_wall(t_cub3d *cub3d)
{
	int 	i;

	i = -1;
	while (++i < cub3d->draw->draw_start)
		my_mlx_pixel_put(cub3d->img, cub3d->draw->x, i, rgb_to_int(*cub3d->map->ciel_color));
	while (i < cub3d->draw->draw_end)
		my_mlx_pixel_put(cub3d->img, cub3d->draw->x, i++, cub3d->draw->color);
	while (i < HEIGHT)
		my_mlx_pixel_put(cub3d->img, cub3d->draw->x, i++, rgb_to_int(*cub3d->map->floor_color));
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

void	cast_ray(t_cub3d *cub3d, int is_mid)
{
	if (is_mid)
		cub3d->draw->ray_angle = cub3d->map->player.angle;
	init_draw(cub3d);
	calc(cub3d);
	check_direction(cub3d);
	if (is_mid)
		cub3d->draw->color = 0;
	draw_wall(cub3d);
}

void	render_scene(t_cub3d *cub3d)
{
	int 	i;

	i = -1;
	cub3d->draw->x = 0;
	cub3d->draw->ray_angle = cub3d->map->player.angle - 30;
	while (++i <= WIDTH)
	{
		if (i != WIDTH / 2)
			cast_ray(cub3d, 0);
		else
			cast_ray(cub3d, 1);
	}
	mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->img->img, 0, 0);
	if (cub3d->weapon == 1)
		mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->img_weapon->img, WIDTH / 2 - WEAPON_W / 2, HEIGHT - WEAPON_H);
	show_2d_map(cub3d);
}
