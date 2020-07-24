/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evelt_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 19:53:50 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/07/23 18:56:45 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <time.h>

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

void			event_key_hook(t_wolf *wolf)
{
	double		old_dir_x;
	double		old_plane_x;

	if (wolf->sdl.event.key.keysym.sym == SDLK_w)
	{
		if (wolf->location.map[(int)(wolf->player.pos_x + wolf->player.dir_x * wolf->mouse.move_speed)][(int)wolf->player.pos_y] == '0')
			wolf->player.pos_x += wolf->player.dir_x * wolf->mouse.move_speed;
		if (wolf->location.map[(int)wolf->player.pos_x][(int)(wolf->player.pos_y + wolf->player.dir_y * wolf->mouse.move_speed)] == '0')
			wolf->player.pos_y += wolf->player.dir_y * wolf->mouse.move_speed;
	}
	else if (wolf->sdl.event.key.keysym.sym == SDLK_s)
	{
		if (wolf->location.map[(int)(wolf->player.pos_x + wolf->player.dir_x * wolf->mouse.move_speed)][(int)wolf->player.pos_y] == '0')
			wolf->player.pos_x -= wolf->player.dir_x * wolf->mouse.move_speed;
		if (wolf->location.map[(int)wolf->player.pos_x][(int)(wolf->player.pos_y + wolf->player.dir_y * wolf->mouse.move_speed)] == '0')
			wolf->player.pos_y -= wolf->player.dir_y * wolf->mouse.move_speed;
	}
	else if (wolf->sdl.event.key.keysym.sym == SDLK_d)
	{
		old_dir_x = wolf->player.dir_x;
		wolf->player.dir_x = wolf->player.dir_x * cos(-wolf->mouse.rot_speed) - wolf->player.dir_y * sin(-wolf->mouse.rot_speed);
		wolf->player.dir_y = old_dir_x * sin(-wolf->mouse.rot_speed) + wolf->player.dir_y * cos(-wolf->mouse.rot_speed);
		old_plane_x = wolf->player.plane_x;
		wolf->player.plane_x = wolf->player.plane_x * cos(-wolf->mouse.rot_speed) - wolf->player.plane_y * sin(-wolf->mouse.rot_speed);
		wolf->player.plane_y = old_plane_x * sin(-wolf->mouse.rot_speed) + wolf->player.plane_y * cos(-wolf->mouse.rot_speed);
	}
	else if (wolf->sdl.event.key.keysym.sym == SDLK_a)
	{
		old_dir_x = wolf->player.dir_x;
		wolf->player.dir_x = wolf->player.dir_x * cos(wolf->mouse.rot_speed) - wolf->player.dir_y * sin(wolf->mouse.rot_speed);
		wolf->player.dir_y = old_dir_x * sin(wolf->mouse.rot_speed) + wolf->player.dir_y * cos(wolf->mouse.rot_speed);
		old_plane_x = wolf->player.plane_x;
		wolf->player.plane_x = wolf->player.plane_x * cos(wolf->mouse.rot_speed) - wolf->player.plane_y * sin(wolf->mouse.rot_speed);
		wolf->player.plane_y = old_plane_x * sin(wolf->mouse.rot_speed) + wolf->player.plane_y * cos(wolf->mouse.rot_speed);
	}
	SDL_SetRenderDrawColor(wolf->sdl.render, 0, 0, 0, 0);
	SDL_RenderClear(wolf->sdl.render);
	raycasting(wolf);
	SDL_RenderPresent(wolf->sdl.render);
}

bool			event_list(t_wolf *wolf)
{
	SDL_WaitEvent(&wolf->sdl.event);
	if (event_exit(wolf) == true)
		wolf->quit = true;
	fps_counter(wolf);
	if (wolf->sdl.event.type == SDL_KEYDOWN &&
		(wolf->sdl.event.key.keysym.sym == SDLK_a ||
		wolf->sdl.event.key.keysym.sym == SDLK_s ||
		wolf->sdl.event.key.keysym.sym == SDLK_w ||
		wolf->sdl.event.key.keysym.sym == SDLK_d))
	{
		event_key_hook(wolf);
	}
	// else if (w->sdl.event.button.button == SDL_BUTTON_RIGHT)
	// apply_render(w->sdl.render, w->sdl.textures[texture_sand], NULL, NULL);
	// else if (w->sdl.event.button.button == SDL_BUTTON_LEFT)
	// 	apply_render(w->sdl.render, w->sdl.textures[texture_wood_door], NULL, NULL);
	return (true);
}
