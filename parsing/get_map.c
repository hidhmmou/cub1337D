/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidhmmou <hidhmmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:20:46 by hidhmmou          #+#    #+#             */
/*   Updated: 2023/03/20 15:27:07 by hidhmmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

void	get_check_map(t_cub3d *cub3d)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	j = 0;
	tmp = 0;
	while (cub3d->map->map[i])
	{
		cub3d->map->check_map[i] = malloc(sizeof(char) * cub3d->map->max_len);
		cub3d->map->check_map[i][cub3d->map->max_len] = 0;
		cub3d->map->check_map[i][cub3d->map->max_len - 1] = '\n';
		ft_memset(cub3d->map->check_map[i], '0', cub3d->map->max_len - 1);
		tmp = 0;
		while (cub3d->map->map[i][j] && cub3d->map->map[i][j] != '\n')
		{
			cub3d->map->check_map[i][j] = cub3d->map->map[i][j];
			j++;
		}
		i++;
		j = 0;
	}
	cub3d->map->check_map[i] = NULL;
}

void	get_square_map(t_cub3d *cub3d)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	j = 0;
	tmp = 0;
	while (cub3d->map->map[i])
	{
		cub3d->map->square_map[i] = malloc(sizeof(char) * cub3d->map->max_len);
		cub3d->map->square_map[i][cub3d->map->max_len] = 0;
		cub3d->map->square_map[i][cub3d->map->max_len - 1] = '\n';
		ft_memset(cub3d->map->square_map[i], 'K', cub3d->map->max_len - 1);
		tmp = 0;
		while (cub3d->map->map[i][j] && cub3d->map->map[i][j] != '\n')
		{
			cub3d->map->square_map[i][j] = cub3d->map->map[i][j];
			j++;
		}
		i++;
		j = 0;
	}
	cub3d->map->square_map[i] = NULL;
}

void	get_map(t_cub3d *cub3d)
{
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	cub3d->map->max_len = 0;
	cub3d->map->len = map_len(cub3d->map->content) + 1;
	len = cub3d->map->len;
	cub3d->map->map = malloc(len * sizeof(char *));
	cub3d->map->check_map = malloc(len * sizeof(char *));
	cub3d->map->square_map = malloc(len * sizeof(char *));
	if (!cub3d->map->map || !cub3d->map->check_map || !cub3d->map->square_map)
		ft_error("malloc error !", NULL);
	while (cub3d->map->content[i] && !in_set(cub3d->map->content[i][0], "0 1"))
		i++;
	while (cub3d->map->content[i] && fast_check(cub3d->map->content[i], j, len))
	{
		cub3d->map->map[j] = ft_strdup(cub3d->map->content[i]);
		if (ft_strlen(cub3d->map->map[j]) > cub3d->map->max_len)
			cub3d->map->max_len = ft_strlen(cub3d->map->map[j]);
		i++;
		j++;
	}
	cub3d->map->map[j] = NULL;
}
