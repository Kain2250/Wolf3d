/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 17:53:36 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/08/09 20:59:18 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	put_player(t_wolf *wolf)
{
	SDL_Rect	rect;

	rect.x = wolf->player.pos_y * 10 + 10;
	rect.y = wolf->player.pos_x * 10 + 10;
	rect.h = 4;
	rect.w = 4;
	SDL_SetRenderDrawColor(wolf->sdl.render, 255, 0, 0, 0);
	SDL_RenderFillRect(wolf->sdl.render, &rect);
	SDL_RenderDrawLineF(wolf->sdl.render, wolf->player.dir_y * 40 + rect.x,
	wolf->player.dir_x * 40 + rect.y, rect.x + 2, rect.y + 2);
}

void		minimap_output(t_wolf *wolf)
{
	int			x;
	int			y;
	SDL_Rect	rect;

	if (wolf->location.minimap == false)
		return ;
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
			SDL_SetRenderDrawColor(wolf->sdl.render, 200, 150, 50, 0);
			wolf->location.map[y][x] == '0' ?
			SDL_RenderDrawRect(wolf->sdl.render, &rect) :
			SDL_RenderFillRect(wolf->sdl.render, &rect);
			 
			rect.x += 10;
			x++;
			put_player(wolf);
		}
		rect.y += 10;
		y++;
	}

}