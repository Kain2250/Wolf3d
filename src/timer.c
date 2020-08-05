/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarc <mcarc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 14:15:36 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/08/04 15:42:11 by mcarc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

Uint32		get_ticks(t_timer *time)
{
	Uint32	time_temp;

	time_temp = 0;
	if (time->started)
	{
		if (time->paused)
			time_temp = time->paused_ticks;
		else
			time_temp = SDL_GetTicks() - time->start_ticks;
	}
	return (time_temp);
}

bool		time_is_started(t_timer *time)
{
	return (time->started);
}

bool		time_is_paused(t_timer *time)
{
	return (time->paused);
}

float		get_fps(t_timer *time)
{
	float	fps;

	fps = time->counted_frames / (get_ticks(time) / 1000.f);
	if (fps > 2000000)
		fps = 0;
	return (fps);
}

void		fps_counter(t_wolf *wolf)
{
	float	avg_fps;

	avg_fps = wolf->time->counted_frames / (get_ticks(wolf->time) / 1000.f);
	if (avg_fps > 2000000)
		avg_fps = 0;
	ft_putnbr((int)avg_fps);
	ft_putchar('\n');
	++wolf->time->counted_frames;
}
