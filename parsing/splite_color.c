/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splite_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidhmmou <hidhmmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:20:28 by hidhmmou          #+#    #+#             */
/*   Updated: 2023/03/20 14:28:59 by hidhmmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

char	**m_error(char	**arr)
{
	unsigned int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	return (NULL);
}

int	ft_count_words(char const *str)
{
	int	i;
	int	nbr_w;

	nbr_w = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == ','))
			i++;
		if (str[i])
			nbr_w++;
		while (str[i] && !(str[i] == ','))
			i++;
	}
	return (nbr_w);
}

int	ft_word_len(char const *str)
{
	int	i;

	i = 0;
	while (str[i] && !(str[i] == ','))
		i++;
	return (i);
}

char	*ft_word_grep(char const *str)
{
	int		len_w;
	int		i;
	char	*word;

	i = 0;
	len_w = ft_word_len(str);
	word = malloc(sizeof(char) * (len_w + 1));
	if (!word)
		return (NULL);
	while (i < len_w)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = 0;
	return (word);
}

char	**splite_colors(char const *s)
{
	int			i;
	char		**splited;

	if (!s)
		return (NULL);
	i = 0;
	splited = malloc(sizeof(char *) * (ft_count_words(s) + 1));
	if (!splited)
		return (NULL);
	while (*s)
	{
		while (*s && (*s == ','))
			s++;
		if (*s)
		{
			splited[i] = ft_word_grep(s);
			if (!splited[i])
				return (m_error(splited));
			i++;
		}
		while (*s && !(*s == ','))
			s++;
	}
	splited[i] = 0;
	return (splited);
}
