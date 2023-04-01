/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidhmmou <hidhmmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 18:34:44 by hidhmmou          #+#    #+#             */
/*   Updated: 2023/04/01 18:34:53 by hidhmmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

int mouse_move(int x, int y, t_cub3d *cub3d)
{
	if (!cub3d->start || cub3d->mouse->shown == 1)
		return (1);
	if (cub3d->mouse->x != x)
	{
		cub3d->map->player.angle -= (x - cub3d->mouse->x) * 0.1;
		cub3d->mouse->x = x;
		if (cub3d->mouse->x >= WIDTH || cub3d->mouse->x <= 0)
		{
			mlx_mouse_move(cub3d->win, WIDTH / 2, HEIGHT / 2);
			cub3d->mouse->x = WIDTH / 2;
		}
		mlx_mouse_move(cub3d->win, cub3d->mouse->x, HEIGHT / 2);
		cub3d->change = 1;
	}
	else
		cub3d->change = 0;
	return (0);
}