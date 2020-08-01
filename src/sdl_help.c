/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_help.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 18:42:09 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/08/01 09:26:27 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	apply_surface(SDL_Surface *source, SDL_Surface *destination,
		SDL_Rect offset)
{
	SDL_BlitSurface(source, NULL, destination, &offset);
}

void	apply_surface_scaled(SDL_Surface *source,
		SDL_Surface *destination, SDL_Rect offset)
{
	SDL_BlitScaled(source, NULL, destination, &offset);
}

void	apply_render(SDL_Renderer *render, SDL_Texture *texture,
		SDL_Rect *srcrect, const SDL_Rect *dstrect)
{
	SDL_RenderClear(render);
	SDL_RenderCopy(render, texture, srcrect, dstrect);
	SDL_RenderPresent(render);
}

void	clear_screen(SDL_Renderer *render)
{
	SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
	SDL_RenderClear(render);
}

bool	event_exit(t_wolf *wolf)
{
	if (wolf->sdl.event.type == SDL_QUIT ||
	(wolf->sdl.event.type == SDL_KEYDOWN &&
	wolf->sdl.event.key.keysym.sym == SDLK_ESCAPE))
		return (true);
	else
		return (false);
}
