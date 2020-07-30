/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorout.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 15:59:58 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/07/30 18:22:32 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROROUT_H
# define ERROROUT_H

# define ERR_FD 2
# define ERR_MALLOC "\033[0;31;1mMemory allocation error\033[0m"
# define ERR_FILE_INVALID "\033[0;31;1mInvalid file\033[0m"
# define ERR_CREATE_WIN "\033[0;31;1mFailed to create window\033[0m"
# define ERR_CREATE_RENDERER "\033[0;31;1mFailed to create renderer\033[0m"

# define ERR_INIT_IMG "\033[0;31;1mFailed to init IMG\033[0m"
# define ERR_INIT_TTF "\033[0;31;1mFailed to init TTF\033[0m"
# define ERR_INIT_SDL "\033[0;31;1mFailed to init SDL\033[0m"
# define ERR_INIT_MIX "\033[0;31;1mFailed to init MIX\033[0m"
# define ERR_LOAD_MIX "\033[0;31;1mFailed to load MIX\033[0m"

# define ERR_CAPTURE_MOUSE "\033[0;31;1mFailed to make mouse capture\033[0m"

# define USAGE_W3D "No input mapfile.\n\tUsage: ./wolf3d mapfile.w3d"

#endif
