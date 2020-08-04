/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_help.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 18:42:09 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/08/04 22:38:11 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

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
