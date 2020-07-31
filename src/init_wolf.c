/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_wolf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 19:39:41 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/07/31 20:27:23 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	quit_sdl(t_wolf *wolf)
{
	int	i;

	i = 0;
	if (wolf->sdl.render != NULL)
		SDL_DestroyRenderer(wolf->sdl.render);
	if (wolf->sdl.window != NULL)
		SDL_DestroyWindow(wolf->sdl.window);
	while (i != texture_total)
	{
		if (wolf->sdl.textures[i] != NULL)
			SDL_DestroyTexture(wolf->sdl.textures[i++]);
		else
			i++;
	}
	// Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	free(wolf->location.flor);
	free(wolf->location.sky);
	free(wolf->time);
	free(wolf);
}

void	filling_var(t_wolf *wolf)
{
	wolf->player.pos_x = 2;
	wolf->player.pos_y = 2;
	wolf->player.dir_x = -1;
	wolf->player.dir_y = 0;
	wolf->player.plane_x = 0;
	wolf->player.plane_y = 0.66;
	wolf->mouse.move_speed = 0.2;
	wolf->mouse.rot_speed = 0.019;
	wolf->menu.button_new = (SDL_Rect *)ft_memalloc(sizeof(SDL_Rect));
	wolf->menu.button_exit = (SDL_Rect *)ft_memalloc(sizeof(SDL_Rect));
	wolf->menu.button_new->h = 150;
	wolf->menu.button_new->w = 250;
	wolf->menu.button_new->x = WIDTH_WIN / 3 * 2;
	wolf->menu.button_new->y = HEIGHT_WIN / 3 * 2;
}

bool	load_files(SDL_Texture **textures, SDL_Renderer *render)
{
	int	i;

	textures[texture_main_menu] = IMG_LoadTexture(render, TEX_MENU);
	textures[texture_concrete] = IMG_LoadTexture(render, TEX_CONCRETE);
	textures[texture_dress_dry] = IMG_LoadTexture(render, TEX_DRESS_DRY);
	textures[texture_dress_green] = IMG_LoadTexture(render, TEX_DRESS_GREEN);
	textures[texture_sand] = IMG_LoadTexture(render, TEX_SAND);
	textures[texture_wood_box] = IMG_LoadTexture(render, TEX_WOOD_BOX_SIDE);
	textures[texture_wood_door] = IMG_LoadTexture(render, TEX_WOOD_DOOR);
	textures[texture_button_play] = IMG_LoadTexture(render, TEX_BUTTON_PLAY);
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
		SDL_INIT_EVENTS | SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC |
		SDL_INIT_GAMECONTROLLER) == -1)
		return (put_error_sdl(ERR_INIT_SDL, SDL_GetError()));
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		return (put_error_sdl(ERR_INIT_MIX, Mix_GetError()));
	if (TTF_Init() == -1)
		return (put_error_sdl(ERR_INIT_TTF, SDL_GetError()));
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
		return (false);
	if ((wolf->sdl.mix.music[mix_menu] = Mix_LoadMUS(MIX_MENU_MUS)) == NULL)
		return (put_error_sdl(ERR_LOAD_MIX, IMG_GetError()));
	return (true);
}
