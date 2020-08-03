/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_raysting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 19:41:42 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/08/03 15:18:22 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			render_screen(t_walls *walls, int x, int y, t_wolf *wolf)
{
	SDL_SetRenderDrawColor(wolf->sdl.render, COLOR_SKY);
	SDL_RenderDrawLine(wolf->sdl.render, x, 0, x, walls->draw_start);
	SDL_SetRenderDrawColor(wolf->sdl.render, walls->color->r,
	walls->color->g, walls->color->b, walls->color->a);
	SDL_RenderDrawLine(wolf->sdl.render, x,
	walls->draw_start, y, walls->draw_end);
	SDL_SetRenderDrawColor(wolf->sdl.render, COLOR_FLOR);
	SDL_RenderDrawLine(wolf->sdl.render, x,
	walls->draw_end, x, wolf->sdl.height);
}

void			getting_the_height_to_the_wall(t_wolf *wolf, t_walls *walls)
{
	walls->line_height = (int)(wolf->sdl.height / wolf->player.perp_wall_dist);
	walls->draw_start = -walls->line_height / 2 + wolf->sdl.height /
	2 + wolf->player.sit;
	walls->draw_end = walls->line_height / 2 + wolf->sdl.height /
	2 + wolf->player.sit;
}

void			find_hit(t_wolf *wolf)
{
	while (wolf->player.hit == 0)
	{
		if (wolf->player.side_dist_x < wolf->player.side_dist_y)
		{
			wolf->player.side_dist_x += wolf->player.delta_dist_x;
			wolf->player.map_x += wolf->player.step_x;
			wolf->player.side = 0;
		}
		else
		{
			wolf->player.side_dist_y += wolf->player.delta_dist_y;
			wolf->player.map_y += wolf->player.step_y;
			wolf->player.side = 1;
		}
		if (wolf->location.map[wolf->player.map_x][wolf->player.map_y] > '0')
			wolf->player.hit = 1;
	}
	if (wolf->player.side == 0)
		wolf->player.perp_wall_dist = (wolf->player.map_x - wolf->player.pos_x
		+ (1 - wolf->player.step_x) / 2) / wolf->player.ray_dir_x;
	else
		wolf->player.perp_wall_dist = (wolf->player.map_y - wolf->player.pos_y
		+ (1 - wolf->player.step_y) / 2) / wolf->player.ray_dir_y;
}

void			ray_computation(t_wolf *wolf)
{
	if (wolf->player.ray_dir_x < 0)
	{
		wolf->player.step_x = -1;
		wolf->player.side_dist_x = (wolf->player.pos_x - wolf->player.map_x) *
		wolf->player.delta_dist_x;
	}
	else
	{
		wolf->player.step_x = 1;
		wolf->player.side_dist_x = (wolf->player.map_x + 1.0 -
		wolf->player.pos_x) * wolf->player.delta_dist_x;
	}
	if (wolf->player.ray_dir_y < 0)
	{
		wolf->player.step_y = -1;
		wolf->player.side_dist_y = wolf->player.delta_dist_y *
		(wolf->player.pos_y - wolf->player.map_y);
	}
	else
	{
		wolf->player.step_y = 1;
		wolf->player.side_dist_y = (wolf->player.map_y + 1.0 -
		wolf->player.pos_y) * wolf->player.delta_dist_y;
	}
}

void			cam_and_screen_setup(t_wolf *wolf, int x_screen, double width)
{
	wolf->player.camera_x = 2 * x_screen / width - 1;
	wolf->player.ray_dir_x = wolf->player.dir_x + wolf->player.plane_x *
	wolf->player.camera_x;
	wolf->player.ray_dir_y = wolf->player.dir_y + wolf->player.plane_y *
	wolf->player.camera_x;
	wolf->player.map_x = (int)wolf->player.pos_x;
	wolf->player.map_y = (int)wolf->player.pos_y;
	wolf->player.hit = 0;
	wolf->player.delta_dist_x = calc_dist(wolf->player.ray_dir_y,
	wolf->player.ray_dir_x);
	wolf->player.delta_dist_y = calc_dist(wolf->player.ray_dir_x,
	wolf->player.ray_dir_y);
}
