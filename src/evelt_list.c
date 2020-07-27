/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evelt_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 19:53:50 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/07/27 17:39:59 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <time.h>

void			clear_queue(void)
{
	SDL_EventState(SDL_KEYDOWN, SDL_DISABLE);
	SDL_EventState(SDL_KEYDOWN, SDL_ENABLE);
	SDL_EventState(SDL_MOUSEMOTION, SDL_DISABLE);
	SDL_EventState(SDL_MOUSEMOTION, SDL_ENABLE);
}

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

void			event_mouse_hook(t_wolf *wolf)
{
	rotate_plane_and_cam(wolf, -atan(wolf->sdl.event.motion.xrel)
	* wolf->mouse.rot_speed);
	raycasting(wolf);
	clear_queue();
}

bool			event_list(t_wolf *wolf)
{
	SDL_WaitEvent(&wolf->sdl.event);
	// SDL_PollEvent(&wolf->sdl.event);
	if (event_exit(wolf) == true)
		wolf->quit = true;
	// fps_counter(wolf);
	if (wolf->sdl.event.type == SDL_KEYDOWN &&
		(wolf->sdl.event.key.keysym.sym == SDLK_a ||
		wolf->sdl.event.key.keysym.sym == SDLK_s ||
		wolf->sdl.event.key.keysym.sym == SDLK_w ||
		wolf->sdl.event.key.keysym.sym == SDLK_d))
		event_key_hook(wolf);
	else if(wolf->sdl.event.type == SDL_MOUSEMOTION)
		event_mouse_hook(wolf);
	return (true);
}
