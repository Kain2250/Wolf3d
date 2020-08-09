/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 17:53:36 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/08/09 18:40:28 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		minimap_output(t_wolf *wolf)
{
	int			x;
	int			y;
	SDL_Rect	rect;

	y = 0;
	rect.y = 10;
	rect.h = 10;
	rect.w = 10;
	while (y < wolf->location.y_len)
	{
		x = 0;
		rect.x = 10;
		while (x < wolf->location.x_len)
		{
			SDL_SetRenderDrawColor(wolf->sdl.render, 150, 100, 150, 0);
			wolf->location.map[y][x] == '0' ?
			SDL_RenderDrawRect(wolf->sdl.render, &rect) :
			SDL_RenderFillRect(wolf->sdl.render, &rect);
			rect.x += 10;
			x++;
			SDL_SetRenderDrawColor(wolf->sdl.render, 255, 0, 0, 0);
			SDL_RenderDrawPointF(wolf->sdl.render,
			wolf->player.pos_y * 10 + 10, wolf->player.pos_x * 10 + 10);
		}
		rect.y += 10;
		y++;
	}
}