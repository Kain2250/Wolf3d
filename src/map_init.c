/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 10:27:47 by mcarc             #+#    #+#             */
/*   Updated: 2020/08/11 21:06:19 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

bool			map_init(t_wolf *wolf)
{
	wolf->sdl.map_width = wolf->location.x_len * 10;
	printf("%d\n", wolf->sdl.map_width);
	if ((wolf->sdl.map_window = SDL_CreateWindow(NAME_MAP, 0, 0,
	wolf->sdl.map_width,
		HEIGHT_MAP, SDL_WINDOW_SHOWN)) == NULL)
		return (put_error_sdl(ERR_CREATE_WIN, SDL_GetError()));
	if ((wolf->sdl.map_render = SDL_CreateRenderer(wolf->sdl.map_window,
		-1, SDL_RENDERER_SOFTWARE)) == NULL)
		return (put_error_sdl(ERR_CREATE_RENDERER, SDL_GetError()));
	if ((wolf->sdl.textures[map_cell] = IMG_LoadTexture(wolf->sdl.map_render,
		TEX_MAP_CELL)) == NULL)
		return (put_error_sdl(ERR_LOAD_IMG, SDL_GetError()));
	return (true);
}

bool			map_destroy(t_wolf *wolf)
{
	SDL_DestroyTexture(wolf->sdl.textures[map_cell]);
	SDL_DestroyRenderer(wolf->sdl.map_render);
	SDL_DestroyWindow(wolf->sdl.map_window);
	return (true);
}
