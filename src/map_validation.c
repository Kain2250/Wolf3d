/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarc <mcarc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 16:03:36 by mcarc             #+#    #+#             */
/*   Updated: 2020/07/31 19:56:57 by mcarc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

bool	line_validation(char *buff, t_wolf *w)
{
	char	**split;

	split = ft_strsplit(buff, ' ');
	if (*split[0] == '0' || *split[w->location.x_len - 1] == '0')
	{
		ft_free_split(split);
		return (false);
	}
	ft_free_split(split);
	return (true);
}

bool	topline_validation(char *buff, t_wolf *w)
{
	char	**split;
	int		x;

	split = ft_strsplit(buff, ' ');
	x = 0;
	while (x < w->location.x_len)
	{
		if (*split[x] == '0')
		{
			ft_free_split(split);
			return (false);
		}
		x++;
	}
	ft_free_split(split);
	return (true);
}

bool	map_validation(char *line, t_wolf *w)
{
	char	**sline;
    int		y;
    bool	placing;

	sline = ft_strsplit(line, '\n');
	y = 0;
	while (y < w->location.y_len)
	{
		if ((y == 0 || y == w->location.y_len - 1)
		&& !topline_validation(sline[y], w))
		{
			ft_free_split(sline);
			return (false);
		}
		else if (!line_validation(sline[y], w))
		{
			ft_free_split(sline);
			return (false);
		}
		else
			y++;
	}
	ft_free_split(sline);
	placing = user_placing(w, line);
	return (true && placing);
}
