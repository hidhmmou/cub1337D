/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidhmmou <hidhmmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 21:31:24 by hidhmmou          #+#    #+#             */
/*   Updated: 2023/04/03 00:41:12 by hidhmmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

void	get_player(t_cub3d *cub3d, int i, int j, int *found)
{
	if ((*found)++)
		ft_error("one player must exist in the map !", NULL);
	cub3d->map->player.x = j * SIZE + SIZE / 2;
	cub3d->map->player.y = i * SIZE + SIZE / 2;
	if (cub3d->map->map[i][j] == 'N')
		cub3d->map->player.angle = 270;
	else if (cub3d->map->map[i][j] == 'S')
		cub3d->map->player.angle = 90;
	else if (cub3d->map->map[i][j] == 'E')
		cub3d->map->player.angle = 180;
	else
		cub3d->map->player.angle = 0;
}

void	check_player(t_cub3d *cub3d)
{
	int	i;
	int	j;
	int	found;
	int	bad_character;

	found = 0;
	bad_character = 0;
	i = -1;
	j = 0;
	cub3d->map->empty_nbr = 0;
	while (cub3d->map->map[++i])
	{
		while (cub3d->map->map[i][j])
		{
			if (in_set(cub3d->map->map[i][j], "ENSW"))
				get_player(cub3d, i, j, &found);
			else if (!in_set(cub3d->map->map[i][j], "1 0D\n"))
				ft_error("bad charachter in the map !", NULL);
			if (cub3d->map->map[i][j++] == ' ')
				cub3d->map->empty_nbr++;
		}
		j = 0;
	}
}
