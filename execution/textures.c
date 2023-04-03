/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidhmmou <hidhmmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 03:53:42 by hidhmmou          #+#    #+#             */
/*   Updated: 2023/04/02 18:40:07 by hidhmmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

void init_textures(t_cub3d *cub3d)
{
    cub3d->textures[NO].img = mlx_xpm_file_to_image(cub3d->mlx, cub3d->map->no_texture, &cub3d->textures[NO].width, &cub3d->textures[NO].height);
    cub3d->textures[NO].addr = mlx_get_data_addr(cub3d->textures[NO].img, &cub3d->textures[NO].bits_per_pixel, &cub3d->textures[NO].line_length, &cub3d->textures[NO].endian);
    cub3d->textures[SO].img = mlx_xpm_file_to_image(cub3d->mlx, cub3d->map->so_texture, &cub3d->textures[SO].width, &cub3d->textures[SO].height);
    cub3d->textures[SO].addr = mlx_get_data_addr(cub3d->textures[SO].img, &cub3d->textures[SO].bits_per_pixel, &cub3d->textures[SO].line_length, &cub3d->textures[SO].endian);
    cub3d->textures[WE].img = mlx_xpm_file_to_image(cub3d->mlx, cub3d->map->we_texture, &cub3d->textures[WE].width, &cub3d->textures[WE].height);
    cub3d->textures[WE].addr = mlx_get_data_addr(cub3d->textures[WE].img, &cub3d->textures[WE].bits_per_pixel, &cub3d->textures[WE].line_length, &cub3d->textures[WE].endian);
    cub3d->textures[EA].img = mlx_xpm_file_to_image(cub3d->mlx, cub3d->map->ea_texture, &cub3d->textures[EA].width, &cub3d->textures[EA].height);
    cub3d->textures[EA].addr = mlx_get_data_addr(cub3d->textures[EA].img, &cub3d->textures[EA].bits_per_pixel, &cub3d->textures[EA].line_length, &cub3d->textures[EA].endian);
}

int	get_y(t_cub3d *cub3d, int i, int y)
{
	float   size;
	int     m;
	float	start;
	float	end;

	size = cub3d->draw->wall_height / SIZE;
	start = 0;
	end = size;
	while (1)
	{
		if ((i >= start && i < end )|| end > cub3d->draw->wall_height)
			break ;
		y++;
		start = end;
		end += size;
	}
	return (y);
}

int get_color_from_texture(t_img *texture, int x, int y)
{
    char *dst;

	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0);
    dst = texture->addr + (y * texture->line_length + x * (texture->bits_per_pixel / 8));
    return (*(unsigned int*)dst);
}

int	get_pixel(t_cub3d *cub3d, int i)
{
	int	x;
	int	y;

	if (cub3d->map->player.direction == EA || cub3d->map->player.direction == WE)
	{
		x = (int)cub3d->draw->wallHitX % SIZE;
		y = get_y(cub3d, i, 0);
		if (cub3d->map->player.direction == EA)
			return (get_color_from_texture(&cub3d->textures[EA], x, y));
		return (get_color_from_texture(&cub3d->textures[WE], x, y));
	}
	if (cub3d->map->player.direction == SO || cub3d->map->player.direction == NO)
	{
		x = (int)cub3d->draw->wallHitY % SIZE;
		y = get_y(cub3d, i, 0);
		if (cub3d->map->player.direction == SO)
			return (get_color_from_texture(&cub3d->textures[SO], x, y));
		return (get_color_from_texture(&cub3d->textures[NO], x, y));
	}
	return (0);
}