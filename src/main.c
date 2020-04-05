/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kain2250 <kain2250@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/21 19:19:04 by kain2250          #+#    #+#             */
/*   Updated: 2020/04/05 16:00:37 by kain2250         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			close_error(t_wolf *w)
{
	(void)w;
}

int				add_pict(t_wolf *w, char *av)
{
	if (load_files(w, av) == false)//загрузка файла
	{
		printf("Unable to load files SDL: %s", SDL_GetError());
		return (1);
	}
	apply_surface(0, 0, w->sdl.image, w->sdl.win);//вывод на экран
	if (SDL_Flip(w->sdl.win) == -1)//обновление экрана
	{
		printf("Unable to Flip SDL: %s", SDL_GetError());
		return (1);
	}
	return (0);
}

SDL_Color		clr_text(int color_place)
{
	SDL_Color	clr;

	if (color_place == TEXT_CLR)
	{
		clr.r = 77;
		clr.g = 109;
		clr.b = 242;
	}
	else if (color_place == OTH_CLR)
	{
		clr.r = 50;
		clr.g = 50;
		clr.b = 50;
	}
	else
	{
		clr.r = 0;
		clr.g = 200;
		clr.b = 160;
	}
		return (clr);
}

void			Text_input(int x, int y, char text[100], t_wolf *w)
{
	TTF_Font	*fnt;
    SDL_Rect	dest;
    SDL_Surface	*sText;

	fnt = TTF_OpenFont("font/1_font.ttf", w->sz);
	sText = TTF_RenderText_Blended(fnt, text, clr_text(TEXT_CLR));
    dest.x = x;
    dest.y = y;
    SDL_BlitSurface(sText, NULL, w->sdl.win, &dest);
    SDL_FreeSurface(sText);
    TTF_CloseFont(fnt);
}

void			put_menu(t_wolf *w)
{
	Text_input(50, 50, "tut mogla bit vasha reklama", w);
	SDL_Flip(w->sdl.win);
}

void			menu_control(t_wolf *w)
{
	add_pict(w, "./textures/main_menu.jpg");
	put_menu(w);
	// while (w->menu.menu == false || w->quit == false)
	// {
	// 	SDL_WaitEvent(&w->sdl.event);
	// 	if (w->sdl.event.type == SDL_QUIT ||
	// 	w->sdl.event.key.keysym.sym == SDLK_ESCAPE)
	// 		w->quit = true;
	// }
}

void			event_list(t_wolf *w)
{
	if (w->sdl.event.type == SDL_QUIT ||
		w->sdl.event.key.keysym.sym == SDLK_ESCAPE)
		w->quit = true;	
	// if (w->sdl.event.button.button == SDL_BUTTON_LEFT)
	// {
	// 	if ((add_pict(w, "123.bmp")) == 1)
	// 		return (1);
	// }
	if (w->sdl.event.button.button == SDL_BUTTON_RIGHT)
	{
		add_pict(w, "./textures/vood_door.jpg");
	}
}

void			init_location(t_wolf *w)
{
	w->location.location = true;
}

void			init_player(t_wolf *w)
{
	w->player.player = true;
}

int				pars_map(t_wolf *w, char *map)
{
	int			fd;
	int			i;

	fd = open(map, O_RDONLY);
	i = 0;
	while (get_next_line(fd, &w->location.map[i]) == 1)
		i++;
	return (0);
}

int				main(int ac, char **av)
{
	t_wolf		*w;

	if (ac > 1)
	{
		w = NULL;
		if (!(w = (t_wolf *)ft_memalloc(sizeof(t_wolf))))
			close_error(w);
		w->quit = false;
		w->sdl.message = NULL;
		w->sdl.background = NULL;
		w->sz = 17;
		if (init_sdl(w) == false)
		{
			printf("Unable to init SDL: %s", SDL_GetError());
			return (1);
		}
		if (pars_map(w, av[1]) == 1)
			return (1);
		menu_control(w);
		while(w->quit == false)
		{
			if (w->player.player == false)
				init_player(w);
			if (w->location.location == false)
				init_location(w);
			SDL_WaitEvent(&w->sdl.event); // ждем эвенты
			event_list(w);
		}
		clean_up(w);//Очистка и выход из окна
	}
	else
		ft_putendl("Usege: ./wolf3d 'image.*'");	
	return (0);
}

// 	if (SDL_Flip(w->sdl.screen) == -1)// Обновление экрана
// 	{
//         return (1);
// 	}

// 	SDL_Delay(5000);// Пауза 2 сек
