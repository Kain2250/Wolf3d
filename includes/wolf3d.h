/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarc <mcarc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/21 19:19:27 by kain2250          #+#    #+#             */
/*   Updated: 2020/07/31 17:12:47 by mcarc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# define NAME_WIN "Wolf3d (by Bdrinkin)"
# define WIDTH_WIN 2000
# define HEIGHT_WIN 1500
# define BPERPIX 32
# define TEXT_CLR 0
# define WHITE_CLR 1
# define OTH_CLR 2
# define DIR_FORWARD 1
# define DIR_BACK 2
# define COLOR_RED 160, 6, 5, 0
# define COLOR_BLUE 18, 10, 143, 0
# define COLOR_GREEN 119, 221, 119, 0
# define COLOR_BLACK 0, 0, 0, 0
# define COLOR_YELLOW 112, 66, 20, 0
# define COLOR_SKY 100, 100, 100, 0
# define COLOR_FLOR 50, 50, 50, 0

# include <math.h>
# include <stdbool.h>
# include "debug_file.h"
# include "libft.h"
# include "definetextures.h"
# include "errorout.h"
# include "SDL.h"
# include "SDL_image.h"
//# include "SDL_ttf.h"
# include "SDL_mixer.h"
# include <stdio.h>

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
}						t_texture;

typedef enum			e_font_tex
{
	fnt_new_g,
	fnt_ext_g,
	fnt_cntn,
	fnt_total
}						t_font_tex;

// typedef struct			s_font
// {
// 	TTF_Font			*font;
// 	SDL_Color			text_color;
// 	SDL_Texture			*texture;
// 	int					width;
// 	int					height;
// 	int					size;
// }						t_font;

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
	double				pos_x;
	double				pos_y;
	int					map_x;
	int					map_y;
	double				dir_x;
	double				dir_y;
	double				ray_dir_x;
	double				ray_dir_y;
	double				plane_x;
	double				plane_y;
	double				camera_x;
	double				side_dist_x;
	double				side_dist_y;
	double				delta_dist_x;
	double				delta_dist_y;
	double				perp_wall_dist;
	int					step_x;
	int					step_y;
	int					hit;
	int					side;
	bool				player;
}						t_player;

typedef struct			s_location
{
	bool				location;
	int					x_len;
	int					y_len;
	int					x_len_check;
	SDL_Rect			*sky;
	SDL_Rect			*flor;
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
	SDL_Surface			*surface;
	SDL_Renderer		*render;
	SDL_Texture			*textures[texture_total];
	SDL_Surface			*picture[texture_total];
	SDL_Event			event;
	SDL_Rect			*rect_src;
	SDL_Rect			*rect_dst;
}						t_sdl_sys;

typedef struct			s_walls
{
	int					draw_start;
	int					draw_end;
	int					line_height;
	int					x;
	SDL_Color			*color;
	struct s_walls		*next;
}						t_walls;

typedef struct			s_timer
{
	Uint32				start_ticks;
	Uint32				paused_ticks;
	bool				paused;
	bool				started;
	int					counted_frames;
}						t_timer;

typedef struct			s_wolf
{
	struct s_sdl_sys	sdl;
	struct s_mouse		mouse;
	struct s_player		player;
	struct s_location	location;
	struct s_timer		*time;
	struct s_menu		menu;
	struct s_walls		walls;
	// struct s_font		*font[fnt_total];
	bool				quit;
}						t_wolf;
/*
** Таймер для FPS
*/
Uint32					get_ticks(t_timer *time);
bool					time_is_started(t_timer *time);
bool					time_is_paused(t_timer *time);
void					timer_init(t_timer *time);
void					timer_start(t_timer *time);
void					timer_stop(t_timer *time);
void					timer_pause(t_timer *time);
void					timer_unpause(t_timer *time);
float					get_fps(t_timer *time);
/*
** Эвенты
*/
bool					event_exit(t_wolf *wolf);
bool					event_list(t_wolf *w);
/*
** Стандартные функции манипуляции изображений в SDL2
*/
void					apply_surface(SDL_Surface *source,
						SDL_Surface *destination, SDL_Rect offset);
void					apply_surface_scaled(SDL_Surface *source,
						SDL_Surface *destination, SDL_Rect offset);
void					apply_render(SDL_Renderer *render,
						SDL_Texture *texture, SDL_Rect *srcrect,
						const SDL_Rect *dstrect);
void					clear_screen(SDL_Renderer *render);
bool					event_exit(t_wolf *wolf);
/*
** Функции манипуляции игроком
*/
void					rotate_plane_and_cam(t_wolf *wolf, float rot_speed);
void					move_player(t_wolf *wolf, int direction);
/*
** Инициализация проекта, присваивание значения переменным
*/
void					filling_var(t_wolf *wolf);
bool					load_files(SDL_Texture **textures,
						SDL_Renderer *render);
bool					initialization(t_wolf *wolf, char *map);
/*
** Основной алгоритм бросания лучей RayCasting
*/
int						raycasting(t_wolf *wolf);
float					calc_dist(double ray_dir_1, double ray_dir_2);
void					brightness_calc(SDL_Color *color);
void					calculate_foog(t_wolf *wolf, t_walls *walls);
void					cam_and_screen_setup(t_wolf *wolf, int x_screen,
						double width);
void					ray_computation(t_wolf *wolf);
void					find_hit(t_wolf *wolf);
void					getting_the_height_to_the_wall(t_wolf *wolf,
						t_walls *walls);
void					render_screen(SDL_Renderer *render, t_walls *walls,
						int x, int y);
/*
** Функции выбора цвета
*/
SDL_Color				*assigned_color(Uint8 red, Uint8 green,
						Uint8 blue, Uint8 alpha);
SDL_Color				*color_cahge(char **map, int x, int y);

bool					put_error_sdl(char *error, const char *error_sdl);
int						put_error_sys(char *error);

int						pars_map(t_wolf *f, char *map);
bool   					map_validation(char *line, t_wolf *w);
bool					user_placing(t_wolf *w, char *line);
void					denine(t_wolf *w);

void					fps_counter(t_wolf *wolf);

void					clear_queue(void);

bool					init_sdl(t_wolf *wolf);
void					quit_sdl(t_wolf *wolf);
int						error_exit(char *err, char *buff);
int						main(int ac, char **av);

#endif
