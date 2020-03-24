/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kain2250 <kain2250@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/21 19:19:27 by kain2250          #+#    #+#             */
/*   Updated: 2020/03/24 19:26:05 by kain2250         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# define WIDTH_WIN 1376
# define HEIGHT_WIN 768
# define BPERPIX 32
# include "libft.h"
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include <stdio.h>

typedef struct			s_mouse
{
	int					prew_x;
	int					prew_y;
	int					x;
	int					y;
	int					l_click;
	int					r_click;
}						t_mose;

typedef struct			s_sdl_sys
{
	SDL_Surface			*screen;
	SDL_Surface 		*message;
	SDL_Surface 		*background;
	SDL_Event			event;


}						t_sdl_sys;

typedef struct			s_wolf
{
	struct s_sdl_sys	sdl;
	struct s_mouse		mouse;	
}						t_wolf;

#endif