/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evelt_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 19:53:50 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/07/12 20:31:42 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			apply_surface(SDL_Surface *source, SDL_Surface *destination,
				SDL_Rect offset)
{
	SDL_BlitSurface(source, NULL, destination, &offset);
}

void			apply_surface_scaled(SDL_Surface *source,
				SDL_Surface *destination, SDL_Rect offset)
{
	SDL_BlitScaled(source, NULL, destination, &offset);
}

void			apply_render(SDL_Renderer *render, SDL_Texture *texture,
				SDL_Rect *srcrect, const SDL_Rect *dstrect)
{
	SDL_RenderClear(render);
	SDL_RenderCopy(render, texture, srcrect, dstrect);
	SDL_RenderPresent(render);
}

bool			event_exit(t_wolf *wolf)
{
	if (wolf->sdl.event.type == SDL_QUIT ||
		wolf->sdl.event.key.keysym.sym == SDLK_ESCAPE)
		return (true);
	else
		return (false);
}

bool			event_list(t_wolf *wolf)
{
	SDL_WaitEvent(&wolf->sdl.event);
	if (event_exit(wolf) == true)
		wolf->quit = true;
	raycasting(wolf);
	// else if (w->sdl.event.button.button == SDL_BUTTON_RIGHT)
	// 	apply_render(w->sdl.render, w->sdl.textures[texture_sand], NULL, NULL);
	// else if (w->sdl.event.button.button == SDL_BUTTON_LEFT)
	// 	apply_render(w->sdl.render, w->sdl.textures[texture_wood_door], NULL, NULL);
	return (true);
}
