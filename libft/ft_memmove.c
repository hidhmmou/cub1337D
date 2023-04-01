/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidhmmou <hidhmmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:00:14 by hidhmmou          #+#    #+#             */
/*   Updated: 2022/10/08 21:00:06 by hidhmmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, void *src, size_t len)
{
	if (dst == NULL && src == NULL)
		return (0);
	if (dst < src)
		ft_memcpy(dst, src, len);
	else
		while (len--)
			*((unsigned char *)(dst + len)) = *((unsigned char *)(src + len));
	return (dst);
}
