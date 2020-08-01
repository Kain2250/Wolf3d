/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evelt_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 19:53:50 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/08/01 18:39:54 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <time.h>

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
	if (Mix_Playing(2) == 0)
		Mix_PlayChannel(2, wolf->sdl.mix.steps[time(NULL) % 3], 0);
	raycasting(wolf);
}

void			event_mouse_hook(t_wolf *wolf)
{
	rotate_plane_and_cam(wolf, -atan(wolf->sdl.event.motion.xrel)
	* wolf->mouse.rot_speed);
	wolf->player.sit += -atan(wolf->sdl.event.motion.yrel) * 10;
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
}

bool			is_key_movement(t_wolf *wolf)
{
	if (wolf->sdl.event.type == SDL_KEYDOWN &&
		(wolf->sdl.event.key.keysym.sym == SDLK_a ||
		wolf->sdl.event.key.keysym.sym == SDLK_s ||
		wolf->sdl.event.key.keysym.sym == SDLK_w ||
		wolf->sdl.event.key.keysym.sym == SDLK_d ||
		wolf->sdl.event.key.keysym.sym == SDLK_UP ||
		wolf->sdl.event.key.keysym.sym == SDLK_DOWN ||
		wolf->sdl.event.key.keysym.sym == SDLK_LEFT ||
		wolf->sdl.event.key.keysym.sym == SDLK_RIGHT))
		return (true);
	return (false);
}

bool			event_list(t_wolf *wolf)
{
	SDL_WaitEvent(&wolf->sdl.event);
	if (event_exit(wolf) == true)
		wolf->quit = true;
	if (wolf->menu.menu == true)
	{
		if (wolf->sdl.event.type == SDL_KEYDOWN &&
			wolf->sdl.event.key.keysym.sym == SDLK_LSHIFT)
			wolf->mouse.move_speed = 0.2;
		else if (wolf->sdl.event.type == SDL_KEYUP &&
			wolf->sdl.event.key.keysym.sym == SDLK_LSHIFT)
			wolf->mouse.move_speed = 0.1;
		if (wolf->sdl.event.type == SDL_KEYDOWN &&
			wolf->sdl.event.key.keysym.sym == SDLK_LCTRL)
			wolf->player.sit *= -1;
		if (wolf->sdl.event.type == SDL_KEYDOWN &&
			(wolf->sdl.event.key.keysym.sym == SDLK_e ||
			wolf->sdl.event.key.keysym.sym == SDLK_q))
			chenge_fov(wolf);
		if (wolf->sdl.event.type == SDL_KEYDOWN &&
			wolf->sdl.event.key.keysym.sym == SDLK_j)
			SDL_SetRelativeMouseMode(SDL_FALSE);
		if (wolf->sdl.event.type == SDL_KEYDOWN &&
			wolf->sdl.event.key.keysym.sym == SDLK_k)
			SDL_SetRelativeMouseMode(SDL_TRUE);
		if (is_key_movement(wolf) == true)
			event_key_hook(wolf);
		else if (wolf->sdl.event.type == SDL_MOUSEMOTION)
			event_mouse_hook(wolf);
	}
	return (true);
}
