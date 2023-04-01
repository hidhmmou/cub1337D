/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_surrounded.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidhmmou <hidhmmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 21:37:05 by hidhmmou          #+#    #+#             */
/*   Updated: 2023/04/01 16:10:52 by hidhmmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

int	check_boundaries(char **map, int rows, int max)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	(void)map;
	while (map[0][++j])
		if (map[0][j] == 'T')
			return (0);
	j = 0;
	while (map[rows - 1][j])
		if (map[rows - 1][j++] == 'T')
			return (0);
	while (map[i] && map[i][0])
		if (map[i++][0] == 'T')
			return (0);
	i = 0;
	while (map[i] && map[i][max - 2])
		if (map[i++][max - 2] == 'T')
			return (0);
	return (1);
}

void	virus_floor(t_cub3d *cub3d, int x, int y)
{
	char	**map;

	map = cub3d->map->check_map;
	if (map[x + 1] && in_set(map[x + 1][y], "0 "))
		ft_func_helper(cub3d, x + 1, y);
	if (map[x - 1] && in_set(map[x - 1][y], "0 "))
		ft_func_helper(cub3d, x - 1, y);
	if (map[x] && in_set(map[x][y + 1], "0 "))
		ft_func_helper(cub3d, x, y + 1);
	if (map[x] && in_set(map[x][y - 1], "0 "))
		ft_func_helper(cub3d, x, y - 1);
	return ;
}

void	ft_func_helper(t_cub3d *cub3d, int x, int y)
{
	cub3d->map->check_map[x][y] = 'T';
	virus_floor(cub3d, x, y);
}

int	count_empty(t_cub3d *cub3d)
{
	int	i;
	int	j;
	int	count;

	i = -1;
	j = 0;
	count = 0;
	while (cub3d->map->check_map[++i])
	{
		while (cub3d->map->check_map[i][j])
		{
			if (cub3d->map->check_map[i][j++] == ' ')
				count++;
		}
		j = 0;
	}
	return (count);
}

int	check_surrounded(t_cub3d *cub3d)
{
	int	x;
	int	y;
	int	check;

	x = cub3d->map->player.x;
	y = cub3d->map->player.y;
	virus_floor(cub3d, x, y);
	check = check_boundaries(cub3d->map->check_map, \
		len_float(cub3d->map->check_map), cub3d->map->max_len);
	return (cub3d->map->empty_nbr == count_empty(cub3d) && check);
}
