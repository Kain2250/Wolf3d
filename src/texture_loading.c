/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loading.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 15:03:46 by mcarc             #+#    #+#             */
/*   Updated: 2020/08/10 19:08:51 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		check_render_mode(t_wolf *wolf, SDL_Rect rect[2])
{
	if (wolf->location.color_mode == mode_cardinal)
	{
		side_determination(wolf);
		render_blocks(wolf, rect);
	}
	else if (wolf->location.color_mode == mode_texture)
		wall_definition(wolf, rect);
}

static void	dop_load(SDL_Texture **textures, SDL_Renderer *render)
{
	textures[texture_gold_fass] = IMG_LoadTexture(render, TEX_GOLD_FASS);
	textures[texture_gold_fass_n] = IMG_LoadTexture(render, TEX_GOLD_FASS_N);
	textures[texture_gold_fass_s] = IMG_LoadTexture(render, TEX_GOLD_FASS_S);
	textures[texture_gold_fass_e] = IMG_LoadTexture(render, TEX_GOLD_FASS_E);
	textures[texture_gold_fass_w] = IMG_LoadTexture(render, TEX_GOLD_FASS_W);
	textures[texture_brick] = IMG_LoadTexture(render, TEX_BRICK);
	textures[texture_brick_n] = IMG_LoadTexture(render, TEX_BRICK_N);
	textures[texture_brick_s] = IMG_LoadTexture(render, TEX_BRICK_S);
	textures[texture_brick_e] = IMG_LoadTexture(render, TEX_BRICK_E);
	textures[texture_brick_w] = IMG_LoadTexture(render, TEX_BRICK_W);
	textures[texture_wind_wood] = IMG_LoadTexture(render, TEX_WIND_WOOD);
	textures[texture_button_start] = IMG_LoadTexture(render, TEX_BUTTON_START);
	textures[texture_button_exit] = IMG_LoadTexture(render, TEX_BUTTON_EXIT);
}

void		load_textures(SDL_Texture **textures, SDL_Renderer *render)
{
	textures[texture_main_menu] = IMG_LoadTexture(render, TEX_MENU);
	textures[texture_main_leg] = IMG_LoadTexture(render, TEX_MENU_LEG);
	textures[texture_steel_panel] = IMG_LoadTexture(render, TEX_STEEL_PANEL);
	textures[texture_steel_panel_n] =
	IMG_LoadTexture(render, TEX_STEEL_PANEL_N);
	textures[texture_steel_panel_s] =
	IMG_LoadTexture(render, TEX_STEEL_PANEL_S);
	textures[texture_steel_panel_e] =
	IMG_LoadTexture(render, TEX_STEEL_PANEL_E);
	textures[texture_steel_panel_w] =
	IMG_LoadTexture(render, TEX_STEEL_PANEL_W);
	textures[texture_gray_brick] = IMG_LoadTexture(render, TEX_GRAY_BRICK);
	textures[texture_steel_cuz] = IMG_LoadTexture(render, TEX_STEEL_CUZ);
	textures[texture_steel_cuz_n] = IMG_LoadTexture(render, TEX_STEEL_CUZ_N);
	textures[texture_steel_cuz_s] = IMG_LoadTexture(render, TEX_STEEL_CUZ_S);
	textures[texture_steel_cuz_e] = IMG_LoadTexture(render, TEX_STEEL_CUZ_E);
	textures[texture_steel_cuz_w] = IMG_LoadTexture(render, TEX_STEEL_CUZ_W);
	dop_load(textures, render);
}
