/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/21 19:19:27 by kain2250          #+#    #+#             */
/*   Updated: 2020/08/07 22:12:28 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# define NAME_WIN "Wolf3d (by Bdrinkin & Mcarc)"
# define WIDTH_WIN 2000
# define HEIGHT_WIN 1500
# define TEXT_SIZE 512
# define IS_PUSH wolf->sdl.event.type == SDL_KEYDOWN
# define KEY_KEY wolf->sdl.event.key.keysym.sym
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
# include "libft.h"
# include "definetextures.h"
# include "errorout.h"
# include "SDL.h"
# include "SDL_image.h"
# include "SDL_mixer.h"
# include <stdio.h>

typedef enum			e_cardinal_point
{
	cardinal_north,
	cardinal_west,
	cardinal_south,
	cardinal_east
}						t_cardinal_point;

typedef enum			e_mode_color
{
	mode_rgb,
	mode_texture,
	mode_cardinal,
}						t_mode_color;

typedef enum			e_texture
{
	texture_main_menu,
	texture_steel_panel,
	texture_steel_panel_n,
	texture_steel_panel_s,
	texture_steel_panel_e,
	texture_steel_panel_w,
	texture_gray_brick,
	texture_steel_cuz,
	texture_steel_cuz_n,
	texture_steel_cuz_s,
	texture_steel_cuz_e,
	texture_steel_cuz_w,
	texture_steel_door,
	texture_gold_fass,
	texture_gold_fass_n,
	texture_gold_fass_s,
	texture_gold_fass_e,
	texture_gold_fass_w,
	texture_brick,
	texture_brick_n,
	texture_brick_s,
	texture_brick_e,
	texture_brick_w,
	texture_wind_wood,
	texture_button_start,
	texture_button_exit,
	texture_total
}						t_texture;

typedef enum			e_count_chank
{
	mix_step1,
	mix_step2,
	mix_step3,
	mix_step_total
}						t_count_chank;

typedef enum			e_count_music
{
	mix_menu,
	mix_game,
	mix_total
}						t_count_music;

typedef struct			s_mouse
{
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
	int					sit;
	bool				player;
	t_cardinal_point	cardinal;
}						t_player;

typedef struct			s_location
{
	bool				location;
	int					x_len;
	int					y_len;
	int					x_len_check;
	int					color_mode;
	char				**map;
}						t_location;

typedef struct			s_menu
{
	bool				menu;
	SDL_Rect			*button_new;
	SDL_Rect			*button_exit;
}						t_menu;

typedef struct			s_music
{
	Mix_Chunk			*steps[mix_step_total];
	Mix_Music			*music[mix_total];
	bool				mute;
}						t_music;

typedef struct			s_sdl_sys
{
	SDL_Window			*window;
	SDL_Renderer		*render;
	SDL_Texture			*textures[texture_total];
	struct s_music		mix;
	SDL_Event			event;
	int					width;
	int					height;
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
void					render_screen(t_walls *walls, int x,
						int y, t_wolf *wolf);
/*
** Функции выбора цвета
*/
SDL_Color				*assigned_color(Uint8 red, Uint8 green,
						Uint8 blue, Uint8 alpha);
SDL_Color				*color_cahge(char **map, int x, int y);
void					shadow_render(t_wolf *wolf, int num_text,
						SDL_Rect rect[2]);
void					change_color_mod(t_wolf *wolf);

bool					put_error_sdl(char *error, const char *error_sdl);
int						put_error_sys(char *error);

int						pars_map(t_wolf *f, char *map);
bool					map_validation(char *line, t_wolf *w);
bool					user_placing(t_wolf *w, char *line);
int						check_line(char *buff);
void					denine(t_wolf *w);

void					fps_counter(t_timer *time);

void					set_button(t_wolf *wolf);
bool					is_button_area(SDL_MouseButtonEvent event,
						SDL_Rect *area, int button);

void					mute_music(t_wolf *wolf);
bool					init_sdl(t_wolf *wolf);
void					quit_sdl(t_wolf *wolf);
int						error_exit(char *err, char *buff);
int						main(int ac, char **av);

void					side_determination(t_wolf *wolf);
void					render_blocks(t_wolf *wolf, SDL_Rect rect[2]);
void					load_textures(SDL_Texture **textures,
						SDL_Renderer *render);
void					render_texture(t_wolf *wolf, t_walls *walls, int x1);
void					wall_definition(t_wolf *wolf, SDL_Rect rect[2]);
void					shadow_render(t_wolf *wolf,
						int num_text, SDL_Rect rect[2]);
void					check_render_mode(t_wolf *wolf, SDL_Rect rect[2]);
void					rect_init(t_walls *walls, int x1,
						SDL_Rect rect[2], int tex_x);
#endif
