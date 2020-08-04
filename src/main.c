/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarc <mcarc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/21 19:19:04 by kain2250          #+#    #+#             */
/*   Updated: 2020/08/04 15:42:01 by mcarc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			error_exit(char *err, char *buff)
{
	if (buff != NULL)
		free(buff);
	ft_putendl_fd(err, ERR_FD);
	return (1);
}

void		clear_queue(void)
{
	SDL_EventState(SDL_KEYDOWN, SDL_DISABLE);
	SDL_EventState(SDL_KEYDOWN, SDL_ENABLE);
	SDL_EventState(SDL_MOUSEMOTION, SDL_DISABLE);
	SDL_EventState(SDL_MOUSEMOTION, SDL_ENABLE);
}

void		start_menu(t_wolf *wolf)
{
	set_button(wolf);
	if (Mix_PlayingMusic() == 0)
		Mix_PlayMusic(wolf->sdl.mix.music[mix_menu], 1);
	SDL_RenderCopy(wolf->sdl.render,
	wolf->sdl.textures[texture_main_menu], 0, 0);
	SDL_RenderCopy(wolf->sdl.render, wolf->sdl.textures[texture_button_start],
	0, wolf->menu.button_new);
	SDL_RenderCopy(wolf->sdl.render, wolf->sdl.textures[texture_button_exit],
	0, wolf->menu.button_exit);
	SDL_RenderPresent(wolf->sdl.render);
	if (is_button_area(wolf->sdl.event.button,
		wolf->menu.button_new, SDL_BUTTON_LEFT))
	{
		wolf->menu.menu = true;
		SDL_SetRelativeMouseMode(SDL_TRUE);
		Mix_HaltMusic();
		raycasting(wolf);
	}
	else if (is_button_area(wolf->sdl.event.button,
		wolf->menu.button_exit, SDL_BUTTON_LEFT))
	{
		quit_sdl(wolf);
		exit(0);
	}
}

int			main(int ac, char **av)
{
	t_wolf	*wolf;

	(void)av;
	if (ac == 2)
	{
		if (!(wolf = (t_wolf *)ft_memalloc(sizeof(t_wolf))))
			return (put_error_sys(ERR_MALLOC));
		if (initialization(wolf, av[ac - 1]) == true)
		{
			timer_start(wolf->time);
			filling_var(wolf);
			while (wolf->quit == false)
			{
				//fps_counter(wolf);
				
				if (wolf->menu.menu == false)
					start_menu(wolf);
				if (event_list(wolf) == false)
					break ;
				// printf("%d\n", SDL_PeepEvents(&wolf->sdl.event, 5, SDL_PEEKEVENT, SDL_FIRSTEVENT, SDL_LASTEVENT));
			}
		}
		quit_sdl(wolf);
	}
	else
		ft_putendl(USAGE_W3D);
	return (0);
}
