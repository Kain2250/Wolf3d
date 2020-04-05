/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prime_funct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kain2250 <kain2250@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 07:06:55 by kain2250          #+#    #+#             */
/*   Updated: 2020/03/29 18:34:19 by kain2250         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void				clean_up(t_wolf *w)
{
	SDL_FreeSurface(w->sdl.image);// Освободить загруженное изображение
	SDL_Quit();
	free(w);
}

bool				init_sdl(t_wolf *w)
{
	w->sdl.win = NULL;
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
		return (false);
	if (TTF_Init() == -1)
		return (false);
	w->sdl.win = SDL_SetVideoMode(WIDTH_WIN,
	HEIGHT_WIN, BPERPIX, SDL_SWSURFACE | SDL_DOUBLEBUF);// Настройка экрана
	if (w->sdl.win == NULL)
		return (false);
	SDL_WM_SetCaption("Wolf3D", NULL);// Наименование окна
	return (true);
}

void			apply_surface(int x, int y, SDL_Surface *source,
				SDL_Surface *destination)
{
	SDL_Rect	offset;

 	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(source, NULL, destination, &offset);// Применить изображение к экрану
}

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

bool			load_files(t_wolf *w, char *av)
{
	w->sdl.image = load_image(av);// Зарузка изображения
	if (w->sdl.image == NULL)//Если изображение не загрузилось - выход
	{
		return (false);
	}
	return (true);
}
