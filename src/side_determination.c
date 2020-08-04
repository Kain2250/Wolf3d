/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   side_determination.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarc <mcarc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 14:53:33 by mcarc             #+#    #+#             */
/*   Updated: 2020/08/04 15:42:09 by mcarc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			side_determination(t_wolf *wolf)
{
	double		dx;
	double		dy;

	dx = wolf->player.pos_x - wolf->player.map_x;
	dy = wolf->player.pos_y - wolf->player.map_y;
	if ((dx < 0 && dy < 0 && !wolf->player.side)
		|| (dx < 0 && dy >= 0 && !wolf->player.side))
		wolf->player.cardinal = north;
	else if ((dx >= 0 && dy >= 0 && !wolf->player.side)
		|| (dx >= 0 && dy < 0 && !wolf->player.side))
		wolf->player.cardinal = south;
	else if ((dx < 0 && dy >=0 && wolf->player.side)
		|| (dx >= 0 && dy >=0 && wolf->player.side))
		wolf->player.cardinal = east;
	else
		wolf->player.cardinal = west;
}
