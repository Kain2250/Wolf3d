/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_and_sky.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 17:21:14 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/08/10 19:42:12 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	floor_cast(t_wolf *wolf)
{
	int	y;
	int	x;
	int	p;

	float	ray_dir_x0;
	float	ray_dir_y0;
	float	ray_dir_x1;
	float	ray_dir_y1;
	float	pos_z;
	float	row_distance;
	float	floor_step_x;
	float	floor_step_y;
	float	floor_x;
	float	floor_y;

	int		cell_x;
	int		cell_y;
	int		tx;
	int		ty;
	int		floor_text;
	
	x = 0;
	y = 0;
	while (y < wolf->sdl.height)
	{
		ray_dir_x0 = wolf->player.dir_x - wolf->player.plane_x;
		ray_dir_y0 = wolf->player.dir_y - wolf->player.plane_y;
		ray_dir_x1 = wolf->player.dir_x + wolf->player.plane_x;
		ray_dir_y1 = wolf->player.dir_y + wolf->player.plane_y;
		p = y - wolf->sdl.height / 2;
		pos_z = 0.5 * wolf->sdl.height;
		row_distance = pos_z / p;
		floor_step_x = row_distance * (ray_dir_x1 - ray_dir_x0) / wolf->sdl.width;
		floor_step_y = row_distance * (ray_dir_y1 - ray_dir_y0) / wolf->sdl.width;
		floor_x = wolf->player.pos_x + row_distance * ray_dir_x0;
		floor_y = wolf->player.pos_y +row_distance * ray_dir_y0;
		while (x < wolf->sdl.width)
		{

			x++;
		}

		y++;
	}
}