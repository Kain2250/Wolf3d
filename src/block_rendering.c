/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_rendering.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 14:51:29 by mcarc             #+#    #+#             */
/*   Updated: 2020/08/04 21:24:48 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

// void	render_first_block(t_wolf *wolf, SDL_Rect rect[2])
// {
// 	if (wolf->player.cardinal == cardinal_north)
// 		SDL_RenderCopy(wolf->sdl.render, wolf->sdl.textures[texture_gold_fass_n], &rect[0], &rect[1]);
// 	else if (wolf->player.cardinal == cardinal_south)
// 		SDL_RenderCopy(wolf->sdl.render, wolf->sdl.textures[texture_gold_fass_s], &rect[0], &rect[1]);
// 	else if (wolf->player.cardinal == cardinal_east)
// 		SDL_RenderCopy(wolf->sdl.render, wolf->sdl.textures[texture_gold_fass_e], &rect[0], &rect[1]);
// 	else
// 		SDL_RenderCopy(wolf->sdl.render, wolf->sdl.textures[texture_gold_fass_w], &rect[0], &rect[1]);
// }
// void	render_second_block(t_wolf *wolf, SDL_Rect rect[2])
// {
// 	if (wolf->player.cardinal == cardinal_north)
// 		SDL_RenderCopy(wolf->sdl.render, wolf->sdl.textures[texture_steel_cuz_n], &rect[0], &rect[1]);
// 	else if (wolf->player.cardinal == cardinal_south)
// 		SDL_RenderCopy(wolf->sdl.render, wolf->sdl.textures[texture_steel_cuz_s], &rect[0], &rect[1]);
// 	else if (wolf->player.cardinal == cardinal_east)
// 		SDL_RenderCopy(wolf->sdl.render, wolf->sdl.textures[texture_steel_cuz_e], &rect[0], &rect[1]);
// 	else
// 		SDL_RenderCopy(wolf->sdl.render, wolf->sdl.textures[texture_steel_cuz_w], &rect[0], &rect[1]);
// }
// void	render_third_block(t_wolf *wolf, SDL_Rect rect[2])
// {
// 	if (wolf->player.cardinal == cardinal_north)
// 		SDL_RenderCopy(wolf->sdl.render, wolf->sdl.textures[texture_steel_panel_n], &rect[0], &rect[1]);
// 	else if (wolf->player.cardinal == cardinal_south)
// 		SDL_RenderCopy(wolf->sdl.render, wolf->sdl.textures[texture_steel_panel_s], &rect[0], &rect[1]);
// 	else if (wolf->player.cardinal == cardinal_east)
// 		SDL_RenderCopy(wolf->sdl.render, wolf->sdl.textures[texture_steel_panel_e], &rect[0], &rect[1]);
// 	else
// 		SDL_RenderCopy(wolf->sdl.render, wolf->sdl.textures[texture_steel_panel_w], &rect[0], &rect[1]);
// }

// void	render_fourth_block(t_wolf *wolf, SDL_Rect rect[2])
// {
// 	if (wolf->player.cardinal == cardinal_north)
// 		SDL_RenderCopy(wolf->sdl.render, wolf->sdl.textures[texture_brick_n], &rect[0], &rect[1]);
// 	else if (wolf->player.cardinal == cardinal_south)
// 		SDL_RenderCopy(wolf->sdl.render, wolf->sdl.textures[texture_brick_s], &rect[0], &rect[1]);
// 	else if (wolf->player.cardinal == cardinal_east)
// 		SDL_RenderCopy(wolf->sdl.render, wolf->sdl.textures[texture_brick_e], &rect[0], &rect[1]);
// 	else
// 		SDL_RenderCopy(wolf->sdl.render, wolf->sdl.textures[texture_brick_w], &rect[0], &rect[1]);
// }

void	render_all_block(t_wolf *wolf, SDL_Rect rect[2], int texture)
{
	int	text_cur;

	text_cur = texture;
	if (wolf->player.cardinal == cardinal_north)
		text_cur += 0;
	else if (wolf->player.cardinal == cardinal_south)
		text_cur += 1;
	else if (wolf->player.cardinal == cardinal_east)
		text_cur += 2;
	else
		text_cur += 3;
	shadow_render(wolf, text_cur, rect);
}

void	render_blocks(t_wolf *wolf, SDL_Rect rect[2])
{
	if (wolf->location.map[wolf->player.map_x][wolf->player.map_y] == '1')
		render_all_block(wolf, rect, texture_gold_fass_n);
	else if (wolf->location.map[wolf->player.map_x][wolf->player.map_y] == '2')
		render_all_block(wolf, rect, texture_steel_cuz_n);
	else if (wolf->location.map[wolf->player.map_x][wolf->player.map_y] == '3')
		render_all_block(wolf, rect, texture_steel_panel_n);
	else if (wolf->location.map[wolf->player.map_x][wolf->player.map_y] == '4')
		render_all_block(wolf, rect, texture_brick_n);
	// if (wolf->location.map[wolf->player.map_x][wolf->player.map_y] == '1')
	// 	render_first_block(wolf, rect);
	// else if (wolf->location.map[wolf->player.map_x][wolf->player.map_y] == '2')
	// 	render_second_block(wolf, rect);
	// else if (wolf->location.map[wolf->player.map_x][wolf->player.map_y] == '3')
	// 	render_third_block(wolf, rect);
	// else if (wolf->location.map[wolf->player.map_x][wolf->player.map_y] == '4')
	// 	render_fourth_block(wolf, rect);
}
