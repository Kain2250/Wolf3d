/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evelt_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 19:53:50 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/07/31 22:37:10 by bdrinkin         ###   ########.fr       */
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
	if (wolf->sdl.event.key.keysym.sym == SDLK_w ||
		wolf->sdl.event.key.keysym.sym == SDLK_UP)
		move_player(wolf, DIR_FORWARD);
	else if (wolf->sdl.event.key.keysym.sym == SDLK_s ||
		wolf->sdl.event.key.keysym.sym == SDLK_DOWN)
		move_player(wolf, DIR_BACK);
	else if (wolf->sdl.event.key.keysym.sym == SDLK_d ||
		wolf->sdl.event.key.keysym.sym == SDLK_RIGHT)
		rotate_plane_and_cam(wolf, -wolf->mouse.rot_speed);
	else if (wolf->sdl.event.key.keysym.sym == SDLK_a ||
		wolf->sdl.event.key.keysym.sym == SDLK_LEFT)
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

void			chenge_fov(t_wolf *wolf)
{
	if (wolf->sdl.event.key.keysym.sym == SDLK_e)
	{
		wolf->player.plane_x += 0.1;
		wolf->player.plane_y += 0.1;
	}
	else if (wolf->sdl.event.key.keysym.sym == SDLK_q)
	{
		wolf->player.plane_x -= 0.1;
		wolf->player.plane_y -= 0.1;
	}
	raycasting(wolf);
	// printf("%f\n", wolf->player.plane_x);
	// printf("%f\n\n", wolf->player.plane_y);
}

bool			event_list(t_wolf *wolf)
{
	SDL_WaitEvent(&wolf->sdl.event);
	// SDL_PollEvent(&wolf->sdl.event);
	if (event_exit(wolf) == true)
		wolf->quit = true;
	// fps_counter(wolf);
	if (wolf->menu.menu == true)
	{
		if (wolf->sdl.event.type == SDL_KEYDOWN &&
			(wolf->sdl.event.key.keysym.sym == SDLK_e || wolf->sdl.event.key.keysym.sym == SDLK_q))
			chenge_fov(wolf);
		if (wolf->sdl.event.type == SDL_KEYDOWN &&
			wolf->sdl.event.key.keysym.sym == SDLK_j)
			SDL_SetRelativeMouseMode(SDL_FALSE);
		if (wolf->sdl.event.type == SDL_KEYDOWN &&
			wolf->sdl.event.key.keysym.sym == SDLK_k)
			SDL_SetRelativeMouseMode(SDL_TRUE);
		if (wolf->sdl.event.type == SDL_KEYDOWN &&
			(wolf->sdl.event.key.keysym.sym == SDLK_a ||
			wolf->sdl.event.key.keysym.sym == SDLK_s ||
			wolf->sdl.event.key.keysym.sym == SDLK_w ||
			wolf->sdl.event.key.keysym.sym == SDLK_d ||
			wolf->sdl.event.key.keysym.sym == SDLK_UP ||
			wolf->sdl.event.key.keysym.sym == SDLK_DOWN ||
			wolf->sdl.event.key.keysym.sym == SDLK_LEFT ||
			wolf->sdl.event.key.keysym.sym == SDLK_RIGHT))
			event_key_hook(wolf);
		else if(wolf->sdl.event.type == SDL_MOUSEMOTION)
			event_mouse_hook(wolf);
	}
	return (true);
}
