/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evelt_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 19:53:50 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/07/24 20:32:41 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <time.h>

void			event_key_hook(t_wolf *wolf)
{
	if (wolf->sdl.event.key.keysym.sym == SDLK_w)
		move_player(wolf, DIR_FORWARD);
	else if (wolf->sdl.event.key.keysym.sym == SDLK_s)
		move_player(wolf, DIR_BACK);
	else if (wolf->sdl.event.key.keysym.sym == SDLK_d)
		rotate_plane_and_cam(wolf, -wolf->mouse.rot_speed);
	else if (wolf->sdl.event.key.keysym.sym == SDLK_a)
		rotate_plane_and_cam(wolf, wolf->mouse.rot_speed);
	raycasting(wolf);
}

bool			event_list(t_wolf *wolf)
{
	SDL_WaitEvent(&wolf->sdl.event);
	if (event_exit(wolf) == true)
		wolf->quit = true;
	fps_counter(wolf);
	if (wolf->sdl.event.type == SDL_KEYDOWN &&
		(wolf->sdl.event.key.keysym.sym == SDLK_a ||
		wolf->sdl.event.key.keysym.sym == SDLK_s ||
		wolf->sdl.event.key.keysym.sym == SDLK_w ||
		wolf->sdl.event.key.keysym.sym == SDLK_d))
	{
		event_key_hook(wolf);
	}
	return (true);
}
