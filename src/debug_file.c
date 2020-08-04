/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 19:09:59 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/08/04 22:47:38 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	quit_sdl(t_wolf *wolf)
{
	int	i;

	i = 0;
	if (wolf->sdl.render != NULL)
		SDL_DestroyRenderer(wolf->sdl.render);
	if (wolf->sdl.window != NULL)
		SDL_DestroyWindow(wolf->sdl.window);
	while (i != texture_total)
	{
		if (wolf->sdl.textures[i] != NULL)
			SDL_DestroyTexture(wolf->sdl.textures[i++]);
		else
			i++;
	}
	IMG_Quit();
	SDL_Quit();
	if (wolf->time != NULL)
		free(wolf->time);
	free(wolf);
	exit(0);
}

int			error_exit(char *err, char *buff)
{
	if (buff != NULL)
		free(buff);
	ft_putendl_fd(err, ERR_FD);
	return (1);
}

int		put_error_sys(char *error)
{
	ft_putendl_fd(error, ERR_FD);
	return (1);
}

bool	put_error_sdl(char *error, const char *error_sdl)
{
	ft_putstr_fd(error, ERR_FD);
	ft_putchar_fd(' ', ERR_FD);
	ft_putendl_fd(error_sdl, ERR_FD);
	return (false);
}
