/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_01.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidhmmou <hidhmmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 13:20:45 by hidhmmou          #+#    #+#             */
/*   Updated: 2023/04/01 16:10:52 by hidhmmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

int	len_float(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

int	get_rows_nbr(int fd)
{
	int		len;
	char	*line;

	len = 0;
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		len++;
	}
	free(line);
	return (len);
}

void	fill_content(char *map_file, t_cub3d *cub3d)
{
	int	fd;
	int	i;

	i = 0;
	fd = open(map_file, O_RDONLY);
	if (fd == -1)
	{
		printf("%sso_long: no such file or directory: %s%s",
			RED, map_file, RESET);
		exit(1);
	}
	cub3d->map->rows = get_rows_nbr(fd);
	close(fd);
	fd = open(map_file, O_RDONLY);
	cub3d->map->content = malloc(sizeof(char *) * (cub3d->map->rows + 1));
	cub3d->map->content[i] = get_next_line(fd);
	while (i < cub3d->map->rows && cub3d->map->content[i++])
		cub3d->map->content[i] = get_next_line(fd);
	close(fd);
}

char	*get_from_file(char **content, char *target)
{
	int		i;
	char	*tmp;
	char	*ret;

	i = 0;
	while (content[i])
	{
		if (!ft_strncmp(content[i++], target, ft_strlen(target)))
		{
			tmp = ft_substr(content[i - 1] + ft_strlen(target), 0, \
				ft_strlen(content[i - 1] + ft_strlen(target)) - 1);
			ret = ft_strtrim(tmp, " \t");
			free(tmp);
			return (ret);
		}
	}
	return (NULL);
}

int	find(char **content, char *target, int flag)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (content[i])
	{
		if (flag && (content[i][0] == '1'
			|| content[i][0] == ' '
			|| content[i][0] == '0'))
			ft_error("the map must be the last !", NULL);
		if (!ft_strncmp(content[i++], target, ft_strlen(target)))
		{
			nb++;
			if (flag)
				break ;
		}
	}
	return (nb);
}
