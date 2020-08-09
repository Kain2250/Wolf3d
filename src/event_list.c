/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 19:53:50 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/08/09 20:00:12 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			event_key_hook(t_wolf *wolf)
{
	if (KEY_KEY == SDLK_w || KEY_KEY == SDLK_UP)
		move_player(wolf, DIR_FORWARD);
	else if (KEY_KEY == SDLK_s || KEY_KEY == SDLK_DOWN)
		move_player(wolf, DIR_BACK);
	else if (KEY_KEY == SDLK_d || KEY_KEY == SDLK_RIGHT)
		rotate_plane_and_cam(wolf, -wolf->mouse.rot_speed);
	else if (KEY_KEY == SDLK_a || KEY_KEY == SDLK_LEFT)
		rotate_plane_and_cam(wolf, wolf->mouse.rot_speed);
	if (Mix_Playing(2) == 0 && wolf->sdl.mix.mute == false)
		Mix_PlayChannel(2, wolf->sdl.mix.steps[time(NULL) % 3], 0);
	if (IS_PUSH && KEY_KEY == SDLK_TAB && wolf->location.minimap == false)
		wolf->location.minimap = true;
	else if (IS_PUSH && KEY_KEY == SDLK_TAB && wolf->location.minimap == true)
		wolf->location.minimap = false;
}

bool			is_key_movement(t_wolf *wolf)
{
	if (IS_PUSH && (KEY_KEY == SDLK_a ||
					KEY_KEY == SDLK_s ||
					KEY_KEY == SDLK_w ||
					KEY_KEY == SDLK_d ||
					KEY_KEY == SDLK_UP ||
					KEY_KEY == SDLK_DOWN ||
					KEY_KEY == SDLK_LEFT ||
					KEY_KEY == SDLK_RIGHT ||
					KEY_KEY == SDLK_TAB))
		return (true);
	return (false);
}

void			mute_music(t_wolf *wolf)
{
	if (IS_PUSH && KEY_KEY == SDLK_m && wolf->sdl.mix.mute == false)
	{
		wolf->sdl.mix.mute = true;
		Mix_HaltMusic();
	}
	else if (IS_PUSH && KEY_KEY == SDLK_m && wolf->sdl.mix.mute == true)
		wolf->sdl.mix.mute = false;
}

void			game_events(t_wolf *wolf)
{
	if (IS_PUSH && KEY_KEY == SDLK_p)
	{
		wolf->menu.menu = false;
		SDL_SetRelativeMouseMode(SDL_FALSE);
		Mix_HaltMusic();
		return ;
	}
	if (IS_PUSH && (KEY_KEY == SDLK_1 || KEY_KEY == SDLK_2 ||
		KEY_KEY == SDLK_3))
		change_color_mod(wolf);
	if (IS_PUSH && KEY_KEY == SDLK_LSHIFT)
		wolf->mouse.move_speed = 0.3;
	else if (wolf->sdl.event.type == SDL_KEYUP && KEY_KEY == SDLK_LSHIFT)
		wolf->mouse.move_speed = 0.2;
	if (wolf->sdl.event.type == SDL_KEYDOWN &&
		KEY_KEY == SDLK_i)
		SDL_SetRelativeMouseMode(SDL_FALSE);
	if (IS_PUSH && KEY_KEY == SDLK_o)
		SDL_SetRelativeMouseMode(SDL_TRUE);
	if (is_key_movement(wolf) == true)
		event_key_hook(wolf);
	if (wolf->sdl.event.type == SDL_MOUSEMOTION)
		event_mouse_hook(wolf);
	mute_music(wolf);
}

bool			event_list(t_wolf *wolf)
{
	SDL_PollEvent(&wolf->sdl.event);
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
