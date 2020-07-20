/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/21 19:19:27 by kain2250          #+#    #+#             */
/*   Updated: 2020/07/20 15:52:12 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# define NAME_WIN "Wolf3d (by Bdrinkin)"
# define WIDTH_WIN 1280
# define HEIGHT_WIN 1024
# define BPERPIX 32
# define TEXT_CLR 0
# define WHITE_CLR 1
# define OTH_CLR 2

# include <math.h>
# include "debug_file.h"
# include "libft.h"
# include "definetextures.h"
# include "errorout.h"
# include "SDL.h"
# include "SDL_image.h"
# include "SDL_ttf.h"
# include "SDL_mixer.h"

typedef enum
{
	false,
	true
}						bool;

typedef enum			e_texture
{
	texture_main_menu,
	texture_concrete,
	texture_dress_dry,
	texture_dress_green,
	texture_sand,
	texture_wood_box,
	texture_wood_door,
	texture_total
}						n_texture;

typedef enum			e_font_tex
{
	fnt_new_g,
	fnt_ext_g,
	fnt_cntn,
	fnt_total
}						n_font_tex;

typedef struct			s_font
{
	TTF_Font			*font;
	SDL_Color			textColor;
	SDL_Texture			*texture;
	int					width;
	int					height;
	int					size;
}						t_font;

typedef struct			s_mouse
{
	int					prew_x;
	int					prew_y;
	int					x;
	int					y;
	int					l_click;
	int					r_click;
	float				move_speed;
	float				rot_speed;
}						t_mose;

typedef struct			s_player
{
	float				pos_x;
	float				pos_y;
	int					map_x;
	int					map_y;
	float				dir_x;
	float				dir_y;
	float				ray_dir_x;
	float				ray_dir_y;
	float				plane_x;
	float				plane_y;
	float				camera_x;
	float				side_dist_x;
	float				side_dist_y;
	float				delta_dist_x;
	float				delta_dist_y;
	float				perp_wall_dist;
	int					step_x;
	int					step_y;
	int					hit;
	int					side;
	float				time;
	float				old_time;
	bool				player;
}						t_player;

typedef struct			s_location
{
	bool				location;
	int					x_len;
	int					y_len;
	int					x_len_check;
	char				**map;
}						t_location;

typedef struct			s_hitbox
{
	int					x_start;
	int					y_start;
	int					x_fin;
	int					y_fin;
}						t_hitbox;

typedef struct			s_menu
{
	bool				menu;
	bool				pause;
	SDL_Rect			*button_contine;
	SDL_Rect			*button_new;
	SDL_Rect			*button_exit;
}						t_menu;

typedef struct			s_sdl_sys
{
	SDL_Window			*window;
	SDL_Surface 		*surface;
	SDL_Renderer		*render;
	SDL_Texture			*textures[texture_total];
	SDL_Surface			*picture[texture_total];
	SDL_Event			event;
	SDL_Rect			*rect_src;
	SDL_Rect			*rect_dst;
}						t_sdl_sys;

typedef struct			s_wolf
{
	struct s_sdl_sys	sdl;
	struct s_mouse		mouse;
	struct s_player		player;
	struct s_location	location;
	struct s_menu		menu;
	struct s_font		*font[fnt_total];
	bool				quit;
}						t_wolf;

bool					event_exit(t_wolf *wolf);
bool					event_list(t_wolf *w);

void					apply_surface(SDL_Surface *source, SDL_Surface *destination,
						SDL_Rect offset);
void					apply_surface_scaled(SDL_Surface *source,
						SDL_Surface *destination, SDL_Rect offset);
void					apply_render(SDL_Renderer *render, SDL_Texture *texture,
						SDL_Rect *srcrect, const SDL_Rect *dstrect);


bool					put_error_sdl(char *error, const char *error_sdl);
int						put_error_sys(char *error);

void					quit_sdl(t_wolf *wolf);
bool					load_files(SDL_Texture **textures, SDL_Renderer *render);
bool					initialization(t_wolf *wolf, char *map);

int						pars_map(t_wolf *f, char *map);

int						raycasting(t_wolf *wolf);


bool					init_sdl(t_wolf *wolf);
int						main(int ac, char **av);

#endif