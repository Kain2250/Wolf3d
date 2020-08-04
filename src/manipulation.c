/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarc <mcarc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 18:45:19 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/08/04 15:42:03 by mcarc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		rotate_plane_and_cam(t_wolf *wolf, float rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = wolf->player.dir_x;
	wolf->player.dir_x = wolf->player.dir_x * cos(rot_speed) -
	wolf->player.dir_y * sin(rot_speed);
	wolf->player.dir_y = old_dir_x * sin(rot_speed) +
	wolf->player.dir_y * cos(rot_speed);
	old_plane_x = wolf->player.plane_x;
	wolf->player.plane_x = wolf->player.plane_x * cos(rot_speed) -
	wolf->player.plane_y * sin(rot_speed);
	wolf->player.plane_y = old_plane_x * sin(rot_speed) +
	wolf->player.plane_y * cos(rot_speed);
}

void		move_player(t_wolf *wolf, int direction)
{
	double	x;
	double	y;
	double	x1;
	double	y1;

	if (direction == DIR_FORWARD)
	{
		x = wolf->player.pos_x + wolf->player.dir_x * wolf->mouse.move_speed;
		y = wolf->player.pos_y + wolf->player.dir_y * wolf->mouse.move_speed;
		if (wolf->location.map[(int)x][(int)wolf->player.pos_y] == '0')
			wolf->player.pos_x += wolf->player.dir_x * wolf->mouse.move_speed;
		if (wolf->location.map[(int)wolf->player.pos_x][(int)y] == '0')
			wolf->player.pos_y += wolf->player.dir_y * wolf->mouse.move_speed;
	}
	else if (direction == DIR_BACK)
	{
		x1 = wolf->player.pos_x - wolf->player.dir_x * wolf->mouse.move_speed;
		y1 = wolf->player.pos_y - wolf->player.dir_y * wolf->mouse.move_speed;
		if (wolf->location.map[(int)x1][(int)wolf->player.pos_y] == '0')
			wolf->player.pos_x -= wolf->player.dir_x * wolf->mouse.move_speed;
		if (wolf->location.map[(int)wolf->player.pos_x][(int)y1] == '0')
			wolf->player.pos_y -= wolf->player.dir_y  * wolf->mouse.move_speed;
	}
}
