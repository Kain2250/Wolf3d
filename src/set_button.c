/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_button.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 10:14:26 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/08/01 10:32:24 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

bool		is_button_area(SDL_MouseButtonEvent event,
			SDL_Rect *area, int button)
{
	if (event.button == button && (event.type == SDL_MOUSEBUTTONDOWN ||
		event.type == SDL_MOUSEBUTTONUP) &&
		(event.x > area->x && event.x < area->w + area->x) &&
		(event.y > area->y && event.y < area->h + area->y))
		return (true);
	return (false);
}

void		set_button(t_wolf *wolf)
{
	if (wolf->menu.button_new != NULL)
		free(wolf->menu.button_new);
	if (wolf->menu.button_exit != NULL)
		free(wolf->menu.button_exit);
	wolf->menu.button_new = (SDL_Rect *)ft_memalloc(sizeof(SDL_Rect));
	wolf->menu.button_exit = (SDL_Rect *)ft_memalloc(sizeof(SDL_Rect));
	SDL_GetWindowSize(wolf->sdl.window, &wolf->sdl.width, &wolf->sdl.height);
	wolf->menu.button_new->h = 70;
	wolf->menu.button_new->w = 200;
	wolf->menu.button_new->x = wolf->sdl.width / 3 * 2;
	wolf->menu.button_new->y = wolf->sdl.height / 3 * 2;
	wolf->menu.button_exit->h = 70;
	wolf->menu.button_exit->w = 180;
	wolf->menu.button_exit->x = wolf->sdl.width / 3 * 2;
	wolf->menu.button_exit->y = wolf->sdl.height / 7 * 5.2;
}
