/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 18:45:19 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/08/09 15:07:13 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		change_color_mod(t_wolf *wolf)
{
	if (KEY_KEY == SDLK_1)
		wolf->location.color_mode = mode_texture;
	else if (KEY_KEY == SDLK_2)
		wolf->location.color_mode = mode_cardinal;
	else if (KEY_KEY == SDLK_3)
		wolf->location.color_mode = mode_rgb;
}

void		rotate_plane_and_cam(t_wolf *wolf, float rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = wolf->player.dir_x;
	wolf->player.dir_x = wolf->player.dir_x * cos(rot_speed) -
	wolf->player.dir_y * sin(rot_speed);
	wolf->player.dir_y = old_dir_x * sin(rot_speed) +
	wolf->player.dir_y * cos(rot_speed);
	old_plane_x = wolf->player.plane_x;
	wolf->player.plane_x = wolf->player.plane_x * cos(rot_speed) -
	wolf->player.plane_y * sin(rot_speed);
	wolf->player.plane_y = old_plane_x * sin(rot_speed) +
	wolf->player.plane_y * cos(rot_speed);
}

double		decriment(double a, double alpha)
{
	if (a > 0)
		a -= alpha;
	else
		a += alpha;
	return (a);
}

void		move_mouse(t_wolf *wolf, double k_diag, int k_y)
{
	int		buf;

	rotate_plane_and_cam(wolf, -atan(wolf->sdl.event.motion.xrel)
	* wolf->mouse.rot_speed * k_diag);
	buf = -atan(wolf->sdl.event.motion.yrel) * k_y + wolf->player.sit;
	if (buf <= 700 && buf >= -700)
		wolf->player.sit = buf;
}

void		event_mouse_hook(t_wolf *wolf)
{
	int		buf_sit;

	buf_sit = wolf->player.sit;
	if (wolf->sdl.event.motion.xrel && wolf->sdl.event.motion.yrel)
		move_mouse(wolf, 0.9, 15);
	else
		move_mouse(wolf, 1.0, 10);
	wolf->sdl.event.motion.xrel = 0;
	wolf->sdl.event.motion.yrel = 0;
}
