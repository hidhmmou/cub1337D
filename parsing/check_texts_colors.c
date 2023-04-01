/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texts_colors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidhmmou <hidhmmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 17:18:51 by hidhmmou          #+#    #+#             */
/*   Updated: 2023/04/01 16:10:52 by hidhmmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

void	check_textures(char	**content)
{
	int	nb;

	nb = find(content, "NO ", 1);
	nb += find(content, "SO ", 1);
	nb += find(content, "WE ", 1);
	nb += find(content, "EA ", 1);
	if (nb == 4)
	{
		nb = 0;
		nb = find(content, "NO ", 0);
		nb += find(content, "WE ", 0);
		nb += find(content, "EA ", 0);
		nb += find(content, "SO ", 0);
		if (nb != 4)
			ft_error("duplicate textures in the file !", NULL);
	}
	else
		ft_error("incomplete texures !", NULL);
}

void	check_colors(char	**content)
{
	int	nb;

	nb = find(content, "F ", 1);
	nb += find(content, "C ", 1);
	if (nb == 2)
	{
		nb = 0;
		nb = find(content, "F ", 0);
		nb += find(content, "C ", 0);
		if (nb != 2)
			ft_error("duplicate colors in the file !", NULL);
	}
	else
		ft_error("incomplete colors !", NULL);
}

int	get_rgb(int color)
{
	if (color >= 0 && color <= 255)
		return (color);
	else
		ft_error("colors must be included in [0,255]", NULL);
	return (0);
}

void	get_colors(t_cub3d *cub3d)
{
	char	**floor;
	char	**ciel;

	cub3d->map->c_color = get_from_file(cub3d->map->content, "C");
	cub3d->map->f_color = get_from_file(cub3d->map->content, "F");
	if (!check_commas(cub3d->map->c_color, cub3d->map->f_color))
		ft_error("extra commas in colors (R,G,B)", NULL);
	ciel = splite_colors(cub3d->map->c_color);
	floor = splite_colors(cub3d->map->f_color);
	if (check_colors_format(ciel) != 3 || check_colors_format(floor) != 3)
		ft_error("colors must be in this form : R,G,B", NULL);
	cub3d->map->floor_color->r = get_rgb(ft_atoi(floor[0]));
	cub3d->map->floor_color->g = get_rgb(ft_atoi(floor[1]));
	cub3d->map->floor_color->b = get_rgb(ft_atoi(floor[2]));
	cub3d->map->ciel_color->r = get_rgb(ft_atoi(ciel[0]));
	cub3d->map->ciel_color->g = get_rgb(ft_atoi(ciel[1]));
	cub3d->map->ciel_color->b = get_rgb(ft_atoi(ciel[2]));
	free_float(ciel);
	free_float(floor);
}

void	get_textures(t_cub3d *cub3d)
{
	cub3d->map->ea_texture = get_from_file(cub3d->map->content, "EA");
	cub3d->map->no_texture = get_from_file(cub3d->map->content, "NO");
	cub3d->map->so_texture = get_from_file(cub3d->map->content, "SO");
	cub3d->map->we_texture = get_from_file(cub3d->map->content, "WE");
	if (open(cub3d->map->ea_texture, O_RDONLY) < 0
		|| open(cub3d->map->so_texture, O_RDONLY) < 0
		|| open(cub3d->map->we_texture, O_RDONLY) < 0
		||open(cub3d->map->no_texture, O_RDONLY) < 0)
		ft_error("couldn't open texture !", NULL);
}
