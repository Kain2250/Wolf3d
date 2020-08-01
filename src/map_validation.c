/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 16:03:36 by mcarc             #+#    #+#             */
/*   Updated: 2020/08/01 09:19:12 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			size_validation(t_wolf *w, char *map)
{
	char	*buff;
	int		fd;

	fd = open(map, O_RDONLY);
	buff = read_line(fd);
	close(fd);
	if (!map_validation(buff, w))
	{
		free(buff);
		return (error_exit(ERR_FILE_INVALID, NULL));
	}
	free(buff);
	if (!(w->location.x_len >= 3) || !(w->location.y_len >= 3))
		return (1);
	fd = open(map, O_RDONLY);
	buff = read_line(fd);
	close(fd);
	get_z(buff, w);
	denine(w);
	free(buff);
	return (0);
}

bool		line_validation(char *buff, t_wolf *w)
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

bool		topline_validation(char *buff, t_wolf *w)
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

bool		map_validation(char *line, t_wolf *w)
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
