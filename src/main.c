/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarc <mcarc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/21 19:19:04 by kain2250          #+#    #+#             */
/*   Updated: 2020/08/06 19:45:23 by mcarc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		start_menu(t_wolf *wolf)
{
	set_button(wolf);
	if (Mix_PlayingMusic() == 0)
		Mix_PlayMusic(wolf->sdl.mix.music[mix_menu], -1);
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
		quit_sdl(wolf);
}

int			main(int ac, char **av)
{
	t_wolf	*wolf;
	// double	angle_y;

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
				//  printf("%f %f\n", wolf->player.dir_x, wolf->player.dir_y);
				// printf("%f %f\n", acos(wolf->player.dir_x) * 180 / M_PI, acos(wolf->player.dir_y) * 180 / M_PI);
				// printf("%f %f %f %f\n", wolf->player.dir_x, wolf->player.dir_y, acos(wolf->player.dir_x), asin(wolf->player.dir_x));
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
