/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_maps.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarc <mcarc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 19:23:27 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/08/04 15:42:05 by mcarc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	get_z(char *line, t_wolf *f)
{
	int		x;
	int		y;
	char	**split;
	char	**sline;

	f->location.map = (char **)ft_memalloc(sizeof(char *) * f->location.y_len);
	sline = ft_strsplit(line, '\n');
	y = 0;
	while (y < f->location.y_len)
	{
		x = 0;
		f->location.map[y] = (char *)malloc(sizeof(char) *
		(f->location.x_len + 1));
		split = ft_strsplit(sline[y], ' ');
		while (x < f->location.x_len)
		{
			f->location.map[y][x] = split[x][0];
			x++;
		}
		f->location.map[y][x] = '\0';
		y++;
		ft_free_split(split);
	}
	ft_free_split(sline);
}

static int	get_x_len(char *line, t_wolf *f)
{
	int		i;
	int		x;

	i = 0;
	x = 1;
	while (line[i] == ' ')
		i++;
	while (line[i] != '\0')
	{
		if (line[i] == ' ' && line[i + 1] != ' ' && line[i + 1] != '\0')
			x++;
		i++;
	}
	if (f->location.x_len_check == 0)
		f->location.x_len_check = x;
	else if (f->location.x_len_check != x)
		return (0);
	return (x);
}

static char	*read_line(int fd)
{
	char	*line;
	int		i;
	char	*buff;
	char	*buff2;

	line = malloc(10001 * sizeof(char));
	buff = malloc(1 * sizeof(char));
	buff[0] = '\0';
	while ((i = read(fd, line, 10000)) > 0)
	{
		line[10000] = '\0';
		buff2 = ft_strjoin_free(buff, line);
		line = malloc(10001 * sizeof(char));
		buff = buff2;
	}
	free(line);
	return (buff2);
}

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

int			pars_map(t_wolf *w, char *map)
{
	int		fd;
	char	*buff;

	if ((fd = open(map, O_RDONLY)) < 1)
	{
		perror(map);
		return (1);
	}
	while (get_next_line2(fd, &buff))
	{
		if (check_line(buff) && (w->location.x_len = get_x_len(buff, w)) != 0)
			w->location.y_len++;
		else
			return (error_exit(ERR_FILE_INVALID, buff));
		ft_strdel(&buff);
	}
	close(fd);
	if (size_validation(w, map))
		return (1);
	return (0);
}
