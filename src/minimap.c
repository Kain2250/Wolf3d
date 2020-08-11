/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarc <mcarc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 17:53:36 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/08/11 10:26:14 by mcarc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

double		angle(t_wolf *wolf)
{
	if (wolf->player.dir_y >= 0)
		return (acos(wolf->player.dir_x) * 180 / M_PI);
	return (-(acos(wolf->player.dir_x) * 180 / M_PI));
}

static void	put_player(t_wolf *wolf)
{
	SDL_Rect	rect;

	rect.x = wolf->player.pos_y * wolf->sdl.map_width / wolf->location.x_len
		- 3;
	rect.y = HEIGHT_MAP / 2;
	rect.h = 5;
	rect.w = 5;
	SDL_SetRenderDrawColor(wolf->sdl.map_render, 255, 0, 0, 0);
	SDL_RenderFillRect(wolf->sdl.map_render, &rect);
	SDL_RenderDrawLineF(wolf->sdl.map_render, wolf->player.dir_y * 20
		+ rect.x,
	wolf->player.dir_x * 20 + rect.y, rect.x + 2, rect.y + 2);
}

void		draw_map(t_wolf *wolf, SDL_FRect rect)
{
	int			x;
	int			y;
	SDL_FRect	rect2;

	y = 0;
	while (y < wolf->location.y_len)
	{
		x = 0;
		rect.x = 0;
		while (x < wolf->location.x_len)
		{
			rect2 = rect;
			rect2.y -= wolf->player.pos_x * wolf->sdl.map_width
				/ wolf->location.x_len;
			if (wolf->location.map[y][x] != '0')
				SDL_RenderCopyF(wolf->sdl.map_render,
					wolf->sdl.textures[map_cell], NULL, &rect2);
			rect.x += wolf->sdl.map_width / wolf->location.x_len;
			x++;
		}
		rect.y += wolf->sdl.map_width / wolf->location.x_len;
		y++;
	}
}

void		minimap_output(t_wolf *wolf)
{
	SDL_FRect	rect;

	if (wolf->location.minimap == false)
		return ;
	rect.y = 100;
	rect.h = wolf->sdl.map_width / wolf->location.x_len;
	rect.w = wolf->sdl.map_width / wolf->location.x_len;
	SDL_SetRenderDrawColor(wolf->sdl.map_render, 200, 150, 50, 0);
	SDL_RenderClear(wolf->sdl.map_render);
	draw_map(wolf, rect);
	put_player(wolf);
	SDL_RenderPresent(wolf->sdl.map_render);
}
