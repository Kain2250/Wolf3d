/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evelt_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarc <mcarc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 19:53:50 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/08/04 15:41:56 by mcarc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <time.h>

void			event_key_hook(t_wolf *wolf)
{
	SDL_EventState(SDL_MOUSEMOTION, SDL_DISABLE);
	SDL_EventState(SDL_MOUSEMOTION, SDL_ENABLE);
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
}

void			event_mouse_hook(t_wolf *wolf)
{
	SDL_EventState(SDL_KEYDOWN, SDL_DISABLE);
	SDL_EventState(SDL_KEYDOWN, SDL_ENABLE);
	if (wolf->sdl.event.motion.xrel && wolf->sdl.event.motion.yrel)
	{
		rotate_plane_and_cam(wolf, -atan(wolf->sdl.event.motion.xrel)
		* wolf->mouse.rot_speed * 0.5);
		wolf->player.sit += -atan(wolf->sdl.event.motion.yrel) * 10;
	}
	else
	{
		rotate_plane_and_cam(wolf, -atan(wolf->sdl.event.motion.xrel)
		* wolf->mouse.rot_speed);
		wolf->player.sit += -atan(wolf->sdl.event.motion.yrel) * 10;
	}
	wolf->sdl.event.motion.xrel = 0;
	wolf->sdl.event.motion.yrel = 0;
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
}

bool			is_key_movement(t_wolf *wolf)
{
	if (IS_PUSH && (KEY_KEY == SDLK_a || KEY_KEY == SDLK_s ||
		KEY_KEY == SDLK_w || KEY_KEY == SDLK_d || KEY_KEY == SDLK_UP ||
		KEY_KEY == SDLK_DOWN || KEY_KEY == SDLK_LEFT ||	KEY_KEY == SDLK_RIGHT))
		return (true);
	return (false);
}

void			change_color_mod(t_wolf *wolf)
{
	if (wolf->sdl.event.key.keysym.sym == SDLK_1)
		wolf->location.color_mode = true;
	else if (wolf->sdl.event.key.keysym.sym == SDLK_2)
		wolf->location.color_mode = false;
}

void			game_events(t_wolf *wolf)
{
	if (wolf->sdl.event.type == SDL_KEYDOWN &&
			(wolf->sdl.event.key.keysym.sym == SDLK_1 ||
			wolf->sdl.event.key.keysym.sym == SDLK_2))
			change_color_mod(wolf);
		if (IS_PUSH && KEY_KEY == SDLK_LSHIFT)
			wolf->mouse.move_speed = 0.2;
		else if (wolf->sdl.event.type == SDL_KEYUP && KEY_KEY == SDLK_LSHIFT)
			wolf->mouse.move_speed = 0.1;
		if (wolf->sdl.event.type == SDL_KEYDOWN &&
			wolf->sdl.event.key.keysym.sym == SDLK_j)
			SDL_SetRelativeMouseMode(SDL_FALSE);
		if (IS_PUSH && KEY_KEY == SDLK_k)
			SDL_SetRelativeMouseMode(SDL_TRUE);
		if (is_key_movement(wolf) == true)
			event_key_hook(wolf);
		if (wolf->sdl.event.type == SDL_MOUSEMOTION)
			event_mouse_hook(wolf);
}

bool			event_list(t_wolf *wolf)
{
	SDL_WaitEvent(&wolf->sdl.event);
	if (event_exit(wolf) == true)
		wolf->quit = true;
	if (wolf->menu.menu == true)
	{
		game_events(wolf);
		raycasting(wolf);
		SDL_EventState(SDL_MOUSEMOTION, SDL_DISABLE);
		SDL_EventState(SDL_MOUSEMOTION, SDL_ENABLE);
	}
	return (true);
}
