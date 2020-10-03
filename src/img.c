/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucimart <lucimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 14:44:12 by lucimart          #+#    #+#             */
/*   Updated: 2020/09/28 14:53:57 by lucimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libcub3d.h"

/*
** Sets the TRGB color to the specified address, calculated by
** the `x` and `y` coords input. Imagine a 2D plane mapped into a 1D line.
** `y * data->line_length` gets the Y axis of the plane and the map is to sum
** the corresponding x position, which transformed the bits into bytes
** `(data->bits_per_pixel / 8)`, we just need to multiply it by x and sum it to
** the calculated new `Y` position.
** Then in that position we just set the TRGB color. Ex: 0x00FF0000 
** is the hex representation of TRGB(0,255,0,0) which is pure red
*/

void            my_mlx_pixel_put(t_data *data, int x, int y, int trgb)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = trgb;
}