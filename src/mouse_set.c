/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarc <mcarc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 19:07:45 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/08/04 15:42:04 by mcarc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

	// if (wolf->location.map[wolf->player.map_x][wolf->player.map_y] == '1')
	// {
	// 	if (wolf->player.side == 1)
	// 	{
	// 		SDL_GetTextureColorMod(wolf->sdl.textures[texture_wood_box], &walls->color->r, &walls->color->g, &walls->color->b);
	// 		SDL_SetTextureColorMod(wolf->sdl.textures[texture_wood_box], walls->color->r / 2, walls->color->g / 2, walls->color->b / 2);
	// 	}
	// 	SDL_RenderCopy(wolf->sdl.render, wolf->sdl.textures[texture_wood_box], &rect_wall, &rect_wall);
	// }
	// else if (wolf->location.map[wolf->player.map_x][wolf->player.map_y] == '2')
	// {
	// 	if (wolf->player.side == 1)
	// 	{
	// 		SDL_GetTextureColorMod(wolf->sdl.textures[texture_wood_door], &walls->color->r, &walls->color->g, &walls->color->b);
	// 		SDL_SetTextureColorMod(wolf->sdl.textures[texture_wood_door], walls->color->r / 2, walls->color->g / 2, walls->color->b / 2);
	// 	}
	// 	SDL_RenderCopy(wolf->sdl.render, wolf->sdl.textures[texture_wood_door], &rect, &rect_wall);
	// }
	// else if (wolf->location.map[wolf->player.map_x][wolf->player.map_y] == '3')
	// {
	// 	if (wolf->player.side == 1)
	// 	{
	// 		SDL_GetTextureColorMod(wolf->sdl.textures[texture_sand], &walls->color->r, &walls->color->g, &walls->color->b);
	// 		SDL_SetTextureColorMod(wolf->sdl.textures[texture_sand], walls->color->r / 2, walls->color->g / 2, walls->color->b / 2);
	// 	}
	// 	SDL_RenderCopy(wolf->sdl.render, wolf->sdl.textures[texture_sand], &rect, &rect_wall);
	// }
	// else if (wolf->location.map[wolf->player.map_x][wolf->player.map_y] == '4')
	// {
	// 	if (wolf->player.side == 1)
	// 	{
	// 		SDL_GetTextureColorMod(wolf->sdl.textures[texture_concrete], &walls->color->r, &walls->color->g, &walls->color->b);
	// 		SDL_SetTextureColorMod(wolf->sdl.textures[texture_concrete], walls->color->r / 2, walls->color->g / 2, walls->color->b / 2);
	// 	}
	// 	SDL_RenderCopy(wolf->sdl.render, wolf->sdl.textures[texture_concrete], &rect, &rect_wall);
	// }
//if (wolf->sdl.event.motion.xrel && wolf->sdl.event.motion.yrel)
//{
//rotate_plane_and_cam(wolf, -(wolf->sdl.event.motion.xrel)
//* wolf->mouse.rot_speed * 0.5);
//wolf->player.sit += -atan(wolf->sdl.event.motion.yrel)
//+ wolf->mouse.rot_speed * 0.5;
//}
//else
//{
//rotate_plane_and_cam(wolf, -(wolf->sdl.event.motion.xrel)
//* wolf->mouse.rot_speed);
//wolf->player.sit += -(wolf->sdl.event.motion.yrel)
//+ wolf->mouse.rot_speed * 0.5;
//}