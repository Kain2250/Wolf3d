/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/21 19:19:04 by kain2250          #+#    #+#             */
/*   Updated: 2020/08/09 16:51:23 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		start_menu(t_wolf *wolf)
{
	mute_music(wolf);
	if (Mix_PlayingMusic() == 0 && wolf->sdl.mix.mute == false)
		Mix_PlayMusic(wolf->sdl.mix.music[mix_menu], -1);
	set_button(wolf);
	SDL_RenderCopy(wolf->sdl.render, wolf->sdl.textures
	[(wolf->menu.leg ? texture_main_menu : texture_main_leg)], 0, 0);
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
		if (Mix_PlayingMusic() == 1)
			Mix_HaltMusic();
		raycasting(wolf);
	}
	else if (is_button_area(wolf->sdl.event.button,
		wolf->menu.button_exit, SDL_BUTTON_LEFT))
		quit_sdl(wolf);
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
				fps_counter(wolf->time);
			}
		}
		quit_sdl(wolf);
	}
	else
		ft_putendl(USAGE_W3D);
	return (0);
}
