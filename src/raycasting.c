/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarc <mcarc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 19:45:30 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/08/04 15:42:06 by mcarc            ###   ########.fr       */
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

void			render_texture(t_wolf *wolf, t_walls *walls, int x1)
{
	SDL_Rect	rect;
	SDL_Rect	rect_wall;
    double		wall_x;
	int			tex_x;
	int			qwe;

	qwe = TEXT_SIZE;
    if (wolf->player.side == 0)
		wall_x = wolf->player.pos_y + wolf->player.perp_wall_dist * wolf->player.ray_dir_y;
    else
		wall_x = wolf->player.pos_x + wolf->player.perp_wall_dist * wolf->player.ray_dir_x;
    wall_x -= floor(wall_x);
    tex_x = (int)(wall_x * (double)TEXT_SIZE);
    if (wolf->player.side == 0 && wolf->player.ray_dir_x > 0)
		tex_x = TEXT_SIZE - tex_x - 1;
    if (wolf->player.side == 1 && wolf->player.ray_dir_y < 0)
		tex_x = TEXT_SIZE - tex_x - 1;
	rect_wall.h = walls->draw_end - walls->draw_start;
	rect_wall.w = 1;
	rect_wall.x = x1;
	rect_wall.y = walls->draw_start;
	rect.x = tex_x;
	rect.y = 0;
	rect.h = TEXT_SIZE;
	rect.w = 1;
	SDL_SetRenderDrawColor(wolf->sdl.render, COLOR_SKY);
	SDL_RenderDrawLine(wolf->sdl.render, x1, 0, x1, walls->draw_start);
	side_determination(wolf);
	render_blocks(wolf,rect,rect_wall);
	SDL_SetRenderDrawColor(wolf->sdl.render, COLOR_FLOR);
	SDL_RenderDrawLine(wolf->sdl.render, x1,
	walls->draw_end, x1, wolf->sdl.height);
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
		if (wolf->location.color_mode == false)
			render_texture(wolf, walls, x_screen);
		else
			render_screen(walls, x_screen, x_screen, wolf);
		x_screen++;
		free(walls->color);
	}
	SDL_RenderPresent(wolf->sdl.render);
	return (0);
}
