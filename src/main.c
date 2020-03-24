/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kain2250 <kain2250@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/21 19:19:04 by kain2250          #+#    #+#             */
/*   Updated: 2020/03/24 19:34:08 by kain2250         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

SDL_Surface		*load_image(char *filename) 
{
    SDL_Surface	*loadedImage;//Временное хранилище для загруженного изображения   
    SDL_Surface	*optimizedImage;//Оптимизированное изображение, которое будет использоваться

	loadedImage = NULL;
	optimizedImage = NULL;
    loadedImage = IMG_Load(filename);// Загрузить изображение нагруженного изображения
    if (loadedImage != NULL)//Если при загрузке изображения ничего не пошло не так 
    {
		optimizedImage = SDL_DisplayFormat(loadedImage);//Создать оптимизированное изображение
		SDL_FreeSurface(loadedImage);//Очистить старое изображение
    }
    return (optimizedImage);//Возвращаем оптимизированое изображение
}

void			apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *destination)
{
	SDL_Rect	offset; // Сделать временный прямоугольник для хранения смещений

 	offset.x = x;
	offset.y = y; // Передаем смещения прямоугольнику
    SDL_BlitSurface(source, NULL, destination, &offset);// Применить изображение к экрану
}

int				init_sdl(t_wolf *w)
{

	w->sdl.screen = NULL;
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
        return (0);
	}
	w->sdl.screen = SDL_SetVideoMode(WIDTH_WIN, HEIGHT_WIN, BPERPIX, SDL_SWSURFACE);// Настройка экрана
    if (w->sdl.screen == NULL)
	{
    	return (0);
	}    
	SDL_WM_SetCaption("Wolf3D", NULL);// Наименование окна
    return (1);
}

void			close_error(t_wolf *w)
{
	(void)w;
	exit (0);
}

int				main(int ac, char **av)
{
	t_wolf		*w;

	w = NULL;
	if (!(w = (t_wolf *)ft_memalloc(sizeof(t_wolf))))
		close_error(w);
	w->sdl.message = NULL;
	w->sdl.background = NULL;
	init_sdl(w);
    w->sdl.message = load_image("hello.bmp");
    w->sdl.background = load_image("background.bmp");
	// apply_surface(0, 0, w->sdl.background, w->sdl.screen);
 	apply_surface(80, 140, w->sdl.message, w->sdl.screen);
	if (SDL_Flip(w->sdl.screen) == -1)// Обновление экрана
	{
        return (1);
	}  
	SDL_Delay(5000);// Пауза 2 сек
	SDL_FreeSurface(w->sdl.message);
    SDL_FreeSurface(w->sdl.background);// Освободить загруженное изображение 
	SDL_Quit();// Выходим из SDL
	(void)ac;
	(void)av;
	return (0);
}
