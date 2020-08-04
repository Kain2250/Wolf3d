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
	// if (wolf->location.color_mode == true)
	// {
	// 	if (wolf->player.side == 1)

	// }
	// else
	// {
		walls->color = color_cahge(wolf->location.map,
		wolf->player.map_x, wolf->player.map_y);
		if (wolf->player.side == 1)
			brightness_calc(walls->color);
	// }
	
}
void			rect_init(t_walls *walls, int x1, SDL_Rect rect[2], int tex_x)
{
	rect[1].h = walls->draw_end - walls->draw_start;
	rect[1].w = 1;
	rect[1].x = x1;
	rect[1].y = walls->draw_start;
	rect[0].x = tex_x;
	rect[0].y = 0;
	rect[0].h = TEXT_SIZE;
	rect[0].w = 1;
}

void			wall_definition(t_wolf *wolf, SDL_Rect rect[2])
{
	if (wolf->location.map[wolf->player.map_x][wolf->player.map_y] == '2')
		SDL_RenderCopy(wolf->sdl.render, wolf->sdl.textures[texture_gold_fass],
		&rect[0], &rect[1]);
	else if (wolf->location.map[wolf->player.map_x][wolf->player.map_y] == '1')
		SDL_RenderCopy(wolf->sdl.render, wolf->sdl.textures[texture_steel_cuz],
		&rect[0], &rect[1]);
	else if (wolf->location.map[wolf->player.map_x][wolf->player.map_y] == '3')
		SDL_RenderCopy(wolf->sdl.render, wolf->sdl.textures[texture_steel_panel],
		&rect[0], &rect[1]);
	else if (wolf->location.map[wolf->player.map_x][wolf->player.map_y] == '4')
		SDL_RenderCopy(wolf->sdl.render, wolf->sdl.textures[texture_gray_brick],
		&rect[0], &rect[1]);
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
	}
	SDL_RenderPresent(wolf->sdl.render);
	return (0);
}
