/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/21 19:19:04 by kain2250          #+#    #+#             */
/*   Updated: 2020/07/27 15:32:55 by bdrinkin         ###   ########.fr       */
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
			SDL_SetRelativeMouseMode(SDL_TRUE);
			timer_start(wolf->time);
			filling_var(wolf);
			raycasting(wolf);
			while (wolf->quit == false)
			{
				if (event_list(wolf) == false)
					break ;
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
