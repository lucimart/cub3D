/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucimart <lucimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 19:07:59 by lucimart          #+#    #+#             */
/*   Updated: 2020/10/03 15:15:22 by lucimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libcub3d.h"

/*
** Inverts the TRGB color input
** This is done by substracting the max value (255)
** with the current one. We don't invert Transparency
*/

int	get_opposite(int color)
{
	int	t;
	int	r;
	int	g;
	int	b;

	t = get_t(color);
	r = 255 - get_r(color);
	g = 255 - get_g(color);
	b = 255 - get_b(color);
	return (trgb(t, r, g, b));
}

/*
** Shades the TRGB color input
** distance = 1, shade 100%
** distance = 0.75, shade 75%
** color * 0 = 100% shade
** color * 0.25 = 75% shade
** We don't alter Transparency
*/

int	add_shade(double distance, int color)
{
	int	t;
	int	r;
	int	g;
	int	b;

	if (distance == 0)
		return (color);
	else
		distance = 1 - distance;
	t = get_t(color);
	r = (int)floor(distance * get_r(color));
	g = (int)floor(distance * get_g(color));
	b = (int)floor(distance * get_b(color));
	return (trgb(t, r, g, b));
}
