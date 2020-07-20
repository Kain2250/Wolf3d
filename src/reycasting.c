/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 19:45:30 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/07/20 17:18:12 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		filling_var(t_wolf *wolf)
{
	wolf->player.pos_x = 9;
	wolf->player.pos_y = 11;
	wolf->player.dir_x = -1;
	wolf->player.dir_y = 0;
	wolf->player.plane_x = 0;
	wolf->player.plane_y = 0.66;
	wolf->player.time = 0;
	wolf->player.old_time = 0;
}

float			calc_dist(float ray_dir_1, float ray_dir_2)
{
	float		delta_dist;

	if (ray_dir_1 == 0)
		delta_dist = 0;
	else if (ray_dir_2 == 0)
		delta_dist = 1;
	else
		delta_dist = fabsf(1 / ray_dir_2);
	return (delta_dist);
}

SDL_Color		*color_cahge(char **map, int x, int y)
{
	SDL_Color	*color;

	color = ft_memalloc(sizeof(SDL_Color));
	if (map[x][y] == '1')
	{
		color->r = 255;
		color->a = 0;
		color->b = 100;
		color->g = 50;
	}
	else if (map[x][y] == '2')
	{
		color->r = 0;
		color->a = 0;
		color->b = 255;
		color->g = 100;
	}
	else if (map[x][y] == '3')
	{
		color->r = 0;
		color->a = 0;
		color->b = 100;
		color->g = 255;
	}
	else if (map[x][y] == '4')
	{
		color->r = 100;
		color->a = 0;
		color->b = 170;
		color->g = 190;
	}
	return (color);
}

void		brightness_calc(SDL_Color *color)
{
	color->r /= 2;
	color->g /= 2;
	color->b /= 2;
}

int				raycasting(t_wolf *wolf)
{
	int		x;
	float	w;
	int		line_height;
	int		draw_start;
	int		draw_end;
	SDL_Color	*color;

	x = 0;
	w = WIDTH_WIN;
	while (x < (int)WIDTH_WIN)
	{
		wolf->player.camera_x = 2 * x / w - 1;
		wolf->player.ray_dir_x = wolf->player.dir_x + wolf->player.plane_x * wolf->player.camera_x;
		wolf->player.ray_dir_y = wolf->player.dir_y + wolf->player.plane_y * wolf->player.camera_x;
		wolf->player.map_x = (int)wolf->player.pos_x;
		wolf->player.map_y = (int)wolf->player.pos_y;
		wolf->player.hit = 0;
		wolf->player.delta_dist_x = calc_dist(wolf->player.ray_dir_y, wolf->player.ray_dir_x);
		wolf->player.delta_dist_y = calc_dist(wolf->player.ray_dir_x, wolf->player.ray_dir_y);
		if (wolf->player.ray_dir_x < 0)
		{
			wolf->player.step_x = -1;
			wolf->player.side_dist_x = (wolf->player.pos_x - wolf->player.map_x) * wolf->player.delta_dist_x;
		}
		else
		{
			wolf->player.step_x = 1;
			wolf->player.side_dist_x = (wolf->player.map_x + 1.0 - wolf->player.pos_x) * wolf->player.delta_dist_x;
		}
		if (wolf->player.ray_dir_y < 0)
		{
			wolf->player.step_y = -1;
			wolf->player.side_dist_y = (wolf->player.pos_y - wolf->player.map_y) * wolf->player.delta_dist_y;
		}
		else
		{
			wolf->player.step_y = 1;
			wolf->player.side_dist_y = (wolf->player.map_y + 1.0 - wolf->player.pos_y) * wolf->player.delta_dist_y;
		}
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
			wolf->player.perp_wall_dist = (wolf->player.map_x - wolf->player.pos_x + (1 - wolf->player.step_x) / 2) / wolf->player.ray_dir_x;
		else
			wolf->player.perp_wall_dist = (wolf->player.map_y - wolf->player.pos_y + (1 - wolf->player.step_y) / 2) / wolf->player.ray_dir_y;
		line_height = (int)(HEIGHT_WIN / wolf->player.perp_wall_dist);
		draw_start = -line_height / 2 + HEIGHT_WIN / 2;
		if (draw_start < 0)
		draw_start = 0;
		draw_end = line_height / 2 + HEIGHT_WIN / 2;
		if (draw_end >= HEIGHT_WIN)
			draw_end = HEIGHT_WIN - 1;
		color = color_cahge(wolf->location.map, wolf->player.map_x, wolf->player.map_y);
		if (wolf->player.side == 1)
		brightness_calc(color);
		SDL_SetRenderDrawColor(wolf->sdl.render, color->r, color->g, color->b, color->a);
		SDL_RenderDrawLine(wolf->sdl.render, x, draw_start, x, draw_end);
		x++;
		// free(color);
	}
	return (0);
}