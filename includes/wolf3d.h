/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kain2250 <kain2250@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/21 19:19:27 by kain2250          #+#    #+#             */
/*   Updated: 2020/04/01 23:30:18 by kain2250         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# define WIDTH_WIN 1280
# define HEIGHT_WIN 1024
# define BPERPIX 32
# define TEXT_CLR 0
# define OTH_CLR 1

# include "libft.h"
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include <SDL/SDL_ttf.h>

typedef enum
{
	false,
	true
}						bool;

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
	SDL_Surface			*win;
	SDL_Surface 		*message;
	SDL_Surface 		*background;
	SDL_Surface			*image;
	SDL_Event			event;
	TTF_Font			*font;
	SDL_Color			textColor;
}						t_sdl_sys;

typedef struct			s_player
{
	int					x;
	int					y;
	bool				player;
}						t_player;

typedef struct			s_location
{
	bool				location;
	char				**map;
}						t_location;

typedef struct			s_menu
{
	bool				menu;
}						t_menu;

typedef struct			s_wolf
{
	struct s_sdl_sys	sdl;
	struct s_mouse		mouse;
	struct s_player		player;
	struct s_location	location;
	struct s_menu		menu;
	int					sz;
	bool				quit;
}						t_wolf;

SDL_Surface				*load_image(char *filename);
void					clean_up(t_wolf *w);
void					apply_surface(int x, int y, SDL_Surface *source,
						SDL_Surface *destination);
bool					init_sdl(t_wolf *w);
bool					load_files(t_wolf *w, char *av);

int						main(int ac, char **av);
void					close_error(t_wolf *w);
void					put_menu(t_wolf *w);
void					Text_input(int x, int y, char text[100], t_wolf *w);
SDL_Color				clr_text(int color_place);
int						add_pict(t_wolf *w, char *av);
void					menu_control(t_wolf *w);


#endif