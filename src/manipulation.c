/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarc <mcarc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 18:45:19 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/08/07 19:54:23 by mcarc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		change_color_mod(t_wolf *wolf)
{
	if (KEY_KEY == SDLK_1)
		wolf->location.color_mode = mode_texture;
	else if (KEY_KEY == SDLK_2)
		wolf->location.color_mode = mode_cardinal;
	else if (KEY_KEY == SDLK_3)
		wolf->location.color_mode = mode_rgb;
}

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

double		decriment(double a, double alpha)
{
	if (a > 0)
		a -= alpha;
	else
		a += alpha;
	return (a);
}

void		move_player(t_wolf *wolf, int direction)
{
	int		dir_def[8];

	dir_def[0] = wolf->location.map[(int)(wolf->player.pos_x)][(int)(wolf->player.pos_y + wolf->mouse.move_speed + 0.2)] > '0' ? 0 : 1;  //y> 0 1
	dir_def[1] = wolf->location.map[(int)(wolf->player.pos_x)][(int)(wolf->player.pos_y - (wolf->mouse.move_speed + 0.2))] > '0' ? 0 : 1; //y< 1 0
	dir_def[2] = wolf->location.map[(int)(wolf->player.pos_x + wolf->mouse.move_speed + 0.2)][(int)(wolf->player.pos_y)] > '0' ? 0 : 1;  //x> 2 3
	dir_def[3] = wolf->location.map[(int)(wolf->player.pos_x - wolf->mouse.move_speed - 0.2)][(int)(wolf->player.pos_y)] > '0' ? 0 : 1;  //x< 3 2
	dir_def[4] = wolf->location.map[(int)(wolf->player.pos_x - wolf->mouse.move_speed - 0.15)][(int)(wolf->player.pos_y + wolf->mouse.move_speed + 0.15)] > '0' ? 0 : 1;  // y> x< 4 6
	dir_def[5] = wolf->location.map[(int)(wolf->player.pos_x - wolf->mouse.move_speed - 0.15)][(int)(wolf->player.pos_y - wolf->mouse.move_speed - 0.15)] > '0' ? 0 : 1;  // y< x< 5 7
	dir_def[6] = wolf->location.map[(int)(wolf->player.pos_x + wolf->mouse.move_speed + 0.15)][(int)(wolf->player.pos_y - wolf->mouse.move_speed - 0.15)] > '0' ? 0 : 1;  // y< x> 6 4
	dir_def[7] = wolf->location.map[(int)(wolf->player.pos_x + wolf->mouse.move_speed + 0.15)][(int)(wolf->player.pos_y + wolf->mouse.move_speed + 0.15)] > '0' ? 0 : 1;  // y> x> 7 5
	if (direction == DIR_BACK)
	{
		if (wolf->player.dir_x < 0 && wolf->player.dir_y >= 0)
		{
			if (dir_def[6] && dir_def[1] && dir_def[2] && dir_def[5] && dir_def[7])
			{
				wolf->player.pos_x -= wolf->player.dir_x * wolf->mouse.move_speed;
				wolf->player.pos_y -= wolf->player.dir_y * wolf->mouse.move_speed;
			}
			else if (dir_def[1] && dir_def[5])
				wolf->player.pos_y -= wolf->player.dir_y * wolf->mouse.move_speed;
			else if (dir_def[2] && dir_def[7])
				wolf->player.pos_x -= wolf->player.dir_x * wolf->mouse.move_speed;
		}
		if (wolf->player.dir_x >= 0 && wolf->player.dir_y < 0)
		{
			if (dir_def[4] && dir_def[0] && dir_def[3] && dir_def[5] && dir_def[7])
			{
				wolf->player.pos_x -= wolf->player.dir_x * wolf->mouse.move_speed;
				wolf->player.pos_y -= wolf->player.dir_y * wolf->mouse.move_speed;
			}
			else if (dir_def[0] && dir_def[7])
				wolf->player.pos_y -= wolf->player.dir_y * wolf->mouse.move_speed;
			else if (dir_def[3] && dir_def[5])
				wolf->player.pos_x -= wolf->player.dir_x * wolf->mouse.move_speed;
		}
		if (wolf->player.dir_x < 0 && wolf->player.dir_y < 0)
		{
			if (dir_def[7] && dir_def[0] && dir_def[2] && dir_def[6] && dir_def[4])
			{
				wolf->player.pos_x -= wolf->player.dir_x * wolf->mouse.move_speed;
				wolf->player.pos_y -= wolf->player.dir_y * wolf->mouse.move_speed;
			}
			else if (dir_def[0] && dir_def[4])
				wolf->player.pos_y -= wolf->player.dir_y * wolf->mouse.move_speed;
			else if (dir_def[2] && dir_def[6])
				wolf->player.pos_x -= wolf->player.dir_x * wolf->mouse.move_speed;
		}
		if (wolf->player.dir_x >= 0 && wolf->player.dir_y >= 0)
		{
			if (dir_def[5] && dir_def[1] && dir_def[3] && dir_def[6] && dir_def[4])
			{
				wolf->player.pos_x -= wolf->player.dir_x * wolf->mouse.move_speed;
				wolf->player.pos_y -= wolf->player.dir_y * wolf->mouse.move_speed;
			}
			else if (dir_def[1] && dir_def[6])
				wolf->player.pos_y -= wolf->player.dir_y * wolf->mouse.move_speed;
			else if (dir_def[3] && dir_def[4])
				wolf->player.pos_x -= wolf->player.dir_x * wolf->mouse.move_speed;
		}
	}
	else if (direction == DIR_FORWARD)
	{
		if (wolf->player.dir_x < 0 && wolf->player.dir_y >= 0)
		{
			if (dir_def[4] && dir_def[0] && dir_def[3] && dir_def[5] && dir_def[7])
			{
				wolf->player.pos_x += wolf->player.dir_x * wolf->mouse.move_speed;
				wolf->player.pos_y += wolf->player.dir_y * wolf->mouse.move_speed;
			}
			else if (dir_def[0] && dir_def[7])
				wolf->player.pos_y += wolf->player.dir_y * wolf->mouse.move_speed;
			else if (dir_def[3] && dir_def[5])
				wolf->player.pos_x += wolf->player.dir_x * wolf->mouse.move_speed;
		}
		if (wolf->player.dir_x >= 0 && wolf->player.dir_y < 0)
		{
			if (dir_def[6] && dir_def[1] && dir_def[2] && dir_def[5] && dir_def[7])
			{
				wolf->player.pos_x += wolf->player.dir_x * wolf->mouse.move_speed;
				wolf->player.pos_y += wolf->player.dir_y * wolf->mouse.move_speed;
			}
			else if (dir_def[1] && dir_def[5])
				wolf->player.pos_y += wolf->player.dir_y * wolf->mouse.move_speed;
			else if (dir_def[2] && dir_def[7])
				wolf->player.pos_x += wolf->player.dir_x * wolf->mouse.move_speed;
		}
		if (wolf->player.dir_x < 0 && wolf->player.dir_y < 0)
		{
			if (dir_def[5] && dir_def[1] && dir_def[3] && dir_def[6] && dir_def[4])
			{
				wolf->player.pos_x += wolf->player.dir_x * wolf->mouse.move_speed;
				wolf->player.pos_y += wolf->player.dir_y * wolf->mouse.move_speed;
			}
			else if (dir_def[1] && dir_def[6])
				wolf->player.pos_y += wolf->player.dir_y * wolf->mouse.move_speed;
			else if (dir_def[3] && dir_def[4])
				wolf->player.pos_x += wolf->player.dir_x * wolf->mouse.move_speed;
		}
		if (wolf->player.dir_x >= 0 && wolf->player.dir_y >= 0)
		{
			if (dir_def[7] && dir_def[0] && dir_def[2] && dir_def[6] && dir_def[4])
			{
				wolf->player.pos_x += wolf->player.dir_x * wolf->mouse.move_speed;
				wolf->player.pos_y += wolf->player.dir_y * wolf->mouse.move_speed;
			}
			else if (dir_def[0] && dir_def[4])
				wolf->player.pos_y += wolf->player.dir_y * wolf->mouse.move_speed;
			else if (dir_def[2] && dir_def[6])
				wolf->player.pos_x += wolf->player.dir_x * wolf->mouse.move_speed;
		}
	}
}
