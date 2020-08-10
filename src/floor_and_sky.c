/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_and_sky.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 17:21:14 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/08/10 21:55:48 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static Uint32			getpixel(SDL_Surface *surface, int x, int y)
{
	int			bpp;
	Uint8		*p;

	bpp = surface->format->BytesPerPixel;
	p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	if (bpp == 1)
		return (*p);
	else if (bpp == 2)
		return (*(Uint16 *)p);
	else if (bpp == 3)
	{
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return (p[0] << 16 | p[1] << 8 | p[2]);
		else
			return (p[0] | p[1] << 8 | p[2] << 16);
	}
	else if (bpp == 4)
		return (*(Uint32 *)p);
	return (0);
}

void			floor_cast(t_wolf *wolf)
{
	int			y;
	int			x;
	int			p;

	float		ray_dir_x0;
	float		ray_dir_y0;
	float		ray_dir_x1;
	float		ray_dir_y1;
	float		pos_z;
	float		row_distance;
	float		floor_step_x;
	float		floor_step_y;
	float		floor_x;
	float		floor_y;

	int			cell_x;
	int			cell_y;
	int			tx;
	int			ty;

	SDL_Color	rgb;
	Uint32		data;

	y = wolf->sdl.height / 2 + wolf->player.sit;
	clear_screen(wolf->sdl.render);
	while (y < wolf->sdl.height)
	{
		ray_dir_x0 = wolf->player.dir_x - wolf->player.plane_x;
		ray_dir_y0 = wolf->player.dir_y - wolf->player.plane_y;
		ray_dir_x1 = wolf->player.dir_x + wolf->player.plane_x;
		ray_dir_y1 = wolf->player.dir_y + wolf->player.plane_y;
		p  = y - wolf->sdl.height / 2;
		pos_z = 0.5 * wolf->sdl.height;
		row_distance = pos_z / p;
		floor_step_x = row_distance * (ray_dir_x1 - ray_dir_x0) / wolf->sdl.width;
		floor_step_y = row_distance * (ray_dir_y1 - ray_dir_y0) / wolf->sdl.width;
		floor_x = wolf->player.pos_x + row_distance * ray_dir_x0;
		floor_y = wolf->player.pos_y +row_distance * ray_dir_y0;
		x = 0;
		while (x < wolf->sdl.width)
		{
			cell_x = (int)floor_x;
			cell_y = (int)floor_y;
			tx = (int)(wolf->sdl.floor[0]->w * (floor_x - cell_x)) & (wolf->sdl.floor[0]->h - 1);
			ty = (int)(wolf->sdl.floor[0]->w * (floor_y - cell_y)) & (wolf->sdl.floor[0]->h - 1);
			floor_x += floor_step_x;
			floor_y += floor_step_y;
			data = getpixel(wolf->sdl.floor[0], tx, ty);
			SDL_GetRGB(data, wolf->sdl.floor[0]->format, &rgb.r, &rgb.g, &rgb.b);
			SDL_SetRenderDrawColor(wolf->sdl.render, rgb.r, rgb.g, rgb.b, 0);
			SDL_RenderDrawPoint(wolf->sdl.render, x, y);
			x++;
		}
		y++;
	}
}