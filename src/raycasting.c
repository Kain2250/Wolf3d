/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 19:45:30 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/08/01 18:23:10 by bdrinkin         ###   ########.fr       */
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

	if (Mix_PlayingMusic() == 0)
		Mix_PlayMusic(wolf->sdl.mix.music[mix_game], 1);
	SDL_GetWindowSize(wolf->sdl.window, &wolf->sdl.width, &wolf->sdl.height);
	clear_screen(wolf->sdl.render);
	x_screen = 0;
	width = wolf->sdl.width;
	walls = ft_memalloc(sizeof(t_walls));
	while (x_screen < wolf->sdl.width)
	{
		cam_and_screen_setup(wolf, x_screen, width);
		ray_computation(wolf);
		find_hit(wolf);
		getting_the_height_to_the_wall(wolf, walls);
		calculate_foog(wolf, walls);
		render_screen(walls, x_screen, x_screen, wolf);
		x_screen++;
		free(walls->color);
	}
	SDL_RenderPresent(wolf->sdl.render);
	return (0);
}
