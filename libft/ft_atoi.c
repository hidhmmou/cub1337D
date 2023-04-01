/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidhmmou <hidhmmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 15:43:54 by hidhmmou          #+#    #+#             */
/*   Updated: 2023/02/23 16:16:23 by hidhmmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(const char t)
{
	if (t == ' ')
		return (1);
	if (t >= 9 && t <= 13)
		return (1);
	return (0);
}

static int	is_num(const char t)
{
	if (t >= '0' && t <= '9')
		return (1);
	return (0);
}

static int	ft_check(int m, const char *str, int sign)
{
	if (m >= 19)
	{
		if (ft_strncmp("9223372036854775807", str, 19) < 0
			&& sign == 1)
			return (-1);
		if (ft_strncmp("9223372036854775808", str, 19) < 0
			&& sign == -1)
			return (0);
	}
	return (1);
}

static void	skip_and_inicialise(int *i, int *sign, const char *str)
{
	*sign = 1;
	*i = 0;
	while (str[*i] && ft_isspace(str[*i]))
		(*i)++;
	if (str[*i] == '+')
		(*i)++;
	else if (str[*i] == '-')
	{
		(*i)++;
		*sign = -1;
	}
	while (str[*i] == '0')
		(*i)++;
}

int	ft_atoi(const char *str)
{
	int					i;
	unsigned long long	s;
	int					sign;
	int					m;
	int					start;

	skip_and_inicialise(&i, &sign, str);
	m = 0;
	s = 0;
	start = i;
	while (str[i] && is_num(str[i]))
	{
		s = s * 10 + str[i++] - '0';
		m++;
		if (ft_check(m, str + start, sign) != 1)
			return ((ft_check(m, str + start, sign)));
	}
	return (sign * s);
}
