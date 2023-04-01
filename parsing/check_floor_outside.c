/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_floor_outside.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidhmmou <hidhmmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 16:47:47 by hidhmmou          #+#    #+#             */
/*   Updated: 2023/03/01 18:34:17 by hidhmmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

int	check_right(t_cub3d *cub3d, int i, int j)
{
	while (cub3d->map->square_map[i][j])
	{
		if (cub3d->map->square_map[i][j] == '1')
			return (1);
		else if (cub3d->map->square_map[i][j] == ' ')
			return (0);
		j++;
	}
	return (0);
}

int	check_left(t_cub3d *cub3d, int i, int j)
{
	while (j >= 0 && cub3d->map->map[i][j])
	{
		if (cub3d->map->square_map[i][j] == '1')
			return (1);
		else if (cub3d->map->square_map[i][j] == ' ')
			return (0);
		j--;
	}
	return (0);
}

int	check_above(t_cub3d *cub3d, int i, int j)
{
	while (i >= 0)
	{
		if (cub3d->map->square_map[i][j] == '1')
			return (1);
		else if (cub3d->map->square_map[i][j] == ' ')
			return (0);
		else if (cub3d->map->square_map[i][j] == 'K')
			break ;
		i--;
	}
	return (0);
}

int	check_bellow(t_cub3d *cub3d, int i, int j)
{
	while (cub3d->map->square_map[i] && cub3d->map->square_map[i][j])
	{
		if (cub3d->map->square_map[i][j] == '1')
			return (1);
		else if (cub3d->map->square_map[i][j] == ' ')
			return (0);
		else if (cub3d->map->square_map[i][j] == 'K')
			break ;
		i++;
	}
	return (0);
}

int	check_outsider_floor(t_cub3d *cub3d)
{
	int	i;
	int	j;

	i = 0;
	while (cub3d->map->square_map[i])
	{
		j = 0;
		while (cub3d->map->square_map[i][j])
		{
			if (cub3d->map->square_map[i][j] == '0')
			{
				if (!check_right(cub3d, i, j + 1))
					return (0);
				if (!check_left(cub3d, i, j - 1))
					return (0);
				if (!check_above(cub3d, i - 1, j))
					return (0);
				if (!check_bellow(cub3d, i + 1, j))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
