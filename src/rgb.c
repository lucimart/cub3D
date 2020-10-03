/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucimart <lucimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 18:54:34 by lucimart          #+#    #+#             */
/*   Updated: 2020/10/03 15:10:37 by lucimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Transparency (alpha) and RGB (0-255 all of the previous values)
** Converts the input into an hex with values: 0x TT RR GG BB
** By bitshifting and bit OR. Ex of OR: 1000 | 0010 = 1010 
*/

int		trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

/*
** Get Transparency (alpha)
** TRGB is composed by: 0x TT RR GG BB
** By bitshifting and bit AND. Ex of AND: 1010 | 0010 = 0010 
*/

int		get_t(int trgb)
{
	return (trgb & (0xFF << 24));
}

/*
** Get Red
** TRGB is composed by: 0x TT RR GG BB
** By bitshifting and bit AND. Ex of AND: 1010 | 0010 = 0010 
*/

int		get_r(int trgb)
{
	return (trgb & (0xFF << 16));
}

/*
** Get Green
** TRGB is composed by: 0x TT RR GG BB
** By bitshifting and bit AND. Ex of AND: 1010 | 0010 = 0010 
*/

int		get_g(int trgb)
{
	return (trgb & (0xFF << 8));
}

/*
** Get Blue
** TRGB is composed by: 0x TT RR GG BB
** By bitshifting and bit AND. Ex of AND: 1010 | 0010 = 0010 
*/

int		get_b(int trgb)
{
	return (trgb & 0xFF);
}