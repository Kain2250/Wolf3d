/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_help.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarc <mcarc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 18:42:09 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/08/09 18:54:29 by mcarc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	calc_dir_def(t_wolf *wolf, int dir_def[8])
{
	dir_def[0] = wolf->location.map[(int)(wolf->player.pos_x)]
	[(int)(wolf->player.pos_y + wolf->mouse.move_speed + 0.08)] > '0' ? 0 : 1;
	dir_def[1] = wolf->location.map[(int)(wolf->player.pos_x)]
	[(int)(wolf->player.pos_y - (wolf->mouse.move_speed + 0.08))] > '0' ? 0 : 1;
	dir_def[2] = wolf->location.map
	[(int)(wolf->player.pos_x + wolf->mouse.move_speed + 0.08)]
	[(int)(wolf->player.pos_y)] > '0' ? 0 : 1;
	dir_def[3] = wolf->location.map
	[(int)(wolf->player.pos_x - wolf->mouse.move_speed - 0.08)]
	[(int)(wolf->player.pos_y)] > '0' ? 0 : 1;
	dir_def[4] = wolf->location.map
	[(int)(wolf->player.pos_x - wolf->mouse.move_speed - 0.02)]
	[(int)(wolf->player.pos_y + wolf->mouse.move_speed + 0.02)] > '0' ? 0 : 1;
	dir_def[5] = wolf->location.map
	[(int)(wolf->player.pos_x - wolf->mouse.move_speed - 0.02)]
	[(int)(wolf->player.pos_y - wolf->mouse.move_speed - 0.02)] > '0' ? 0 : 1;
	dir_def[6] = wolf->location.map
	[(int)(wolf->player.pos_x + wolf->mouse.move_speed + 0.02)]
	[(int)(wolf->player.pos_y - wolf->mouse.move_speed - 0.02)] > '0' ? 0 : 1;
	dir_def[7] = wolf->location.map
	[(int)(wolf->player.pos_x + wolf->mouse.move_speed + 0.02)]
	[(int)(wolf->player.pos_y + wolf->mouse.move_speed + 0.02)] > '0' ? 0 : 1;
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
