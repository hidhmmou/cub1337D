/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidhmmou <hidhmmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:16:58 by hidhmmou          #+#    #+#             */
/*   Updated: 2023/03/21 15:33:30 by hidhmmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

void	check_surroundness(t_cub3d *cub3d)
{
	//if (!check_surrounded(cub3d))
	//	ft_error("map not surrounded by walls !", NULL);
	if (!check_outsider_floor(cub3d))
		ft_error("floor outside !", NULL);
}

void	check_imposter_elements(char **content)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (content[++i])
	{
		if (in_set(content[i][0], " 10FC\n"))
			continue ;
		else if (ft_strncmp(content[i], "WE", 2)
			&& ft_strncmp(content[i], "NO", 2)
			&& ft_strncmp(content[i], "EA", 2)
			&& ft_strncmp(content[i], "SO", 2))
			ft_error("invalid element in the file", NULL);
	}
}

void	check_content(t_cub3d *cub3d)
{
	check_imposter_elements(cub3d->map->content);
	check_textures(cub3d->map->content);
	check_colors(cub3d->map->content);
	get_textures(cub3d);
	get_colors(cub3d);
	get_map(cub3d);
	check_player(cub3d);
	get_check_map(cub3d);
	get_square_map(cub3d);
	check_surroundness(cub3d);
	printf("%sValid map !\n%s", GREEN, RESET);
}
