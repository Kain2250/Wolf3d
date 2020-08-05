/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_rendering.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarc <mcarc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 14:51:29 by mcarc             #+#    #+#             */
/*   Updated: 2020/08/05 15:37:01 by mcarc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			shadow_render(t_wolf *wolf, int num_text, SDL_Rect rect[2])
{
	if (wolf->player.side == 1)
	{
		SDL_SetTextureColorMod(wolf->sdl.textures[num_text], 140, 140, 140);
		SDL_RenderCopy(wolf->sdl.render, wolf->sdl.textures[num_text],
			&rect[0], &rect[1]);
		SDL_SetTextureColorMod(wolf->sdl.textures[num_text], 255, 255, 255);
	}
	else
		SDL_RenderCopy(wolf->sdl.render, wolf->sdl.textures[num_text],
			&rect[0], &rect[1]);
}

void			wall_definition(t_wolf *wolf, SDL_Rect rect[2])
{
	if (wolf->location.map[wolf->player.map_x][wolf->player.map_y] == '2')
		shadow_render(wolf, texture_gold_fass, rect);
	else if (wolf->location.map[wolf->player.map_x][wolf->player.map_y] == '1')
		shadow_render(wolf, texture_steel_cuz, rect);
	else if (wolf->location.map[wolf->player.map_x][wolf->player.map_y] == '3')
		shadow_render(wolf, texture_steel_panel, rect);
	else if (wolf->location.map[wolf->player.map_x][wolf->player.map_y] == '4')
		shadow_render(wolf, texture_gray_brick, rect);
}

void			render_texture(t_wolf *wolf, t_walls *walls, int x1)
{
	SDL_Rect	rect[2];
	double		wall_x;
	int			tex_x;

	if (wolf->player.side == 0)
		wall_x = wolf->player.pos_y + wolf->player.perp_wall_dist *
		wolf->player.ray_dir_y;
	else
		wall_x = wolf->player.pos_x + wolf->player.perp_wall_dist *
		wolf->player.ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)TEXT_SIZE);
	if (wolf->player.side == 0 && wolf->player.ray_dir_x > 0)
		tex_x = TEXT_SIZE - tex_x - 1;
	if (wolf->player.side == 1 && wolf->player.ray_dir_y < 0)
		tex_x = TEXT_SIZE - tex_x - 1;
	rect_init(walls, x1, rect, tex_x);
	SDL_SetRenderDrawColor(wolf->sdl.render, COLOR_SKY);
	SDL_RenderDrawLine(wolf->sdl.render, x1, 0, x1, walls->draw_start);
	check_render_mode(wolf, rect);
	SDL_SetRenderDrawColor(wolf->sdl.render, COLOR_FLOR);
	SDL_RenderDrawLine(wolf->sdl.render, x1,
	walls->draw_end, x1, wolf->sdl.height);
}

void			render_all_block(t_wolf *wolf, SDL_Rect rect[2], int texture)
{
	int			text_cur;

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

void			render_blocks(t_wolf *wolf, SDL_Rect rect[2])
{
	if (wolf->location.map[wolf->player.map_x][wolf->player.map_y] == '1')
		render_all_block(wolf, rect, texture_gold_fass_n);
	else if (wolf->location.map[wolf->player.map_x][wolf->player.map_y] == '2')
		render_all_block(wolf, rect, texture_steel_cuz_n);
	else if (wolf->location.map[wolf->player.map_x][wolf->player.map_y] == '3')
		render_all_block(wolf, rect, texture_steel_panel_n);
	else if (wolf->location.map[wolf->player.map_x][wolf->player.map_y] == '4')
		render_all_block(wolf, rect, texture_brick_n);
}
