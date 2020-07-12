/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 19:45:30 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/07/12 20:47:11 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		filling_var(t_wolf *wolf)
{
	wolf->player.pos_x = 2;
	wolf->player.pos_y = 2;
	wolf->player.dir_x = -1;
	wolf->player.dir_y = 0;
	wolf->player.plane_x = 0;
	wolf->player.plane_y = 0.66;
	wolf->player.time = 0;
	wolf->player.old_time = 0;
}

int			raycasting(t_wolf *wolf)
{
	int		x;
	float	w;

	x = 0;
	w = 512;
	while (x < (int)w)
	{
		wolf->player.camera_x = 2 * x / w - 1;
		wolf->player.ray_dir_x = wolf->player.dir_x + wolf->player.plane_x * wolf->player.camera_x;
		wolf->player.ray_dir_y = wolf->player.dir_y + wolf->player.plane_y * wolf->player.camera_x;
	}
	return (0);
}