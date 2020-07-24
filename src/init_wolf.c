/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_wolf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 19:39:41 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/07/24 19:46:32 by bdrinkin         ###   ########.fr       */
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
	wolf->player.pos_x = 8;
	wolf->player.pos_y = 12;
	wolf->player.dir_x = -1;
	wolf->player.dir_y = 0;
	wolf->player.plane_x = 0;
	wolf->player.plane_y = 0.66;
	wolf->mouse.move_speed = 0.2;
	wolf->mouse.rot_speed = 0.09;
	wolf->location.flor = (SDL_Rect *)ft_memalloc(sizeof(SDL_Rect));
	wolf->location.sky = (SDL_Rect *)ft_memalloc(sizeof(SDL_Rect));
	wolf->location.sky->h = 32;
	wolf->location.sky->w = 32;
	wolf->location.sky->x = 0;
	wolf->location.sky->y = 0;
	wolf->location.flor->h = HEIGHT_WIN / 2;
	wolf->location.flor->w = WIDTH_WIN;
	wolf->location.flor->x = 0;
	wolf->location.flor->y = HEIGHT_WIN / 2;
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
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
		return (put_error_sdl(ERR_INIT_SDL, SDL_GetError()));
	if (TTF_Init() == -1)
		return (put_error_sdl(ERR_INIT_TTF, SDL_GetError()));
	if (!(IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG))
		return (put_error_sdl(ERR_INIT_IMG, IMG_GetError()));
	if ((wolf->sdl.window = SDL_CreateWindow(NAME_WIN, SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, WIDTH_WIN,
		HEIGHT_WIN, SDL_WINDOW_SHOWN)) == NULL)
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
	if (init_sdl(wolf) == false)
		return (false);
	else if (pars_map(wolf, map) == 1)
		return (false);
	else if (load_files(wolf->sdl.textures, wolf->sdl.render) == false)
		return (false);
	return (true);
}
