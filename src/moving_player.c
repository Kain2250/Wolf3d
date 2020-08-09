/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 15:04:34 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/08/09 15:58:56 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		x_less_y_more__y_less_x_more(t_wolf *wolf, int dir_def[8])
{
	if (wolf->player.dir_x < 0 && wolf->player.dir_y >= 0)
	{
		if (dir_def[1] && dir_def[2] && dir_def[5] && dir_def[6] && dir_def[7])
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
}

static void		x_less_y_less__x_more_y_more(t_wolf *wolf, int dir_def[8])
{
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

static void		x_less_y_more__x_more_y_less(t_wolf *wolf, int dir_def[8])
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
}

static void		x_less_y_less__y_more_x_more(t_wolf *wolf, int dir_def[8])
{
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

void			move_player(t_wolf *wolf, int direction)
{
	int			dir_def[8];

	calc_dir_def(wolf, dir_def);
	if (direction == DIR_BACK)
	{
		x_less_y_more__y_less_x_more(wolf, dir_def);
		x_less_y_less__x_more_y_more(wolf, dir_def);
	}
	else if (direction == DIR_FORWARD)
	{
		x_less_y_more__x_more_y_less(wolf, dir_def);
		x_less_y_less__y_more_x_more(wolf, dir_def);
	}
}
