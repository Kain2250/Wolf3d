/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/21 19:19:27 by kain2250          #+#    #+#             */
/*   Updated: 2020/08/09 18:10:52 by bdrinkin         ###   ########.fr       */
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
# define COLOR_RED 255, 60, 60, 0
# define COLOR_BLUE 60, 135, 255, 0
# define COLOR_GREEN 79, 255, 60, 0
# define COLOR_BLACK 0, 0, 0, 0
# define COLOR_YELLOW 255, 241, 60, 0
# define COLOR_PURPLE 174, 91, 179, 0
# define COLOR_SKY 127, 231, 255, 0
# define COLOR_FLOR 179, 130, 91, 0

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
	texture_main_leg,
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
	bool				leg;
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
	SDL_Color			*color;
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
	int					dir_def[8];
}						t_wolf;

void					shadow_render(t_wolf *wolf, int num_text,
						SDL_Rect rect[2]);
void					wall_definition(t_wolf *wolf, SDL_Rect rect[2]);
void					render_texture(t_wolf *wolf, t_walls *walls, int x1);
void					render_all_block(t_wolf *wolf, SDL_Rect rect[2],
						int texture);
void					render_blocks(t_wolf *wolf, SDL_Rect rect[2]);

void					render_screen(t_walls *walls, int x, int y,
						t_wolf *wolf);
void					getting_the_height_to_the_wall(t_wolf *wolf,
						t_walls *walls);
void					find_hit(t_wolf *wolf);
void					ray_computation(t_wolf *wolf);
void					cam_and_screen_setup(t_wolf *wolf, int x_screen,
						double width);

SDL_Color				*color_cahge(char **map, int x, int y);
SDL_Color				*assigned_color(Uint8 red, Uint8 green, Uint8 blue,
						Uint8 alpha);

void					quit_sdl(t_wolf *wolf);
int						error_exit(char *err, char *buff);
bool					put_error_sdl(char *error, const char *error_sdl);
int						put_error_sys(char *error);

void					event_key_hook(t_wolf *wolf);
bool					is_key_movement(t_wolf *wolf);
void					mute_music(t_wolf *wolf);
void					game_events(t_wolf *wolf);
bool					event_list(t_wolf *wolf);

void					filling_var(t_wolf *wolf);
bool					load_files(SDL_Texture **textures,
						SDL_Renderer *render);
bool					init_sdl(t_wolf *wolf);
bool					load_mixer(t_wolf *wolf);
bool					initialization(t_wolf *wolf, char *map);

void					start_menu(t_wolf *wolf);
int						main(int ac, char **av);

void					change_color_mod(t_wolf *wolf);
void					rotate_plane_and_cam(t_wolf *wolf, float rot_speed);
double					decriment(double a, double alpha);
void					move_mouse(t_wolf *wolf, double k_diag, int k_y);
void					event_mouse_hook(t_wolf *wolf);

int						check_line(char *buff);
bool					line_validation(char *buff, t_wolf *w);
bool					topline_validation(char *buff, t_wolf *w);
bool					map_validation(char *line, t_wolf *w);

void					move_player(t_wolf *wolf, int direction);

int						size_validation(t_wolf *w, char *map);
int						pars_map(t_wolf *w, char *map);

float					calc_dist(double ray_dir_1, double ray_dir_2);
void					brightness_calc(SDL_Color *color);
void					calculate_foog(t_wolf *wolf, t_walls *walls);
void					rect_init(t_walls *walls, int x1,
						SDL_Rect rect[2], int tex_x);
int						raycasting(t_wolf *wolf);

void					calc_dir_def(t_wolf *wolf, int dir_def[8]);
void					clear_screen(SDL_Renderer *render);
bool					event_exit(t_wolf *wolf);
bool					is_button_area(SDL_MouseButtonEvent event,
						SDL_Rect *area, int button);
void					set_button(t_wolf *wolf);

void					side_determination(t_wolf *wolf);

void					timer_init(t_timer *time);
void					timer_start(t_timer *time);
void					timer_stop(t_timer *time);
void					timer_pause(t_timer *time);
void					timer_unpause(t_timer *time);

void					check_render_mode(t_wolf *wolf, SDL_Rect rect[2]);
void					load_textures(SDL_Texture **textures,
						SDL_Renderer *render);

Uint32					get_ticks(t_timer *time);
bool					time_is_started(t_timer *time);
bool					time_is_paused(t_timer *time);
void					fps_counter(t_timer *time);

void					denine(t_wolf *w);
bool					user_placing(t_wolf *w, char *line);
void					minimap_output(t_wolf *wolf);

#endif
