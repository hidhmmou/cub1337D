/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidhmmou <hidhmmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 21:02:57 by hidhmmou          #+#    #+#             */
/*   Updated: 2022/10/25 19:53:18 by hidhmmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	lend;
	size_t	lens;
	size_t	i;

	lend = 0;
	lens = 0;
	if (dst)
		lend = ft_strlen(dst);
	i = 0;
	lens = ft_strlen(src);
	if (dstsize == 0 || dstsize <= lend)
		return (lens + dstsize);
	while (src[i] && i < dstsize - lend - 1)
	{
		dst[lend + i] = src[i];
		i++;
	}
	dst[lend + i] = '\0';
	return (lend + lens);
}
