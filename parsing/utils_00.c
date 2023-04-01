/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_00.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidhmmou <hidhmmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:03:01 by hidhmmou          #+#    #+#             */
/*   Updated: 2023/04/01 16:10:52 by hidhmmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

void	free_float(char	**arr)
{
	unsigned int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	ft_free(t_cub3d *cub3d)
{
	int	i;

	i = -1;
	if (cub3d->map->content)
		free_float(cub3d->map->content);
	if (cub3d->map->map)
		free_float(cub3d->map->map);
	exit(0);
}

void	ft_error(char *message, t_cub3d *cub3d)
{
	printf("%sError\n%s%s\n", RED, message, RESET);
	if (cub3d)
		ft_free(cub3d);
	exit(EXIT_FAILURE);
}

int	rgb_to_int(t_color color)
{
	return ((color.r << 16) | (color.g << 8) | color.b);
}

int shader(int color, float percent)
{
	int r;
	int g;
	int b;
	int shade;

	shade = 255;
	if (percent > 100)
		percent = 100;
	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	shade -= shade * percent / 100;
	
	return(shade << 24 | r << 16 | g << 8 | b);
}