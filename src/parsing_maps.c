/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_maps.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 19:23:27 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/07/23 17:19:14 by bdrinkin         ###   ########.fr       */
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

int			check_line(char *buff)
{
	int		iter;

	iter = 0;
	while (buff[iter] != '\0')
	{
		if (buff[iter] == '0' || buff[iter] == '1' ||
			buff[iter] == '2' || buff[iter] == '3' ||
			buff[iter] == '4' || buff[iter] == ' ')
			iter++;
		else
			return (0);
	}
	return (1);
}

int			pars_map(t_wolf *f, char *map)
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
		if (check_line(buff) && (f->location.x_len = get_x_len(buff, f)) != 0)
			f->location.y_len++;
		else
		{
			free(buff);
			ft_putendl_fd(ERR_FILE_INVALID, ERR_FD);
			return (1);
		}
		ft_strdel(&buff);
	}
	if (!f->location.x_len && !f->location.y_len)
	{
		ft_putendl_fd(ERR_FILE_INVALID, ERR_FD);
		return (1);
	}
	close(fd);
	fd = open(map, O_RDONLY);
	buff = read_line(fd);
	close(fd);
	get_z(buff, f);
	free(buff);
	return (0);
}

// int				pars_map(t_wolf *w, char *map)
// {
// 	int			fd;
// 	int			i;

// 	if ((fd = open(map, O_RDONLY)) < 1)
// 	{
// 		perror(map);
// 		return (1);
// 	}
// 	i = 0;
// 	w->location.map = (char **)ft_memalloc(sizeof(char *) * 22);
// 	while (i != 22)
// 	{
// 		w->location.map[i] = (char *)ft_memalloc(sizeof(char) * 25);
// 		i++;
// 	}
// 	i = 0;
// 	while (get_next_line(fd, &w->location.map[i]) == 1)
// 		i++;
// 	close(fd);
// 	ft_put2arr(22, w->location.map);
// 	return (0);
// }