/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/21 19:19:04 by kain2250          #+#    #+#             */
/*   Updated: 2020/07/23 19:46:40 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			main(int ac, char **av)
{
	t_wolf	*wolf;

	(void)av;
	if (ac == 2)
	{
		if (!(wolf = (t_wolf *)ft_memalloc(sizeof(t_wolf))))
			return (put_error_sys(ERR_MALLOC));
		if (!(wolf->time = (t_timer *)ft_memalloc(sizeof(t_timer))))
			return (put_error_sys(ERR_MALLOC));
		if (initialization(wolf, av[ac - 1]) == true)
		{
			timer_start(wolf->time);
			filling_var(wolf);
			raycasting(wolf);
			SDL_RenderPresent(wolf->sdl.render);
			while(wolf->quit == false)
			{
				if (event_list(wolf) == false)
					break ;
				SDL_GetRenderDrawColor(wolf->sdl.render, 0, 0, 0, 0);
				SDL_RenderClear(wolf->sdl.render);

			}
		}
		else
			bad_complite();
		quit_sdl(wolf);
	}
	else
		ft_putendl(USAGE_W3D);
	return (0);
}

// Захват мыши в окне
// if (SDL_CaptureMouse(SDL_TRUE) == -1)
// {
// 	put_error_sdl(ERR_CAPTURE_MOUSE, SDL_GetError());
// 	return (1);
// }
// else
// 	return (0);
