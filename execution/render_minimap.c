/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidhmmou <hidhmmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:42:34 by hidhmmou          #+#    #+#             */
/*   Updated: 2023/04/06 05:09:32 by hidhmmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

int get_color(char c)
{
	if (c == 'K' || c == ' ')
		return (0xFF4392F1);
	if (c == '1')
		return (0x002C54);
	if (c == 'D')
		return (0x9992F1);
	if (c == '0' || in_set(c, "NSWEX"))
		return (0x4CFF5733);
	if (c == '\n')
		return (0xFF00FF00);
	return (0);
}
// light gray in hex 
void	put_pixel_square(t_cub3d *cub3d, int x, int y, int color)
{
	int		i;
	int		j;

	i = 0;
	while (i < cub3d->map->minimap_size)
	{
		j = -1;
		while (++j < cub3d->map->minimap_size)
			my_mlx_pixel_put(cub3d->img_2d, y + j, x + i, color);
		i++;
	}
	j = -1;
}


void render_view(t_cub3d *cub3d, int is_mid)
{
	float	pixel_x;
	float	pixel_y;
	float	tmp[2];

	pixel_x = (float)cub3d->map->player.x / SIZE * cub3d->map->minimap_size;
	pixel_y = (float)cub3d->map->player.y / SIZE * cub3d->map->minimap_size;
	tmp[0] = pixel_x;
	tmp[1] = pixel_y;
	init_draw(cub3d);
	while (!check_hit_wall(cub3d, pixel_y, pixel_x, cub3d->map->minimap_size))
	{
		if (!is_mid)
			my_mlx_pixel_put(cub3d->img_2d, pixel_x, pixel_y, 0x44002C54);
		else
			my_mlx_pixel_put(cub3d->img_2d, pixel_x, pixel_y, 0x00FF00);
		pixel_x += cub3d->draw->increment_x;
		pixel_y += cub3d->draw->increment_y;
	}
	put_player(cub3d, tmp);
	my_mlx_pixel_put(cub3d->img_2d, pixel_x, pixel_y, 0x00FF00);
	my_mlx_pixel_put(cub3d->img_2d, pixel_x - 1, pixel_y - 1, 0x00FF00);
}

// dark gray in hex 0x2C54

void	render_background(t_cub3d *cub3d)
{
	int	i;
	int	j;
	int x;
	int y;

	i = 0;
	x = 0;
	y = 0;
	while (cub3d->map->square_map[i])
	{
		j = 0;
		y = 0;
		while (cub3d->map->square_map[i][j])
		{
			if (cub3d->map->square_map[i][j])
				put_pixel_square(cub3d, x, y, get_color(cub3d->map->square_map[i][j]));
			j++;
			y += cub3d->map->minimap_size;
		}
		i++;
		x += cub3d->map->minimap_size;
	}
}

void	erase_minimap(t_cub3d *cub3d)
{
	int x;
	int y;

	x = 99 + cub3d->map->player.x / (float)SIZE * (float)cub3d->map->minimap_size;
	while (++x < WIDTH)
	{
		y = -1;
		while (++y < HEIGHT)
			my_mlx_pixel_put(cub3d->img_2d, x, y, 0xFFFF00FF);
	}
	x = -1;
	while (++x < WIDTH)
	{
		y = 99 + cub3d->map->player.y / (float)SIZE * (float)cub3d->map->minimap_size;
		while (++y < HEIGHT)
			my_mlx_pixel_put(cub3d->img_2d, x, y, 0xFFFF00FF);
	}
}

void show_2d_map(t_cub3d *cub3d)
{
	int x;
	int y;

	if (cub3d->minimap > 0)
	{
		x = 100 - cub3d->map->player.x / (float)SIZE * (float)cub3d->map->minimap_size;
		y = 100 - cub3d->map->player.y / (float)SIZE * (float)cub3d->map->minimap_size;
		erase_minimap(cub3d);
		mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->img_2d->img,  x, y);
		return ;
	}
	x = WIDTH / 2 - cub3d->map->minimap_size * cub3d->map->max_len / 2;
	y = HEIGHT / 2 - cub3d->map->minimap_size * cub3d->map->len / 2;
	mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->img_2d->img, x, y);
	put_xpm_file_to_window(cub3d, "textures/back.xpm", 32, 32);
}

void	mini_map(t_cub3d *cub3d)
{
	int i;
	int width;
	int height;

	i = 0;
	img_transparent(cub3d, cub3d->img_2d);
	if (cub3d->minimap > 0)
		cub3d->map->minimap_size = SIZE_2D;
	else
		cub3d->map->minimap_size = MIN(WIDTH / cub3d->map->max_len, HEIGHT / cub3d->map->len);
	render_background(cub3d);
	cub3d->draw->ray_angle = cub3d->map->player.angle - 30;
	cub3d->draw->ray_angle += 180;
	while (++i <= WIDTH)
		render_view(cub3d, 0);
	cub3d->draw->ray_angle = cub3d->map->player.angle;
	cub3d->draw->ray_angle += 180;
	render_view(cub3d, 1);
	 my_mlx_pixel_put(cub3d->img_2d, cub3d->map->player.x, cub3d->map->player.y, 0x00FF00);
	//cub3d->map->player.img = mlx_xpm_file_to_image(cub3d->mlx, "textures/player.xpm", &width, &height);
	//mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->map->player.img, 0, 0);
}

void *animate_torch(void *param)
{
	int i = 0;
	char *tmp;
	char *path;
	t_cub3d *cub3d;
	
	cub3d = (t_cub3d *)param;
	while (i <= 5)
	{
		++cub3d->change;
		tmp = ft_strjoin("textures/torch/", ft_itoa(i));
		path = ft_strjoin(tmp, ".xpm");
		cub3d->torch->img = mlx_xpm_file_to_image(cub3d->mlx, path, &cub3d->torch->width, &cub3d->torch->height);
		usleep(1500);
		free(tmp);
		free(path);
		i++;
		if (i == 6)
			i = 0;
	}
	return (NULL);
}

void	render(t_cub3d *cub3d)
{
	mlx_clear_window(cub3d->mlx, cub3d->win);
	mini_map(cub3d);
	render_scene(cub3d);
	if (cub3d->weapon == -1 && cub3d->minimap == 1)
		mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->torch->img, WIDTH / 2, 0);
}
