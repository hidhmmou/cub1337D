/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidhmmou <hidhmmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 01:02:48 by hidhmmou          #+#    #+#             */
/*   Updated: 2023/04/02 02:37:44 by hidhmmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

void minimap(int button, int x, int y, t_cub3d *cub3d)
{
	if (button == LEFT_CLICK && in_range(x, y, 0, 0, 200, 200) && cub3d->minimap > 0)
	{
		cub3d->minimap *= -1;
		render(cub3d);
	}
	else if (button == LEFT_CLICK && in_range(x, y, 37, 32, 106, 112) && cub3d->minimap < 0)
	{
		cub3d->minimap *= -1;
		render(cub3d);
	}
}

void press_start(int button, int x, int y, t_cub3d *cub3d)
{
	if (button == LEFT_CLICK && in_range(x, y, 506, 511, 813, 602) && !cub3d->start++)
		render(cub3d);
}
