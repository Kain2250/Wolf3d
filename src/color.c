/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 10:47:42 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/07/27 12:32:03 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

SDL_Color		*color_cahge(char **map, int x, int y)
{
	if (map[x][y] == '1')
		return (assigned_color(COLOR_RED));
	else if (map[x][y] == '2')
		return (assigned_color(COLOR_YELLOW));
	else if (map[x][y] == '3')
		return (assigned_color(COLOR_GREEN));
	else if (map[x][y] == '4')
		return (assigned_color(COLOR_BLUE));
	return (NULL);
}

SDL_Color		*assigned_color(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha)
{
	SDL_Color	*color;

	color = ft_memalloc(sizeof(SDL_Color));
	color->a = alpha;
	color->r = red;
	color->g = green;
	color->b = blue;
	return (color);
}
