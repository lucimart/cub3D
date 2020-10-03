/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucimart <lucimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 19:38:53 by lucimart          #+#    #+#             */
/*   Updated: 2020/10/03 19:39:22 by lucimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libcub3d.h"

int		is_save_flag(const char *str)
{
	if (ft_strequ(str, "--save"))
		return (1);
	ft_putstr("Error\nInvalid flag. Available flags: --save");
	return (0);	
}

int		is_ext(const char *filename, const char *ext) 
{
	const char *dot;

	dot = ft_strrchr(filename, '.');
	if (!dot || dot == filename || !ft_strequ(dot, ext))
		return (0);
	return (1);
}