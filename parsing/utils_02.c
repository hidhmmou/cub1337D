/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_02.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidhmmou <hidhmmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 22:47:53 by hidhmmou          #+#    #+#             */
/*   Updated: 2023/03/13 11:01:54 by hidhmmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

int	map_len(char **content)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (content[i])
	{
		if (in_set(content[i][0], "0 1"))
			break ;
		i++;
	}
	while (content[i++])
		len++;
	return (len);
}

int	in_set(char c, char *set)
{
	int	i;

	i = -1;
	while (set[++i])
		if (c == set[i])
			return (1);
	return (0);
}

int	fast_check(char	*line, int i, int len)
{
	if (line[0] == '\n')
		ft_error("invalid map (extra new line)!", NULL);
	if (i == len - 2 && line[ft_strlen(line) - 1] == '\n')
		ft_error("invalid map (extra new line at the end of the map)!", NULL);
	return (1);
}

int	is_num(const char t)
{
	if (t >= '0' && t <= '9')
		return (1);
	return (0);
}

int	check_colors_format(char **tab)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tab[i])
	{
		while (tab[i][j])
		{
			if (!is_num(tab[i][j]))
				ft_error("colors must be numbers !", NULL);
			j++;
		}
		j = 0;
		i++;
	}
	i = 0;
	while (tab[i])
		i++;
	return (i);
}
