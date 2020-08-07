/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_placing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarc <mcarc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 14:25:12 by mcarc             #+#    #+#             */
/*   Updated: 2020/08/05 17:37:16 by mcarc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			denine(t_wolf *w)
{
	w->location.map[(int)w->player.pos_x][(int)w->player.pos_y] = '0';
}

static bool		evaluate_user_position(t_wolf *w)
{
	if (w->player.pos_x == -1 || w->player.pos_y == -1)
		return (false);
	return (true);
}

static void		line_user_placing(t_wolf *w, int y, char **sline)
{
	int			x;
	static int	counter = 0;

	x = 0;
	while (x < w->location.x_len)
	{
		if (sline[x][0] == '9')
		{
			counter++;
			w->player.pos_x = y + 0.5;
			w->player.pos_y = x + 0.5;
		}
		x++;
	}
	if (counter > 1)
	{
		w->player.pos_x = -1;
		w->player.pos_y = -1;
	}
}

bool			user_placing(t_wolf *w, char *line)
{
	int			y;
	char		**split;
	char		**sline;

	sline = ft_strsplit(line, '\n');
	y = 0;
	w->player.pos_x = -1;
	w->player.pos_y = -1;
	while (y < w->location.y_len)
	{
		split = ft_strsplit(sline[y], ' ');
		line_user_placing(w, y, split);
		ft_free_split(split);
		y++;
	}
	ft_free_split(sline);
	return (evaluate_user_position(w));
}
