/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_wolf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 19:39:41 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/08/11 18:43:03 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	filling_var(t_wolf *wolf)
{
	wolf->player.dir_x = -1.f;
	wolf->player.dir_y = 0.f;
	wolf->player.plane_x = 0.f;
	wolf->player.plane_y = 0.65;
	wolf->mouse.move_speed = 0.2;
	wolf->mouse.rot_speed = 0.019;
	wolf->player.sit = 2;
	wolf->location.color_mode = mode_texture;
	wolf->location.delta_time = SDL_GetTicks();
}

bool	load_files(SDL_Texture **textures, SDL_Renderer *render)
{
	int	i;

	load_textures(textures, render);
	i = 0;
	while (i != texture_total)
	{
		if (textures[i] == NULL)
			return (false);
		else
			i++;
	}
	return (true);
}

bool	init_sdl(t_wolf *wolf)
{
	if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO |
		SDL_INIT_EVENTS) == -1)
		return (put_error_sdl(ERR_INIT_SDL, SDL_GetError()));
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		return (put_error_sdl(ERR_INIT_MIX, Mix_GetError()));
	if (!(IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG))
		return (put_error_sdl(ERR_INIT_IMG, IMG_GetError()));
	if ((wolf->sdl.window = SDL_CreateWindow(NAME_WIN, SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, WIDTH_WIN,
		HEIGHT_WIN, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE)) == NULL)
		return (put_error_sdl(ERR_CREATE_WIN, SDL_GetError()));
	if ((wolf->sdl.render = SDL_CreateRenderer(wolf->sdl.window,
		-1, SDL_RENDERER_ACCELERATED)) == NULL)
		return (put_error_sdl(ERR_CREATE_RENDERER, SDL_GetError()));
	return (true);
}

bool	load_mixer(t_wolf *wolf)
{
	if ((wolf->sdl.mix.music[mix_menu] = Mix_LoadMUS(MIX_MENU_MUS)) == NULL)
		return (put_error_sdl(ERR_LOAD_MIX, SDL_GetError()));
	if ((wolf->sdl.mix.music[mix_game] = Mix_LoadMUS(MIX_GAME)) == NULL)
		return (put_error_sdl(ERR_LOAD_MIX, SDL_GetError()));
	if ((wolf->sdl.mix.steps[mix_step1] = Mix_LoadWAV(MIX_STEP1)) == NULL)
		return (put_error_sdl(ERR_LOAD_MIX, SDL_GetError()));
	if ((wolf->sdl.mix.steps[mix_step2] = Mix_LoadWAV(MIX_STEP2)) == NULL)
		return (put_error_sdl(ERR_LOAD_MIX, SDL_GetError()));
	if ((wolf->sdl.mix.steps[mix_step3] = Mix_LoadWAV(MIX_STEP3)) == NULL)
		return (put_error_sdl(ERR_LOAD_MIX, SDL_GetError()));
	return (true);
}

bool	initialization(t_wolf *wolf, char *map)
{
	if (!(wolf->time = (t_timer *)ft_memalloc(sizeof(t_timer))))
	{
		put_error_sys(ERR_MALLOC);
		return (false);
	}
	if (pars_map(wolf, map) == 1)
		return (false);
	else if (init_sdl(wolf) == false)
		return (false);
	else if (load_files(wolf->sdl.textures, wolf->sdl.render) == false)
		return (put_error_sdl(ERR_LOAD_IMG, SDL_GetError()));
	else if (load_mixer(wolf) == false)
		return (false);
	return (true);
}
