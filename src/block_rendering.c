/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_rendering.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarc <mcarc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 14:51:29 by mcarc             #+#    #+#             */
/*   Updated: 2020/08/04 15:41:49 by mcarc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	render_first_block(t_wolf *wolf, SDL_Rect rect, SDL_Rect rect_wall)
{
	if (wolf->player.cardinal == north)
		SDL_RenderCopy(wolf->sdl.render, wolf->sdl.textures[texture_gold_fass_n], &rect, &rect_wall);
	else if (wolf->player.cardinal == south)
		SDL_RenderCopy(wolf->sdl.render, wolf->sdl.textures[texture_gold_fass_s], &rect, &rect_wall);
	else if (wolf->player.cardinal == east)
		SDL_RenderCopy(wolf->sdl.render, wolf->sdl.textures[texture_gold_fass_e], &rect, &rect_wall);
	else
		SDL_RenderCopy(wolf->sdl.render, wolf->sdl.textures[texture_gold_fass_w], &rect, &rect_wall);
}
void	render_second_block(t_wolf *wolf, SDL_Rect rect, SDL_Rect rect_wall)
{
	if (wolf->player.cardinal == north)
		SDL_RenderCopy(wolf->sdl.render, wolf->sdl.textures[texture_steel_cuz_n], &rect, &rect_wall);
	else if (wolf->player.cardinal == south)
		SDL_RenderCopy(wolf->sdl.render, wolf->sdl.textures[texture_steel_cuz_s], &rect, &rect_wall);
	else if (wolf->player.cardinal == east)
		SDL_RenderCopy(wolf->sdl.render, wolf->sdl.textures[texture_steel_cuz_e], &rect, &rect_wall);
	else
		SDL_RenderCopy(wolf->sdl.render, wolf->sdl.textures[texture_steel_cuz_w], &rect, &rect_wall);
}
void	render_third_block(t_wolf *wolf, SDL_Rect rect, SDL_Rect rect_wall)
{
	if (wolf->player.cardinal == north)
		SDL_RenderCopy(wolf->sdl.render, wolf->sdl.textures[texture_steel_panel_n], &rect, &rect_wall);
	else if (wolf->player.cardinal == south)
		SDL_RenderCopy(wolf->sdl.render, wolf->sdl.textures[texture_steel_panel_s], &rect, &rect_wall);
	else if (wolf->player.cardinal == east)
		SDL_RenderCopy(wolf->sdl.render, wolf->sdl.textures[texture_steel_panel_e], &rect, &rect_wall);
	else
		SDL_RenderCopy(wolf->sdl.render, wolf->sdl.textures[texture_steel_panel_w], &rect, &rect_wall);
}

void	render_fourth_block(t_wolf *wolf, SDL_Rect rect, SDL_Rect rect_wall)
{
	if (wolf->player.cardinal == north)
		SDL_RenderCopy(wolf->sdl.render, wolf->sdl.textures[texture_brick_n], &rect, &rect_wall);
	else if (wolf->player.cardinal == south)
		SDL_RenderCopy(wolf->sdl.render, wolf->sdl.textures[texture_brick_s], &rect, &rect_wall);
	else if (wolf->player.cardinal == east)
		SDL_RenderCopy(wolf->sdl.render, wolf->sdl.textures[texture_brick_e], &rect, &rect_wall);
	else
		SDL_RenderCopy(wolf->sdl.render, wolf->sdl.textures[texture_brick_w], &rect, &rect_wall);
}

void	render_blocks(t_wolf *wolf, SDL_Rect rect, SDL_Rect rect_wall)
{
	if (wolf->location.map[wolf->player.map_x][wolf->player.map_y] == '1')
		render_first_block(wolf, rect, rect_wall);
	else if (wolf->location.map[wolf->player.map_x][wolf->player.map_y] == '2')
		render_second_block(wolf, rect, rect_wall);
	else if (wolf->location.map[wolf->player.map_x][wolf->player.map_y] == '3')
		render_third_block(wolf, rect, rect_wall);
	else if (wolf->location.map[wolf->player.map_x][wolf->player.map_y] == '4')
		render_fourth_block(wolf, rect, rect_wall);
}
