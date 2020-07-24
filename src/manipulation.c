/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 18:45:19 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/07/24 18:47:02 by bdrinkin         ###   ########.fr       */
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

	x = wolf->player.pos_x + wolf->player.dir_x * wolf->mouse.move_speed;
	y = wolf->player.pos_y + wolf->player.dir_y * wolf->mouse.move_speed;
	if (direction == DIR_FORWARD)
	{
		if (wolf->location.map[(int)x][(int)wolf->player.pos_y] == '0')
			wolf->player.pos_x += wolf->player.dir_x * wolf->mouse.move_speed;
		if (wolf->location.map[(int)wolf->player.pos_x][(int)y] == '0')
			wolf->player.pos_y += wolf->player.dir_y * wolf->mouse.move_speed;
	}
	else
	{
		if (wolf->location.map[(int)x][(int)wolf->player.pos_y] == '0')
			wolf->player.pos_x -= wolf->player.dir_x * wolf->mouse.move_speed;
		if (wolf->location.map[(int)wolf->player.pos_x][(int)y] == '0')
			wolf->player.pos_y -= wolf->player.dir_y * wolf->mouse.move_speed;
	}
}
