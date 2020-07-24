/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 19:45:30 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/07/24 20:32:27 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

float			calc_dist(double ray_dir_1, double ray_dir_2)
{
	float		delta_dist;

	if (ray_dir_1 == 0)
		delta_dist = 0;
	else if (ray_dir_2 == 0)
		delta_dist = 1;
	else
		delta_dist = fabs(1 / ray_dir_2);
	return (delta_dist);
}

SDL_Color		*color_cahge(char **map, int x, int y)
{
	SDL_Color	*color;

	color = ft_memalloc(sizeof(SDL_Color));
	if (map[x][y] == '1')
	{
		color->r = 50;
		color->a = 255;
		color->b = 200;
		color->g = 100;
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

void			brightness_calc(SDL_Color *color)
{
	color->r /= 2;
	color->g /= 2;
	color->b /= 2;
}

void			calculate_foog(t_wolf *wolf, t_walls *walls)
{
	walls->color = color_cahge(wolf->location.map,
	wolf->player.map_x, wolf->player.map_y);
	if (wolf->player.side == 1)
		brightness_calc(walls->color);
}

int				raycasting(t_wolf *wolf)
{
	int			x_screen;
	double		width;
	t_walls		*walls;

	clear_screen(wolf->sdl.render);
	x_screen = 0;
	width = WIDTH_WIN;
	walls = ft_memalloc(sizeof(t_walls));
	while (x_screen < WIDTH_WIN)
	{
		cam_and_screen_setup(wolf, x_screen, width);
		ray_computation(wolf);
		find_hit(wolf);
		getting_the_height_to_the_wall(wolf, walls);
		calculate_foog(wolf, walls);
		render_screen(wolf->sdl.render, walls, x_screen, x_screen);
		x_screen++;
		free(walls->color);
	}
	SDL_RenderPresent(wolf->sdl.render);
	return (0);
}
