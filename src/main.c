/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/21 19:19:04 by kain2250          #+#    #+#             */
/*   Updated: 2020/07/31 20:24:01 by bdrinkin         ###   ########.fr       */
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

bool		is_button_area(SDL_MouseButtonEvent event,
			SDL_Rect *area, int button)
{
	if (event.button == button && (event.type == SDL_MOUSEBUTTONDOWN ||
		event.type == SDL_MOUSEBUTTONUP) &&
		(event.x > area->x && event.x < area->w + area->x) &&
		(event.y > area->y && event.y < area->h + area->y))
		return (true);
	return (false);
}

void		start_menu(t_wolf *wolf)
{
	if (Mix_PlayingMusic() == 0)
		Mix_PlayMusic(wolf->sdl.mix.music[mix_menu], 1);
	SDL_RenderCopy(wolf->sdl.render,
	wolf->sdl.textures[texture_main_menu], 0, 0);
	SDL_RenderCopy(wolf->sdl.render, wolf->sdl.textures[texture_button_play],
	0, wolf->menu.button_new);
	SDL_RenderPresent(wolf->sdl.render);
	if (is_button_area(wolf->sdl.event.button,
		wolf->menu.button_new, SDL_BUTTON_LEFT))
	{
		wolf->menu.menu = true;
		SDL_SetRelativeMouseMode(SDL_TRUE);
		Mix_HaltMusic();
		raycasting(wolf);
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
				if (wolf->menu.menu == false)
					start_menu(wolf);
				if (event_list(wolf) == false)
					break ;
			}
		}
		quit_sdl(wolf);
	}
	else
		ft_putendl(USAGE_W3D);
	return (0);
}
