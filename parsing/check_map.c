/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidhmmou <hidhmmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:47:20 by hidhmmou          #+#    #+#             */
/*   Updated: 2023/03/21 15:32:51 by hidhmmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

int	check_empty(char *file)
{
	int		fd;
	char	test;
	int		ret;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		printf("%scub3d: no such file or directory: %s%s",
			RED, file, RESET);
		exit(1);
	}
	ret = read(fd, &test, 1);
	close(fd);
	return (ret);
}

void	check_if_dir(char *f_name)
{
	int	fd;

	fd = open(f_name, O_DIRECTORY);
	if (fd != -1)
	{
		close(fd);
		ft_error("this is a directory !", NULL);
	}
}

int	check_extention(char *f_name)
{
	size_t	len;
	char	*ext;
	int		i;

	i = 0;
	len = ft_strlen(f_name);
	ext = ".cub";
	while (len-- > 4)
		i++;
	while (f_name[i])
	{
		if (f_name[i] != *ext)
			return (0);
		i++;
		ext++;
	}
	return (1);
}

void	pre_check_map(char *file)
{
	check_if_dir(file);
	if (!check_extention(file))
		ft_error("bad extention !", NULL);
	if (!check_empty(file))
		ft_error("empty file !", NULL);
}
