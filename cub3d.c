/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidhmmou <hidhmmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:05:32 by hidhmmou          #+#    #+#             */
/*   Updated: 2023/03/31 01:13:16 by hidhmmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/parsing.h"
#include "includes/execution.h"

void	parsing(t_cub3d **cub3d, char **av, int ac)
{
	if (ac != 2)
		ft_error("Usage : ./cub3d path/to/map", NULL);
	pre_check_map(av[1]);
	cub3d_init(cub3d);
	fill_content(av[1], *cub3d);
	check_content(*cub3d);
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

void	executing(t_cub3d *cub3d)
{
	cub3d->draw->x = WIDTH;
	cub3d->draw->ray_angle = cub3d->map->player.angle - 30;
	cub3d->win_height = --cub3d->map->len * SIZE;
	cub3d->win_width = --cub3d->map->max_len * SIZE;
	cub3d->minimap = 1;
	cub3d->mouse->shown = 1;
	cub3d->weapon = -1;
	cub3d->map->minimap_size = SIZE_2D;
	cub3d->mlx = mlx_init();
	cub3d->win = mlx_new_window(cub3d->mlx, WIDTH, HEIGHT, "Cub1337D");
	cub3d->img->img = mlx_new_image(cub3d->mlx, WIDTH, HEIGHT);
	cub3d->img->addr = mlx_get_data_addr(cub3d->img->img, &cub3d->img->bits_per_pixel, &cub3d->img->line_length, &cub3d->img->endian);
	cub3d->img_2d->img = mlx_new_image(cub3d->mlx, WIDTH, HEIGHT);
	cub3d->img_2d->addr = mlx_get_data_addr(cub3d->img_2d->img, &cub3d->img_2d->bits_per_pixel, &cub3d->img_2d->line_length, &cub3d->img_2d->endian);
	cub3d->img_weapon->img = mlx_new_image(cub3d->mlx, WIDTH, HEIGHT);
	cub3d->img_weapon->addr = mlx_get_data_addr(cub3d->img_weapon->img, &cub3d->img_weapon->bits_per_pixel, &cub3d->img_weapon->line_length, &cub3d->img_weapon->endian);
	img_transparent(cub3d, cub3d->img_weapon);
}

int mouse_move(int x, int y, t_cub3d *cub3d)
{
	if (!cub3d->start || cub3d->mouse->shown == 1)
		return (1);
	if (cub3d->mouse->x != x)
	{
		cub3d->map->player.angle -= (x - cub3d->mouse->x) * 0.1;
		cub3d->mouse->x = x;
		if (cub3d->mouse->x >= WIDTH || cub3d->mouse->x <= 0)
		{
			mlx_mouse_move(cub3d->win, WIDTH / 2, HEIGHT / 2);
			cub3d->mouse->x = WIDTH / 2;
		}
		mlx_mouse_move(cub3d->win, cub3d->mouse->x, HEIGHT / 2);
		cub3d->change = 1;
	}
	else
		cub3d->change = 0;
	return (0);
}

int	main(int ac, char *av[])
{
	t_cub3d	*cub3d;

	parsing(&cub3d, av, ac);
	executing(cub3d);
	put_xpm_file_to_window(cub3d, "textures/intro.xpm", 0, 0);
	//put_xpm_file_to_window(cub3d, "0.xpm", WIDTH / 2 - 200, HEIGHT - 487);
	mlx_hook(cub3d->win, 2, 0, &press, cub3d);
	mlx_hook(cub3d->win, 3, 0, &release, cub3d);
	mlx_hook(cub3d->win, 6, 0, &mouse_move, cub3d);
	mlx_loop_hook(cub3d->mlx, &loop, cub3d);
	mlx_mouse_hook(cub3d->win, &mouse_press, cub3d);
	mlx_hook(cub3d->win, 17, 0, &close_window, cub3d);
	mlx_loop(cub3d->mlx);
	return (0);
}
